"""
Functions that setup and run the modified DDASAC solver.  This is the ODE
solver used by the Pfaendtner group to solve this model - users from other
institutions may need to configure their own solvers (or use ODE solvers in
python, for example from scipy.integrate).  All the paths and files
referenced in this module are specific to what is on cmole (a computer at
the University of Washington).
"""
from subprocess import call

import numpy as np

from ligpy_utils import set_paths, build_k_matrix
from constants import COOL_RATE


def write_ddasac_format_rxns(reactions_list, kmatrix, working_directory):
    """
    This function writes the reactions in a format appropriate to pass
    to our modified DDASAC solver.  Reactions are written to a file in the
    working directory named `ddasac_format_reactions.dat`.

    Parameters
    ----------
    reactions_list    : str
                        path to the file reactionlist.dat
    kmatrix           : list
                        the output of ligpy_utils.build_k_matrix()
    working_directory : str
                        relative path to your working directory (where to
                        save this file)

    Returns
    -------
    None
    """
    ddasac_format_output = []
    for i, line in enumerate(open(reactions_list, 'rb').readlines()):
        LHS = ''
        kinetics = 'k_jim('
        RHS = ''
        # use these booleans to flag whether the entry is the first on a line
        first_reactant = True
        first_product = True

        for x in line.split(','):
            # if a reactant and the first reactant encountered
            if eval(x.split('_')[0]) < 0 and first_reactant:
                LHS += str(abs(eval(x.split('_')[0]))) + ' ' + x.split('_')[1]
                first_reactant = False
            # if a reactant but is not the first reactant on the line
            elif eval(x.split('_')[0]) < 0:
                LHS += ' + ' + (str(abs(eval(x.split('_')[0]))) + ' ' +
                                x.split('_')[1])
            # if this term refers to the first product
            elif eval(x.split('_')[0]) > 0 and first_product:
                RHS += (str(eval(x.split('_')[0])) + ' ' +
                        x.split('_')[1].split()[0])
                first_product = False
            elif eval(x.split('_')[0]) > 0:
                RHS += ' + ' + (str(eval(x.split('_')[0])) + ' ' +
                                x.split('_')[1].split()[0])
            else:
                raise ValueError('none of the if conditions were met...')

        kinetics += (str(eval(kmatrix[i][0])) + ', ' +
                     str(eval(kmatrix[i][2]))+ ', ' +
                     str(eval(kmatrix[i][1]))+') ')
        LHS += ' -> '
        RHS += ' ;'
        ddasac_format_output.append(LHS + kinetics + RHS + '\n')

    outputfile = '%s/ddasac_format_reactions.dat' % (working_directory)
    with open(outputfile, 'wb') as output:
        first_lines = ['%comp PLIGC:1\n', '%comp PLIGH:2\n',
                       '%comp PLIGO:3\n', '%Renergy=8.314\n', '%%\n']
        output.writelines(first_lines)
        output.writelines(ddasac_format_output)


def write_ddat(y0, specieslist, num_reactions, num_net_reactions, atol,
               rtol, T0, h, t_end, max_T, t_step, working_dir):
    """
    This function writes the ddat.in file to use with our modified DDASAC
    solver.  The file is saved in the working directory specified.

    Parameters
    ----------
    y0                : numpy array
                        an array of the initial concentrations of each species
    specieslist       : lst
                        a list of all the species in the kinetic scheme
    num_reactions     : int
                        the number of reactions in the kinetic scheme
    num_net_reactions : int
                        the number of net reactions in the kinetic scheme
    atol              : float
                        the absolute tolerance of the solver
    rtol              : float
                        the relative tolerance of the solver
    T0                : float
                        initial temperature in degrees Kelvin
    h                 : float
                        heating rate in K/min
    t_end             : float
                        the end time of the simulation in seconds
    max_T             : float
                        maximum temperature in degrees Kelvin
    t_step            : float
                        the output time step that you would like to save
                        results at in seconds
    working_dir       : str
                        relative path to your working directory (where to
                        save this file)

    Returns
    -------
    None
    """
    global ramp_time
    global ddat_outputfile
    if h == 0:     # if the program is isothermal
        ramp_time = t_end
        ddat_outputfile = '%s/ddat_isothermal.in' % (working_dir)
    elif h < 0:   # if this is the cool down period
        ramp_time = t_end
        ddat_outputfile = '%s/ddat_cooldown.in' % (working_dir)
    else:
        # number of sec it takes to ramp from the initial temp to max temp
        ramp_time = float(max_T - T0)*60/h
        if ramp_time > t_end:
            ramp_time = t_end
        ddat_outputfile = '%s/ddat_ramp.in' % (working_dir)

    num_species = len(specieslist)
    with open(ddat_outputfile, 'wb') as ddat:
        file_body = ('ddasac\n'
                     '0\n'
                     '1\n'
                     '%s\n'
                     '%s\n'
                     '1\n'
                     '%s\n'
                     '0\n'
                     '%s\n'
                     '%s\n'
                     '0.0e0\n'
                     '0\n'
                     'batch\n'
                     'concentration\n'
                     '0.0e0\n'
                     '1.0e0\n'
                     '0.0e0\n'
                     '1.0e0\n'
                     '%s\n'
                     '%s\n'
                     '-1\n'
                     '0 %s %s\n'
                     % (num_reactions, num_net_reactions, num_species, rtol,
                        atol, T0, float(h)/60, ramp_time, t_step))
        for entry in y0:
            file_body += str(entry) + ' '
        ddat.write(file_body)


def run_ddasac(reactionlist, kmatrix, working_dir, y0, specieslist, atol,
               rtol, T0, h, t_end, max_T, t_step, cool_time):
    """
    Run the DDASAC ODE solver on the model.  Output from the solver is saved
    in the working directory.

    Parameters
    ----------
    reactionlist      : str
                        path to the file `complete_reactionlist.dat`
    kmatrix           : lst
                        a list of lists that defines a matrix.  Each entry in
                        the list is A, n, E for a given reaction
    working_dir       : str
                        relative path to your working directory (where to
                        save this file)
    y0                : numpy array
                        an array of the initial concentrations of each species
    specieslist       : lst
                        a list of all the species in the kinetic scheme
    atol              : float
                        the absolute tolerance of the solver
    rtol              : float
                        the relative tolerance of the solver
    T0                : float
                        initial temperature in degrees Kelvin
    h                 : float
                        heating rate in K/min
    t_end             : float
                        the end time of the simulation in seconds
    max_T             : float
                        maximum temperature in degrees Kelvin
    t_step            : float
                        the output time step that you would like to save
                        results at in seconds

    Returns
    -------
    None

    """
    # rewrite the reactions in a format ddasac can use
    write_ddasac_format_rxns(reactionlist, kmatrix, working_dir)

    # initialize the solver by copying files and running mech2mod
    call("cp ~/DDASAC_files_needed/bsub.c .;"
         "cp ~/DDASAC_files_needed/jacobian.c .;"
         "~/DDASAC_files_needed/mech2modBH %s/ddasac_format_reactions.dat"
         % working_dir, shell=True)

    # read the number of net reactions from the default ddat.in file
    # (this file will be overwritten by mine)
    with open('ddat.in', 'rb') as ddat:
        net_rxns = ddat.readlines()[4].rstrip()
    num_reactions = len(kmatrix)

    # write ddat.in file for the initial condition to the max temperature
    write_ddat(y0, specieslist, num_reactions, net_rxns, atol, rtol, T0, h,
               t_end, max_T, t_step, working_dir)
    call("make -f /scratch/jpfaendt/software/parest/ddasac/software/Makefile;"
         "cp -f %s ddat.in;"
         "./parest -d ddat.in;"
         "mv graph.out %s/ddasac_results_1.out;"
         "mv net_rates.out %s/ddasac_net_rates_1.out;"
         "mv rates.out %s/ddasac_rates_1.out" %
         (ddat_outputfile, working_dir, working_dir, working_dir), shell=True)

    # Generate new ddat.in file to continue the isothermal portion of this run
    if ramp_time < t_end:
        ddasac_results = '%s/ddasac_results_1.out' % (working_dir)
        # -7 because there are 6 lines of descriptive text at end
        num_lines = sum(1 for line in open(ddasac_results))-7
        y_ddasac = np.zeros((num_lines, len(specieslist)))
        for i, line in enumerate(open(ddasac_results, 'rb').readlines()):
            if 1 <= i < num_lines + 1:
                for j, concentration in enumerate(line.split('\t')[1:-2]):
                    y_ddasac[i-1, j] = concentration

        new_end_time = t_end - ramp_time
        write_ddat(y_ddasac[-1, :], specieslist, num_reactions, net_rxns,
                   atol, rtol, max_T, 0, new_end_time, max_T, t_step,
                   working_dir)
        call("cp -f %s ddat.in;"
             "./parest -d ddat.in;"
             "mv graph.out %s/ddasac_results_2.out;"
             "mv net_rates.out %s/ddasac_net_rates_2.out;"
             "mv rates.out %s/ddasac_rates_2.out" %
             (ddat_outputfile, working_dir, working_dir, working_dir),
             shell=True)

    # Generate a third ddat.in file to use to for the cool down portion
    if cool_time > 0:
        ddasac_results = '%s/ddasac_results_2.out' % (working_dir)
        num_lines = sum(1 for line in open(ddasac_results))-7
        y_ddasac = np.zeros((num_lines, len(specieslist)))
        for i, line in enumerate(open(ddasac_results, 'rb').readlines()):
            if 1 <= i < num_lines + 1:
                for j, concentration in enumerate(line.split('\t')[1:-2]):
                    y_ddasac[i-1, j] = concentration
        new_end_time = cool_time
        write_ddat(y_ddasac[-1, :], specieslist, num_reactions, net_rxns,
                   atol, rtol, max_T, COOL_RATE, new_end_time, max_T, 1,
                   working_dir)
        call("cp -f %s ddat.in;"
             "./parest -d ddat.in;"
             "mv graph.out %s/ddasac_results_3.out;"
             "mv net_rates.out %s/ddasac_net_rates_3.out;"
             "mv rates.out %s/ddasac_rates_3.out" %
             (ddat_outputfile, working_dir, working_dir, working_dir),
             shell=True)


# write_ddasac_format_rxns(set_paths()[0], build_k_matrix(set_paths()[1]), '.')
