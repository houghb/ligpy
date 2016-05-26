"""
Misc utility functions required by several modules in the ligpy program.
"""
import os

import numpy as np

from constants import GAS_CONST, MW

def set_paths():
    """
    Set the absolute path to required files on the current machine.

    Returns
    -------
    reactionlist_path     : str
                            path to the file `complete_reactionlist.dat`
    rateconstantlist_path : str
                            path to the file `complete_rateconstantlist.dat`
    compositionlist_path  : str
                            path to the file `compositionlist.dat`
    """
    module_dir = os.path.abspath(__file__).split('ligpy_utils')[0]
    reactionlist_path = module_dir + 'data/complete_reaction_list.dat'
    rateconstantlist_path = module_dir + 'data/complete_rateconstant_list.dat'
    compositionlist_path = module_dir + 'data/compositionlist.dat'
    return reactionlist_path, rateconstantlist_path, compositionlist_path


def get_specieslist(completereactionlist):
    """
    Make a list of all the molecular species involved in the kinetic scheme.

    Parameters
    ----------
    completereactionlist : str
                           the path to the `complete_reaction_list.dat` file

    Returns
    -------
    specieslist : list
                  a list of all the species in the kinetic scheme
    """
    specieslist = []
    for line in open(completereactionlist, 'r').readlines():
        for spec in line.split(','):
            # If the species has already been added to the list then move on.
            if spec.split('_')[1].split()[0] in specieslist:
                continue
            else:
                specieslist.append(spec.split('_')[1].split()[0])
    specieslist.sort()
    return specieslist


def get_speciesindices(specieslist):
    """
    Create a dictionary to assign an arbitrary index to each of the species in
    the kinetic scheme.

    Parameters
    ----------
    specieslist : list
                  a list of all the species in the model

    Returns
    -------
    speciesindices     : dict
                         a dictionary of arbitrary indices with the species
                         from specieslist as keys
    indices_to_species : dict
                         the reverse of speciesindices (keys are the indices
                         and values are the species)
    """
    speciesindices = {}
    index = 0
    for x in specieslist:
        speciesindices[x] = index
        index += 1
    indices_to_species = dict(zip(speciesindices.values(),
                                  speciesindices.keys()))
    return speciesindices, indices_to_species


def define_initial_composition(compositionlist, species):
    """
    Read the plant ID specified and define the initial composition of the
    lignin polymer in terms of the three model components (PLIGC, PLIGH,
    PLIGO).

    Parameters
    ----------
    compositionlist : str
                      the path of the `compositionlist.dat` file
    species         : str
                      the name of a lignin species that exists in the
                      `compositionlist.dat` file
    Returns
    -------
    pligc_0 : float
              The initial composition (mol/L) of PLIGC
    pligh_0 : float
              The initial composition (mol/L) of PLIGH
    pligo_0 : float
              The initial composition (mol/L) of PLIGO

    """
    for line in open(compositionlist, 'rb').readlines():
        if line.split(',')[0] == species:
            # Initial compositions [mole fraction]
            pligc_mol = float(line.split(',')[1])
            pligh_mol = float(line.split(',')[2])
            pligo_mol = float(line.split(',')[3])
            # The weighted average molar mass of mixture [kg/mol]
            weighted_m = (301*pligc_mol + 423*pligh_mol + 437*pligo_mol)/1000
            # the density of the condensed phase [kg/L]
            density = 0.75
            # Initial compositions [mol/L]
            pligc_0 = density/weighted_m * pligc_mol
            pligh_0 = density/weighted_m * pligh_mol
            pligo_0 = density/weighted_m * pligo_mol
            break
    return pligc_0, pligh_0, pligo_0


def build_k_matrix(rateconsts):
    """
    Build a matrix of all the rate constant parameters (A, n, E).

    Parameters
    ----------
    rateconsts : str
                 the path to the file `complete_rateconstant_list.dat`

    Returns
    -------
    kmatrix : list
              a list of lists that defines a matrix.  Each entry in the list
              is A, n, E for a given reaction
    """
    num_lines = sum(1 for line in open(rateconsts))
    kmatrix = [None]*num_lines
    for i, line in enumerate(open(rateconsts, 'r').readlines()):
        kmatrix[i] = [line.split(' ')[0], line.split(' ')[1],
                      line.split(' ')[2].split()[0]]
    return kmatrix


def get_k_value(T, reaction_index, kmatrix):
    """
    Returns the value of the rate constant for a particular reaction index.

    Parameters
    ----------
    T              : float
                     temperature in Kelvin
    reaction_index : int
                     the index of the reaction for which you want the rate
    kmatrix        : list
                     the kmatrix generated by build_k_matrix()

    Returns
    -------
    k : float
        the value of the rate constant for the given reaction at the given
        temperature.
    """
    k = (eval(kmatrix[reaction_index][0]) *
         T**eval(kmatrix[reaction_index][1]) *
         np.exp(-1 * eval(kmatrix[reaction_index][2]) /(GAS_CONST * T)))
    return k


def get_k_value_list(T, kmatrix):
    """
    Returns a list of all the k-values for a given temperature.

    Parameters
    ----------
    T       : float
              temperature in Kelvin
    kmatrix : list
              the kmatrix generated by build_k_matrix()

    Returns
    -------
    kvaluelist : list
                 a list of all the rate constant values for a given temperature
    """
    kvaluelist = []
    for index, row in enumerate(kmatrix):
        kvaluelist.append(get_k_value(T, index, kmatrix))
    return kvaluelist


def build_reactant_dict(completereactionlist, speciesindices):
    """
    Build a dictionary of the reactants involved in each reaction,
    along with their stoichiometric coefficients.  The keys of the
    dictionary are the reaction numbers, the values are lists of lists
    [[reactant1index, -1*coeff1],...]

    Parameters
    ----------
    completereactionlist : str
                           path to the file `complete_reaction_list.dat`
    speciesindices       : dict
                           the dictionary speciesindices from
                           get_speciesindices()

    Returns
    -------
    reactant_dict : dict
                    a dictionary where keys are reaction numbers and values
                    are lists of lists with the reactants and their
                    stoichiometric coefficients for each reaction
    """
    reactant_dict = {}
    for rxnindex, reaction in enumerate(open(completereactionlist, 'rb')
                                        .readlines()):
        reactants = []
        # x is each coefficient_species set
        for x in reaction.split(','):
            # if the species is a reactant
            if float(x.split('_')[0]) < 0:
                reactants.append([speciesindices[x.split('_')[1].split()[0]],
                                  -1*float(x.split('_')[0])])
                # in preceding line: *-1 because I want the |stoich coeff|
        reactant_dict[rxnindex] = reactants
    return reactant_dict


def build_species_rxns_dict(completereactionlist):
    """
    Build a dictionary where keys are species and values are lists with the
    reactions that species is involved in, that reaction's sign in the net
    rate equation, and the stoichiometric coefficient of the species in that
    reaction.

    Parameters
    ----------
    completereactionlist : str
                           path to the file `complete_reaction_list.dat`

    Returns
    -------
    species_rxns : dict
                   keys are the species in the model; values are lists of
                   [reaction that species is involved in,
                   sign of that species in the net rate equation,
                   stoichiometric coefficient]

    """
    specieslist = get_specieslist(set_paths()[0])
    species_rxns = {}
    for species in specieslist:
        # This loop makes a list of which reactions "species" takes part in
        # and what sign that term in the net rate eqn has
        # and what the stoichiometric coefficient is
        reactions_involved = []
        for rxnindex, line in enumerate(open(completereactionlist, 'rb')
                                        .readlines()):
            # example of x = '-1_ADIO'
            for x in line.split(','):
                # If the species being iterated over is part of this reaction
                if species == x.split('_')[1].split()[0]:
                    # if the species is a reactant
                    if float(x.split('_')[0]) < 0:
                        reactions_involved.append(
                            [rxnindex, -1, x.split('_')[0]])
                    # if the species is a product
                    if float(x.split('_')[0]) > 0:
                        reactions_involved.append(
                            [rxnindex, 1, '+' + x.split('_')[0]])
        species_rxns[species] = reactions_involved
    return species_rxns


def build_rates_list(rateconstlist, reactionlist, speciesindices,
                     indices_to_species, human='no'):
    """ This function writes the list of rate expressions for each reaction.

    Parameters
    ----------
    rateconstlist      : str
                         the path to the file `complete_rateconstant_list.dat`
    reactionlist       : str
                         the path to the file `complete_reaction_list.dat`
    speciesindices     : dict
                         a dictionary of arbitrary indices with the species
                         from specieslist as keys
    indices_to_species : dict
                         the reverse of speciesindices (keys are the indices
                         and values are the species)
    human              : str, optional
                         indicate whether the output of this function should
                         be formatted for a human to read ('yes'). Default
                         is 'no'

    Returns
    -------
    rates_list : list
                 a list of the rate expressions for all the reactions in the
                 model
    """
    kmatrix = build_k_matrix(rateconstlist)
    reactant_dict = build_reactant_dict(reactionlist, speciesindices)
    rates_list = []
    for i, line in enumerate(kmatrix):
        rate = 'rate[%s] = kvalue(T,%s) ' % (i, i)
        concentrations = ''
        for entry in reactant_dict[i]:
            if entry == 'n':   # if there is no reaction
                concentrations = '* 0'
                break
            else:
                if human == 'no':
                    concentrations += '* y[%s]**%s ' % (entry[0], entry[1])
                elif human == 'yes':
                    concentrations += '* [%s]**%s ' % \
                        (indices_to_species[entry[0]], entry[1])
                else:
                    raise ValueError('human must be a string: yes or no')
        rate += concentrations
        rates_list.append(rate)
    return rates_list


def build_dydt_list(rates_list, specieslist, species_rxns, human='no'):
    """This function returns the list of dydt expressions generated for all
    the reactions from rates_list.

    Parameters
    ----------
    rates_list         : list
                         the output of build_rates_list()
    specieslist        : list
                         a list of all the species in the kinetic scheme
    species_rxns       : dict
                         dictionary where keys that are the model species and
                         values are the reactions they are involved in
    human              : str, optional
                         indicate whether the output of this function should
                         be formatted for a human to read ('yes'). Default
                         is 'no'

    Returns
    -------
    dydt_expressions : list
                       expressions for the ODEs expressing the concentration
                       of each species with time
    """
    dydt_expressions = []
    for species in specieslist:
        rate_formation = 'd[%s]/dt = ' % (species)
        # "entry" is [reaction#, sign of that reaction, coefficient]
        for entry in species_rxns[species]:
            if human == 'no':
                rate_formation += '%s*%s ' % \
                    (entry[2], rates_list[entry[0]].split(' = ')[1])
            elif human == 'yes':
                rate_formation += '%s*rate[%s] ' % (entry[2], entry[0])
            else:
                raise ValueError('human must be a string: yes or no')
        dydt_expressions.append(rate_formation)
    return dydt_expressions


def write_rates_and_odes(filename, rates, odes):
    """
    Writes a file that contains the model equations to be solved (a list of
    rate expressions, followed by a list of ODEs for each species).  This
    file is just for reference for humans to be able to look at the specific
    reactions that are modeled, it is not actually used by the program. Users
    should only need to generate this file if they've changed anything about
    the kinetic scheme (it already exists in the data folder).

    Parameters
    ----------
    filename : str
               the filename (including relative path if appropriate) of the
               ratesandodes file to write
    rates    : list
               the output of build_rates_list() with human='yes'
    odes     : list
               the output of build_dydt_list() with human='yes'

    Returns
    -------
    None
    """
    with open(filename, 'wb') as initialize:
        initialize.write('Reaction Rates:\n')
    with open(filename, 'ab') as writer:
        for line in rates:
            writer.write(line+'\n')
        writer.write('\n\nODE''s:\n')
        for line in odes:
            writer.write(line+'\n')


# These are some functions for checking the integrity of some model
# components, but they are not used except for exploratory or verification
# purposes
def check_species_in_MW(specieslist=None):
    """
    Check to make sure that everything in the specieslist is in the MW
    dictionary from `constants.py`.

    Parameters
    ----------
    specieslist : list, optional
                  a list of species to check against. If no list is
                  specified then the function get_specieslist() will be used
                  to generate the default list

    Returns
    -------
    None
    """
    if specieslist == None:
        specieslist = get_specieslist(set_paths()[0])

    for item in MW.keys():
        if item in specieslist:
            print '%s is in specieslist' % ('{: <20}'.format(item))
        else:
            print '********'+item
    for item in specieslist:
        if item in MW.keys():
            print '%s is in MW dictionary' % ('{: <20}'.format(item))
        else:
            print '********'+item
    print '\n%s should equal %s' % (len(MW.keys()), len(specieslist))


def check_mass_balance():
    """
    Check for conservation of mass, and if mass is not conserved, see which
    reactions are creating or losing mass.

    Note that mass will not be wholly conserved in this model because
    protons are not accounted for when radicals are involved in
    non-Hydrogen-abstraction reactions, but all other reactions should
    conserve mass.

    Parameters
    ----------
    None

    Returns
    -------
    total_mass_balance : numpy array
                         an array with the amount of mass gained or lost
                         in each reaction
    """
    specieslist = get_specieslist(set_paths()[0])
    speciesindices = get_speciesindices(specieslist)[0]
    kmatrix = build_k_matrix(set_paths()[1])
    species_rxns = build_species_rxns_dict(set_paths()[0])
    # Make vector of the MW's of each species, in the order from speciesindices
    mw_vector = np.zeros((len(MW), 1))
    for species in MW:
        mw_vector[speciesindices[species]] = MW[species][0]
    mw_vector = mw_vector.transpose()

    # In this stoichiometric matrix, rows are species, columns are reactions
    stoicmatrix = np.zeros((len(speciesindices), len(kmatrix)), dtype='float')
    for species in species_rxns:
        i = speciesindices[species]
        for reaction in species_rxns[species]:
            j = reaction[0]
            stoicmatrix[i, j] += float(reaction[2])

    # The result of this dot product should be a vector full of zeros.
    # This will not be the case because protons are not accounted for when
    # radicals are involved in non-H-abstraction rxns,
    # but all other reactions should be 0
    total_mass_balance = np.dot(mw_vector, stoicmatrix[:, :])

    # Use this to look at which reactions are creating or losing mass
    # (from missing Hydrogen)
    h_sum = 0
    for i, value in enumerate(total_mass_balance[0, :]):
        if value != 0:
            print i, value
        h_sum += value
    print '\nNet mass change = %s' % h_sum
    return total_mass_balance


def check_species_fate():
    """
    Check to see which species (if any) are only produced, but never
    consumed in the model reactions (assuming that all reactions occur).

    Parameters
    ----------
    None

    Returns
    -------
    fate_dict : dictionary
                a dictionary with the fate of model species
    """
    specieslist = get_specieslist(set_paths()[0])
    species_rxns = build_species_rxns_dict(set_paths()[0])
    fate_dict = {}
    for species in specieslist:
        fate_dict[species] = 'produced only'
        for entry in species_rxns[species]:
            if entry[1] < 0:
                fate_dict[species] = 'consumed'
    for species in specieslist:
        if fate_dict[species] == 'consumed':
            del fate_dict[species]
    return fate_dict
