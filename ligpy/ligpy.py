"""
Build and solve the ligpy kinetic model.  This model simulates the
pyrolysis of lignin in a perfectly mixed batch reactor.  For complete model
details see the journal article linked in the README at
https://github.com/houghb/ligpy.

Please read the documentation for instructions on using this module.
"""

import os
import time
import sys

import numpy as np

from equivalent_compositions import write_compositionlist
import ligpy_utils as utils
import ddasac_utils as ddasac

# Time the duration of running this script
script_start_time = time.time()
script_start_time_human = time.asctime()

# These are the files and paths that will be referenced in this program:
file_completereactionlist, file_completerateconstantlist, file_compositionlist\
    = utils.set_paths()
working_directory = 'results_dir'
if not os.path.exists(working_directory):
    os.makedirs(working_directory)

# Make sure the compositionlist is up to date
write_compositionlist(file_compositionlist.split('compositionlist')[0])

# Read command line arguments, defined as follows:
# end_time = end time in seconds (excludes cool down time)
# output_time_step = time step of written results in seconds
# cool_time = time [s] to cool down after isothermal hold
# initial_T = initial temperature in Kelvin
# heat_rate = heating rate in *C/min
# maximum_T = maximum temperature to hold at in Kelvin
# absolute_tolerance, relative_tolerance = the tolerances for the ODE solver
# plant = the species of lignin to model (from `compositionlist.dat`)
if __name__ == "__main__":
    try:
        args = sys.argv[1:]
        end_time = float(args[0])
        output_time_step = float(args[1])
        cool_time = int(args[2])
        initial_T = float(args[3])
        heat_rate = float(args[4])
        maximum_T = float(args[5])
        absolute_tolerance = float(args[6])
        relative_tolerance = float(args[7])
        plant = str(args[8])
    except ValueError:
        print ('Error reading arguments, please check you have passed all '
               'the required arguments.')

print('\nProgram started %s with arguments:\n'
      'end time (s) = %s\n'
      'output time step (s) = %s\n'
      'initial temperature (K) = %s\n'
      'heating rate (K/min) = %s\n'
      'maximum temperature (K) = %s\n'
      'absolute tolerance = %s\n'
      'relative tolerance = %s\n'
      'plant name = %s\n'
       % (script_start_time_human, end_time, output_time_step, initial_T,
          heat_rate, maximum_T, absolute_tolerance, relative_tolerance,
          plant))

# Get lists of all the species in the kinetic scheme and their indices
specieslist = utils.get_specieslist(file_completereactionlist)
speciesindices, indices_to_species = utils.get_speciesindices(specieslist)
# Get kmatrix
kmatrix = utils.build_k_matrix(file_completerateconstantlist)

# Set the initial composition of the lignin polymer
PLIGC_0, PLIGH_0, PLIGO_0 = utils.define_initial_composition(
    file_compositionlist, plant)

# Set the initial conditions for the DDASAC solver
y0_ddasac = np.zeros(len(specieslist))
y0_ddasac[:3] = [PLIGC_0, PLIGH_0, PLIGO_0]
# Solve the model with DDASAC
# This is compartmentalized into its own module so that future users can
# use different solvers of their choice and only need to replace that module
ddasac.run_ddasac(file_completereactionlist, kmatrix, working_directory,
                  y0_ddasac, specieslist, absolute_tolerance,
                  relative_tolerance, initial_T, heat_rate, end_time,
                  maximum_T, output_time_step, cool_time)

script_running_time = time.time() - script_start_time
print('This program took %s seconds to run' % script_running_time)




