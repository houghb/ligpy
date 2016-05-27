*********************
Getting started
*********************

Here are some instructions on running a lignin pyrolysis simulation using
ligpy.  The package structure diagram is included here
for reference while following these steps.

  .. image:: ligpy_diagram.svg

1. Make sure that the elemental analysis of the type of lignin you would like to simulate is specified in the file ``elementalanalysis.dat``.  This file is located in the ``ligpy/data/`` folder and it contains instructions on how to format new entries.

2. Create your own version of ``generate_bash_script.py`` to write the
command line function call to ``ligpy.py``.  Alternatively you can run ligpy
directly from the command line with ``python ligpy.py <arguments>``.

Note: Future users will need to modify ``ddasac_utils.py``, and while doing so they can specify their own directory structure for saving the results; the existing code requires a specific directory structure to already exist on cmole at the University of Washington.

3. Run your script. ``ligpy.py`` will handle calls to all the necessary modules to complete the simulation and save the results.

4. Explore your results.  If you have formatted them in the same way that the
sample results (in ``ligpy/sample_results/``) are formatted then only minor
modifications will be required in ``analysis_tools.py`` to use the existing
Jupyter notebook (``explore_ligpy_results.ipynb``), otherwise you can create
your own analysis scripts to suit your purposes.

Updating or revising the kinetic scheme
----------------------------------------
We are publishing the code for this model with the hope that it makes it easy to
revise, improve, and expand the kinetic scheme.  Changing the kinetic scheme
only requires modification of the files ``complete_reaction_list.dat`` and
``complete_rateconstant_list.dat``.  The formatting for these files is
described in the README in ``ligpy/data/``.  Once you've added reactions or
updated kinetic parameters in these files the rest of the code will update
the set of equations that is solved automatically.
