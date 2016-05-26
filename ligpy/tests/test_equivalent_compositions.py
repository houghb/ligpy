import unittest

from ..equivalent_compositions import get_equiv_comp, get_species_list
from ..ligpy_utils import set_paths


class TestGetEquivComp(unittest.TestCase):
    """Tests for get_equiv_comp()"""

    def test_returns_three_floats(self):
        """Does get_equiv_comp() return three floats?"""
        datadir = set_paths()[2].split('compositionlist')[0]
        output = get_equiv_comp('Picea_mariana', datadir)
        self.assertEqual(len(output), 3)
        for i in output:
            self.assertIsInstance(i, float)

    def test_returns_expected_values(self):
        """Does get_equiv_comp() return the expected values?"""
        datadir = set_paths()[2].split('compositionlist')[0]
        tuple1 = get_equiv_comp('Picea_mariana', datadir)
        tuple2 = (0.52231922638025652, 0.51029677529754947,
                  -0.032616001677805921)
        for x in [0, 1, 2]:
            self.assertAlmostEqual(tuple1[x], tuple2[x], places=14)
        tuple1 = get_equiv_comp('Populus_tremuloides', datadir)
        tuple2 = (0.17791175297196676, 0.46178664816315829,
                  0.36030159886487506)
        for x in [0, 1, 2]:
            self.assertAlmostEqual(tuple1[x], tuple2[x], places=14)
        tuple1 = get_equiv_comp('Lignoboost', datadir)
        tuple2 = (0.99363870471413362, -0.065770945283958729,
                  0.072132240569825243)
        for x in [0, 1, 2]:
            self.assertAlmostEqual(tuple1[x], tuple2[x], places=14)
        tuple1 = get_equiv_comp('Acer_macrophyllum', datadir)
        tuple2 = (0.36258735738441195, 0.11845586420211719,
                  0.51895677841347088)
        for x in [0, 1, 2]:
            self.assertAlmostEqual(tuple1[x], tuple2[x], places=14)


class TestGetSpeciesList(unittest.TestCase):
    """Tests for get_species_list()"""

    def test_returns_list_of_strings(self):
        """Does get_species_list() return a list of strings?"""
        datadir = set_paths()[2].split('compositionlist')[0]
        self.assertIsInstance(get_species_list(datadir), list)
        self.assertIsInstance(get_species_list(datadir)[3], str)


if __name__ == '__main__':
    unittest.main()
