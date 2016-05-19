"""
Contains functions that generate bash scripts to run the ligpy model from
the command line (on cmole).  If you are a user that is not in the Pfaendtner
research group at the University of Washington you will not have access to
cmole, so you must replace the function `write_script()` below with one
appropriate for the environment you want to solve the model in.
"""

import equivalent_compositions as ec
from constants import COOL_RATE, ABSOLUTE_TOLERANCE, RELATIVE_TOLERANCE

# initial temperature in Celsius
T0 = 25


def choose_params():
    """
    This function prompts the user for the input parameters necessary to
    run the ligpy model.

    Returns
    --------
    h         : float
                the heating rate in C/min
    Tmax      : float
                the maximum temperature in C
    t_end     : float
                the end time for reactions in seconds
    cool_time : float
                the length of time (s) to cool down at 13C/min (the
                cool_rate is set in `constants.py`)
    species   : str
                the lignin species to model
    t_step    : float
                the output time step for storing data in seconds
    """
    # Choose heating rate
    t_unit = raw_input('What is the time unit of your heating '
                       'rate (min, s, ms)? ')
    h = float(input('What is the heating rate (in C/time) for the '
                    'time unit you entered? '))

    if t_unit == 'min':
        h = h            # units of C/min
    elif t_unit == 's':
        h *= 60         # convert to C/min
    elif t_unit == 'ms':
        h = h * 1000 * 60    # convert to C/min
    else:
        print 'Please try again with min, s, or ms'

    print '----- Heating rate is %s C/min\n' % h

    # Choose end time (cooling time, if specified, will continue after this)
    Tmax = input('What is the max temperature in Celsius? ')
    hold = input('How many seconds do you want to hold '
                 'after reaching the max temperature? ')

    t_end = float(Tmax - T0) / (h / 60) + hold
    print ('----- Time to reach max temperature is %s seconds. '
           't_end has been set to %s s.\n' %
           (float(Tmax - T0) / (h / 60), t_end))

    # Choose the cooling time (at 13C/min)
    cool = raw_input('Do you want to include cooling time (y or n)? ')
    if cool == 'n':
        cool_time = 0
    else:
        # the cooling time in seconds
        cool_time = (Tmax - T0) * 60 / (-1 * COOL_RATE)
    print '----- The cooling time is %s seconds.\n' % cool_time

    # Choose the species to model
    species = raw_input('Enter the name of the species you want to model.\n'
                        'If you need to see a list of available species '
                        'type `list`. ')
    if 'list' in species:
        for spec in ec.get_species_list():
            print spec
        species = raw_input('\nPlease enter a species from the list: ')

    while species not in ec.get_species_list():
        print '\nThat is not in the list, here are the choices: '
        for spec in ec.get_species_list():
            print spec
        species = raw_input('\nWhich species? ')

    print '----- The species is %s.\n' % species

    # Choose the output time step for storing data
    t_step = input('What is the time step you would like to store data '
                   'at (s)? ')

    return h, Tmax, t_end, cool_time, species, t_step


def write_script(h, Tmax, t_end, cool_time, species, t_step, T0=T0):
    """
    Write the bash script that will run the simulation and saves it in the
    current directory.  This script is meant to be run from my home
    directory on cmole.  It creates new directories and runs `ligpy.py`.
    If you are running this on another machine (not cmole) then you must
    write your own function to replace this one.

    Parameters
    -----------
    h         : float
                the heating rate in C/min
    Tmax      : float
                the maximum temperature in C
    t_end     : float
                the end time for reactions in seconds
    cool_time : float
                the length of time (s) to cool down at 13C/min
    species   : str
                the lignin species to model
    t_step    : float
                the ouput time step for storing data in seconds
    T0        : float, optional
                the initial temperature in C (default 25C)

    Returns
    --------
    None
    """
    sh_file = ('~/ligpy_%s-%sK_to_%sK-%sCperMin-%send-%scool.sh'
               % (species, T0+273, Tmax+273, h, t_end, cool_time))
    # the name of the directory where results are stored
    directory_name = ('%s-max%sK-%sCperMin-%send-%scool' %
                      (species, Tmax+273, h, t_end, cool_time))

    # Initialize the output file and overwrite old versions.
    open(sh_file, 'wb').write('#!/bin/bash\n')

    code = ['#This script runs the python code with'
            'the following parameters:\n'
            '#Temperature: %s C to %s C\n'
            '#Heating rate: %s C/min\n'
            '#End time (of heating or isothermal stage): %s s\n'
            '#Cooling time: %s s\n'
            '#Output time step: %s s\n'
            '#Lignin species: %s\n\n'
            % (T0, Tmax, h, t_end, cool_time, t_step, species)]

    code.append('chmod 644 %s\n' % (sh_file.split('/')[2]))
    code.append('mkdir model_runs/%s\n' % directory_name)
    code.append('cd model_runs/%s\n' % directory_name)
    code.append('python ~/ligpy/ligpy/ligpy.py %s %s %s %s %s %s %s %s %s '
                '&> lig_model.log &\n'
                % (t_end, t_step, cool_time, T0+273.15, h,
                   Tmax+273.15, ABSOLUTE_TOLERANCE, RELATIVE_TOLERANCE,
                   species))
    code.append('cd ../..\n')
    open(sh_file, 'ab').writelines(code)

write_script(*choose_params())
