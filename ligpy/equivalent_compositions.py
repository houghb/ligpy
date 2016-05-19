""" Functions related to calculating and saving the equivalent composition
of lignins (in terms of mole fractions of LIGC, LIGH, LIGO) from their
elemental compositions (available experimentally)."""

import numpy as np

# Atomic masses of C, H, O
M_C = 12.011
M_H = 1.0079
M_O = 15.999
# Number of carbon, hydrogen, oxygen atoms
# in 1 mole of LIGC (LC), LIGH (LH), LIGO (LO)
LC_C = 17
LC_H = 17
LC_O = 5
LO_C = 20
LO_H = 23
LO_O = 10
LH_C = 22
LH_H = 29
LH_O = 9


def get_equiv_comp(species, datadir, filewrite=True):
    """
    Function that takes the name of a species of lignin and calculates
    the equivalent composition (mole fractions of LIGC, LIGH, LIGO) based
    on the elemental analysis of that lignin species.  Equivalent composition
    is determined based on a linear relationship assuming conservation
    of mass.

    Parameters
    -----------
    species   : str
                a string corresponding to a species name in the file
                `elementalanalysis.dat`
    datadir   : str
                absolute path to the data directory where compositionlist
                should be saved
    filewrite : bool, optional
                a boolean indicating whether this function is being
                called in order to write the equivalent compositions
                to a file (=True).  If False, information on the
                equivalent composition conversion is printed in addition
                to being returned by the function

    Returns
    --------
    LIGC : float
           the mole fraction of LIGC
    LIGH : float
           the mole fraction of LIGH
    LIGO : float
           the mole fraction of LIGO

    """
    # g [element]/mol [LIG*]
    a_mat = np.array([[LC_C*M_C, LO_C*M_C, LH_C*M_C],
                      [LC_H*M_H, LO_H*M_H, LH_H*M_H],
                      [LC_O*M_O, LO_O*M_O, LH_O*M_O]])

    with open('%s/elementalanalysis.dat' % datadir, 'rb') as elemental:
        names = []
        for line in elemental.readlines():
            names.append(line.split(' ')[0])
            if line.split(' ')[0] == species:
                # Mass fraction of element in lignin
                carb = float(line.split(' ')[1])
                hydr = float(line.split(' ')[2])
                oxyg = float(line.split(' ')[3])
        if species not in names:
            raise ValueError('Species is not in elementalanalysis.dat')

    mass_frac = np.array([carb, hydr, oxyg])
    moles = np.dot(np.linalg.inv(a_mat), mass_frac)
    tot_moles = sum(moles)
    # Mole fraction of each model component
    ligc = moles[0]/tot_moles
    ligh = moles[2]/tot_moles
    ligo = moles[1]/tot_moles

    if filewrite is False:
        print '%s Summary:' % species
        print 'The sum of mass fractions is %s' % (carb+hydr+oxyg)
        print 'The sum of mole fractions is %s' % (ligc+ligh+ligo)
        print '\nMole fractions:\nLigC = %s\nLigH = %s\nLigO = %s' % \
              (ligc, ligh, ligo)
    return ligc, ligh, ligo


def get_species_list(datadir):
    """
    Function that returns a list of all the species of lignin that have
    elemental analyses defined in the file `elementalanalysis.dat`.

    Parameters
    ----------
    datadir : str
              absolute path to the data directory where compositionlist
              should be saved

    Returns
    --------
    species : list
              list of strings for all the species in `elementalanalysis.dat`
    """
    species = []
    with open('%s/elementalanalysis.dat' % datadir, 'rb') as elemental:
        for line in elemental.readlines():
            if line[0] == '#':
                continue
            else:
                species.append(line.split(' ')[0])
    return species


def write_compositionlist(datadir):
    """
    Write (or overwrite) a file, `compositionlist.dat`, that contains
    the equivalent compositions (mole fractions of LIGC, LIGH, LIGO) of
    all the lignin species defined in `elementalanalysis.dat`.

    When calculating equivalent compositions it is possible to generate
    a negative composition for one of the three components. This occurs
    when the elemental analysis is outside of the range that it is possible
    to approximate with the three model components. This function will print
    warnings to the user when this occurs, and will automatically set the
    negative value to zero and distribute the difference among the other two
    components. If the negative value is small, this approach is acceptable;
    if it is too large then you cannot approximate the offending lignin
    species with this model and you should manually delete the entry from
    your `elementalanalysis.dat` file and re-run this function.

    Parameters
    -----------
    datadir : str
              absolute path to the data directory where compositionlist
              should be saved

    Returns
    --------
    None
    """
    # Initialize the file and/or overwrite old versions
    with open('%s/compositionlist.dat' % datadir, 'wb') as initialize:
        initialize.write('# Initial compositions of lignin species.\n'
                         '# .\n'
                         '# List generated from the entries in '
                         'elemental_analysis.dat.\n'
                         '# The compositions herein are mole fractions of the '
                         'three model\n'
                         '# components that describe lignin (LIGC, LIGH, '
                         'LIGO).\n'
                         '# .\n'
                         '# Lines are organized as Species, LIGC, LIGH, '
                         'LIGO\n')

    body = []
    species = get_species_list(datadir)
    _ = [body.append(entry + ',' +
                     str(get_equiv_comp(entry, datadir)[0]) + ',' +
                     str(get_equiv_comp(entry, datadir)[1]) + ',' +
                     str(get_equiv_comp(entry, datadir)[2]) + '\n')
         for entry in species]

    # Check for negative equivalent composition values and correct them
    for i, line in enumerate(body):
        for j, value in enumerate([float(line.split(',')[1]),
                                   float(line.split(',')[2]),
                                   float(line.split(',')[3].rstrip())]):
            if value < 0:
                print 'Negative value encountered: ', line.rstrip()
                positives = []
                # indices (in line.split) of the terms that are positive
                positives = [index+1 for index in [0, 1, 2] if index != j]
                # new values based on setting neg value to 0
                new_value1 = str(float(line.split(',')[positives[0]]) +
                                 0.5 * value)
                new_value2 = str(1 - float(new_value1))
                j_value = '0.0'
                if positives[1] == 3:
                    new_value2 += '\n'
                if j == 2:
                    j_value += '\n'
                body[i] = (body[i]
                           .replace(line.split(',')[positives[0]], new_value1)
                           .replace(line.split(',')[positives[1]], new_value2)
                           .replace(line.split(',')[j + 1], j_value))
                print 'Corrected entry will read: ', body[i]

    with open('%s/compositionlist.dat' % datadir, 'ab') as writer:
        writer.writelines(body)
