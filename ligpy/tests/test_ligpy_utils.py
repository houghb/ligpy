import unittest

import numpy as np

from ..ligpy_utils import set_paths, get_specieslist, get_speciesindices
from ..ligpy_utils import define_initial_composition, build_k_matrix
from ..ligpy_utils import get_k_value, get_k_value_list
from ..ligpy_utils import build_reactant_dict, build_species_rxns_dict
from ..ligpy_utils import build_rates_list, build_dydt_list

paths = set_paths()


class TestSetPaths(unittest.TestCase):
    """Tests for set_paths()"""

    def test_returns_three_paths(self):
        """Does set_paths() return the expected number of paths?"""
        self.assertEqual(3, len(paths))

    def test_paths_end_correctly(self):
        """Are the correct files in the data directory set?"""
        self.assertEqual('complete_reaction_list.dat', paths[0].split('/')[-1])
        self.assertEqual('complete_rateconstant_list.dat',
                         paths[1].split('/')[-1])
        self.assertEqual('compositionlist.dat', paths[2].split('/')[-1])


class TestGetSpecieslist(unittest.TestCase):
    """Tests for get_specieslist()"""

    def test_correct_num_species(self):
        """Does get_specieslist() return the correct number of species (with
        'correct' being defined as the number of species in the model as
        developed by Hough et al., 2016)"""
        self.assertEqual(93, len(get_specieslist(paths[0])))

    def test_correct_format(self):
        """Are the entries in specieslist strings longer than 1 character?"""
        specieslist = get_specieslist(paths[0])
        for i in np.random.randint(0, len(specieslist), 5):
            self.assertIsInstance(specieslist[i], str, msg='%s is not a '
                                                             'string' %
                                                             specieslist[i])
            self.assertGreaterEqual(len(specieslist[i]), 2)


class TestGetSpeciesindices(unittest.TestCase):
    """Tests for get_speciesindices()"""

    def test_correct_num_outputs(self):
        """Does get_speciesindices() return two objects?"""
        specieslist = get_specieslist(paths[0])
        self.assertEqual(2, len(get_speciesindices(specieslist)))

    def test_key_value_pairs_are_correct(self):
        """Are the key value pairs in both dictionaries what we expect given
        the original kinetic scheme from Hough et al, 2016?"""
        specieslist = get_specieslist(paths[0])
        output = get_speciesindices(specieslist)
        self.assertEqual(output[0]['C3H8O2'], 11)
        self.assertEqual(output[0]['KETM2'], 26)
        self.assertEqual(output[0]['PC2H2'], 36)
        self.assertEqual(output[0]['RADIO'], 64)
        self.assertEqual(output[1][17], 'CO')
        self.assertEqual(output[1][33], 'OH')
        self.assertEqual(output[1][51], 'PLIG')
        self.assertEqual(output[1][87], 'VKETD')

    def test_indicestospecies_keys_match_values_in_speciesindices(self):
        """Do the keys in the dictionary indices_to_species match the
        corresponding values in the dictionary speciesindices?"""
        specieslist = get_specieslist(paths[0])
        output = get_speciesindices(specieslist)
        for i in np.random.randint(0, np.max(output[1].keys()), 5):
            spec = output[1][i]
            self.assertEqual(output[0][spec], i)


class TestDefineInitialComposition(unittest.TestCase):
    """Tests for define_initial_composition()"""

    def test_returns_three_floats(self):
        """Does define_initial_composition() return three floats?"""
        output = define_initial_composition(paths[2], 'Picea_mariana')
        self.assertEqual(len(output), 3)
        self.assertIsInstance(output[0], float)
        self.assertIsInstance(output[1], float)
        self.assertIsInstance(output[2], float)

    def test_returns_correct_compositions(self):
        """Are the returned values of define_initial_composition() what we
        expect?  This test includes one species (mariana) for which one of
        the composition values is corrected from a negative value."""
        out1 = define_initial_composition(paths[2], 'Pinus_ponderosa')
        self.assertEqual(out1, (1.0038777230088756, 0.6284531186401539,
                                0.41646941919803987))
        out2 = define_initial_composition(paths[2], 'Populus_tremuloides')
        self.assertEqual(out2, (0.3283805357061651, 0.8523424921207198,
                                0.6650265093486953))
        out3 = define_initial_composition(paths[2], 'Picea_mariana')
        self.assertEqual(out3, (1.0504939762837022, 1.0255350192402024, 0.0))


class TestBuildKMatrix(unittest.TestCase):
    """Tests for build_k_matrix() assuming the model as published by Hough
    et al, 2016"""

    def test_correct_length(self):
        """Does build_k_matrix() return a list of the correct length?"""
        self.assertEqual(len(build_k_matrix(paths[1])), 406)

    def test_correct_k_values(self):
        """Are the entries from build_k_matrix() what we expect?"""
        kmatrix = build_k_matrix(paths[1])
        self.assertEqual(kmatrix[32], ['1.00E+09', '0', '121394'])
        self.assertEqual(kmatrix[94], ['2.00E+08', '0', '209300'])
        self.assertEqual(kmatrix[207], ['1*10**8', '0', '46046-4186'])
        self.assertEqual(kmatrix[315], ['1*10**8', '0', '56511-4186'])


class TestGetKValue(unittest.TestCase):
    """Tests for get_k_value()"""

    def test_correct_k_value(self):
        """Does get_k_value() return the values we expect (given the model
        as published by Hough et al, 2016)?"""
        kmatrix = build_k_matrix(paths[1])
        self.assertEqual(get_k_value(580, 38, kmatrix), 0.011665275200890215)
        self.assertEqual(get_k_value(580.9, 38, kmatrix), 0.012129247761253214)
        self.assertEqual(get_k_value(0.6, 38, kmatrix), 0.0)
        self.assertEqual(get_k_value(9000, 38, kmatrix), 197434080.52012232)
        self.assertEqual(get_k_value(580, 117, kmatrix), 255857.06048168481)
        self.assertEqual(get_k_value(580, 397, kmatrix), 6.8695960412443435)


class TestGetKValueList(unittest.TestCase):
    """Tests for get_k_value_list()"""

    def test_k_value_list_correct_length(self):
        """Is the k_value_list the correct length?"""
        kmatrix = build_k_matrix(paths[1])
        self.assertEqual(len(get_k_value_list(580, kmatrix)), 406)

    def test_k_values_positive(self):
        """Are all the k_values greater than 0?"""
        kmatrix = build_k_matrix(paths[1])
        self.assertTrue(all(i >= 0 for i in get_k_value_list(580, kmatrix)))
        self.assertTrue(all(i >= 0 for i in get_k_value_list(0.1, kmatrix)))
        self.assertTrue(all(i >= 0 for i in get_k_value_list(250, kmatrix)))
        self.assertTrue(all(i >= 0 for i in get_k_value_list(900, kmatrix)))

    def test_returns_expected_k_values(self):
        """Does the k_value_list match expected results?"""
        kmatrix = build_k_matrix(paths[1])
        kvaluelist = get_k_value_list(580, kmatrix)
        self.assertEqual(kvaluelist[47], 0.011665275200890215)
        self.assertEqual(kvaluelist[108], 0.0011665275200890216)
        self.assertEqual(kvaluelist[401], 2991.9652637313079)


class TestBuildReactantDict(unittest.TestCase):
    """Tests for build_reactant_dict"""

    def test_correct_num_keys(self):
        """Does the returned reactant_dict have the correct number of keys?"""
        speciesindices = get_speciesindices(get_specieslist(paths[0]))[0]
        reactantdict = build_reactant_dict(paths[0], speciesindices)
        self.assertEqual(len(reactantdict), 406)

    def test_returns_expected_values(self):
        """Does the reactant_dict have the values we expect?"""
        speciesindices = get_speciesindices(get_specieslist(paths[0]))[0]
        reactantdict = build_reactant_dict(paths[0], speciesindices)
        self.assertEqual(reactantdict[46], [[24, 1.0], [81, 1.0]])
        self.assertEqual(reactantdict[83], [[81, 1.0], [16, 1.0]])
        self.assertEqual(reactantdict[179], [[59, 1.0], [30, 1.0]])
        self.assertEqual(reactantdict[208], [[66, 1.0], [30, 1.0]])
        self.assertEqual(reactantdict[405], [[64, 1.0], [23, 1.0]])


class TestBuildSpeciesRxnsDict(unittest.TestCase):
    """Tests for build_species_rxns_dict()"""

    def test_correct_num_keys(self):
        """Does the returned reactant_dict have the correct number of keys?"""
        species_rxns = build_species_rxns_dict(paths[0])
        self.assertEqual(len(species_rxns), 93)

    def test_returns_expected_values(self):
        """Does the reactant_dict have the values we expect?"""
        species_rxns = build_species_rxns_dict(paths[0])
        self.assertEqual(species_rxns['ADIOM2'], [[32, -1, '-1'],
                                                  [36, -1, '-1'],
                                                  [84, -1, '-1'],
                                                  [115, 1, '+1'],
                                                  [136, 1, '+1'],
                                                  [157, 1, '+1'],
                                                  [178, 1, '+1'],
                                                  [199, 1, '+1'],
                                                  [220, 1, '+1'],
                                                  [238, -1, '-1'],
                                                  [239, -1, '-1'],
                                                  [240, -1, '-1'],
                                                  [241, -1, '-1'],
                                                  [241, 1, '+1'],
                                                  [242, -1, '-1'],
                                                  [243, -1, '-1'],
                                                  [244, -1, '-1'],
                                                  [245, -1, '-1'],
                                                  [246, -1, '-1'],
                                                  [247, -1, '-1'],
                                                  [248, -1, '-1'],
                                                  [249, -1, '-1'],
                                                  [250, -1, '-1'],
                                                  [251, -1, '-1'],
                                                  [252, -1, '-1'],
                                                  [253, -1, '-1'],
                                                  [254, -1, '-1'],
                                                  [255, -1, '-1'],
                                                  [256, -1, '-1'],
                                                  [257, -1, '-1'],
                                                  [258, -1, '-1'],
                                                  [262, 1, '+1'],
                                                  [283, 1, '+1'],
                                                  [304, 1, '+1'],
                                                  [325, 1, '+1'],
                                                  [346, 1, '+1'],
                                                  [367, 1, '+1'],
                                                  [388, 1, '+1']])
        self.assertEqual(species_rxns['VADIO'], [[90, 1, '+1']])
        self.assertEqual(species_rxns['LIGO'], [[106, 1, '+1'],
                                                [107, -1, '-1']])


class TestBuildRatesList(unittest.TestCase):
    """Tests for build_rates_list()"""

    def test_correct_length(self):
        """Are the correct number of entries present in the rates_list?"""
        speciesindices = get_speciesindices(get_specieslist(paths[0]))
        rates_list = build_rates_list(paths[1], paths[0], speciesindices[0],
                         speciesindices[1])
        self.assertEqual(len(rates_list), 406)

    def test_returns_expected_values(self):
        """Are the expected rate expressions returned?"""
        speciesindices = get_speciesindices(get_specieslist(paths[0]))
        rates_list = build_rates_list(paths[1], paths[0], speciesindices[0],
                         speciesindices[1])
        self.assertEqual(rates_list[15],
                         'rate[15] = kvalue(T,15) * y[76]**1.0 ')
        self.assertEqual(rates_list[45],
                         'rate[45] = kvalue(T,45) * y[23]**1.0 * y[81]**1.0 ')
        self.assertEqual(rates_list[61],
                         'rate[61] = kvalue(T,61) * y[77]**2.0 ')
        self.assertEqual(rates_list[205],
                         'rate[205] = kvalue(T,205) * y[60]**1.0 * y['
                         '30]**1.0 ')

    def test_human_parameter_works(self):
        """Does the parameter, "human" work as expected?"""
        speciesindices = get_speciesindices(get_specieslist(paths[0]))
        rates_list1 = build_rates_list(paths[1], paths[0], speciesindices[0],
                         speciesindices[1], human='yes')
        self.assertEqual(rates_list1[405],
                         'rate[405] = kvalue(T,405) * [RADIO]**1.0 * ['
                         'KET]**1.0 ')
        self.assertRaises(ValueError,
                          lambda: build_rates_list(paths[1], paths[0],
                                                   speciesindices[0],
                                                   speciesindices[1],
                                                   human='valerr'))


class TestBuildDYDTList(unittest.TestCase):
    """Tests for build_dydt_list()"""
    specieslist = get_specieslist(paths[0])
    species_rxns = build_species_rxns_dict(paths[0])
    speciesindices = get_speciesindices(get_specieslist(paths[0]))
    rates_list = build_rates_list(paths[1], paths[0],
                                       speciesindices[0],
                                       speciesindices[1])
    dydt = build_dydt_list(rates_list, specieslist, species_rxns)

    def test_correct_length(self):
        """Are the correct number of ODEs present in the dydt list?"""
        self.assertEqual(len(TestBuildDYDTList.dydt), 93)

    def test_returns_expected_values(self):
        """Does build_dydt_list() return the values we expect?"""
        test1 = TestBuildDYDTList.dydt[22]
        test2 = TestBuildDYDTList.dydt[60]
        test3 = TestBuildDYDTList.dydt[88]
        self.assertEqual(test1, 'd[H2O]/dt = +1*kvalue(T,57) * y[70]**2.0  '
                                '+2*kvalue(T,62) * y[76]**2.0  +2*kvalue(T,'
                                '66) * y[68]**2.0  +2*kvalue(T,67) * y['
                                '67]**2.0  +1*kvalue(T,73) * y[80]**1.0 * y['
                                '74]**1.0  +2*kvalue(T,76) * y[73]**2.0  '
                                '+4*kvalue(T,79) * y[75]**1.0 * y[75]**1.0  '
                                '+1*kvalue(T,129) * y[33]**1.0 * y[29]**1.0  '
                                '+1*kvalue(T,150) * y[33]**1.0 * y[53]**1.0  '
                                '+1*kvalue(T,171) * y[33]**1.0 * y[54]**1.0  '
                                '+1*kvalue(T,192) * y[33]**1.0 * y[30]**1.0  '
                                '+1*kvalue(T,213) * y[33]**1.0 * y[30]**1.0  '
                                '+1*kvalue(T,234) * y[33]**1.0 * y[47]**1.0  '
                                '+1*kvalue(T,255) * y[33]**1.0 * y[1]**1.0  '
                                '+1*kvalue(T,276) * y[33]**1.0 * y[26]**1.0  '
                                '+1*kvalue(T,297) * y[33]**1.0 * y[3]**1.0  '
                                '+1*kvalue(T,318) * y[33]**1.0 * y[27]**1.0  '
                                '+1*kvalue(T,339) * y[33]**1.0 * y[27]**1.0  '
                                '+1*kvalue(T,360) * y[33]**1.0 * y[46]**1.0  '
                                '+1*kvalue(T,381) * y[33]**1.0 * y[0]**1.0  '
                                '+1*kvalue(T,402) * y[33]**1.0 * y[23]**1.0  ')
        self.assertEqual(test2, 'd[PRKETM2]/dt = +1*kvalue(T,8) * y[50]**1.0  '
                                '-1*kvalue(T,9) * y[60]**1.0  -1*kvalue(T,59) '
                                '* y[70]**1.0 * y[60]**1.0  -1*kvalue(T,72) * '
                                'y[69]**1.0 * y[60]**1.0  -1*kvalue(T,121) * '
                                'y[60]**1.0 * y[29]**1.0  -1*kvalue(T,142) * '
                                'y[60]**1.0 * y[53]**1.0  -1*kvalue(T,163) * '
                                'y[60]**1.0 * y[54]**1.0  -1*kvalue(T,184) * '
                                'y[60]**1.0 * y[30]**1.0  -1*kvalue(T,205) * '
                                'y[60]**1.0 * y[30]**1.0  -1*kvalue(T,226) * '
                                'y[60]**1.0 * y[47]**1.0  -1*kvalue(T,247) * '
                                'y[60]**1.0 * y[1]**1.0  -1*kvalue(T,268) * '
                                'y[60]**1.0 * y[26]**1.0  -1*kvalue(T,289) * '
                                'y[60]**1.0 * y[3]**1.0  -1*kvalue(T,310) * '
                                'y[60]**1.0 * y[27]**1.0  -1*kvalue(T,331) * '
                                'y[60]**1.0 * y[27]**1.0  -1*kvalue(T,352) * '
                                'y[60]**1.0 * y[46]**1.0  -1*kvalue(T,373) * '
                                'y[60]**1.0 * y[0]**1.0  -1*kvalue(T,394) * '
                                'y[60]**1.0 * y[23]**1.0  ')
        self.assertEqual(test3, 'd[VKETDM2]/dt = +1*kvalue(T,86) * '
                                'y[25]**1.0  ')


if __name__ == '__main__':
    unittest.main()
