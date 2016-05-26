************************************
Installing ligpy
************************************
Requirements
=====================================

These are the requirements for full functionality of ligpy.  Version numbers
are the versions used when developing ligpy which are known to work.

* Python 2.7
* NumPy 1.10.4
* DDASAC (a stiff ODE solver, not open source)

We used DDASAC as our ODE solver for ligpy because we found it performed the
best on the stiff set of ODEs in this model, both in terms of computational
efficiency (it is several orders of magnitude faster than the ODE solvers in
scipy.integrate) and in its robustness to our very stiff system of equations.
Unfortunately DDASAC is not open source, so future users will need to choose
their own ODE solver and modify some modules in this program accordingly.

This code has been tested in both OS X and Linux environments, but not on a PC.
The potential issues we might expect if running in a Windows environment arise
from statements like ``split('/')`` that are used when accessing pieces of
directory paths.  Users in a Windows environment may need to change all
instances of ``split('/')`` to ``split('\\')`` because Windows uses forward
slashes in file paths while Unix systems use backslashes.  A command line tool
like sed can do this quickly.


Installation
============
Clone the github repo: https://github.com/houghb/ligpy

On the command line, enter the ligpy repo you cloned and run the command:

``python setup.py install``

This will install ligpy on your machine so you can call it from anywhere.
Alternatively you can just run ligpy locally by referencing the absolute or
relative paths to the cloned repository.
