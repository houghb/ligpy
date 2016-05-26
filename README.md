### A Kinetic Model for Lignin Pyrolysis (ligpy)
------

Biomass valorization through thermochemical conversion of lignocellulosic feedstocks is limited by our lack of detailed kinetic models. In addition to adding mechanistic understanding, more detailed models are needed to optimize industrial biomass pyrolysis processes for producing fuels and chemicals. To this end, we developed a kinetic model for lignin pyrolysis involving ~100 species and 400 reactions which is capable of predicting the temporal evolution of molecules and functional groups during lignin pyrolysis. The model provides information beyond the lumped yields of common pyrolysis models without any fitting, allowing it to cover a wider range of feedstocks and reaction conditions. Good agreement is observed with slow pyrolysis experiments, and an exhaustive global sensitivity analysis using over two million simulations sheds light on reactions that contribute most to the variance in model predictions (sensitivity analysis results and a package to visualize them are available  [here](https://github.com/houghb/savvy). Model predictions for fast pyrolysis are available, however, recently developed experimental techniques for kinetically-controlled fast pyrolysis of biomass have yet to be applied to lignin.

*ligpy* is a package developed to solve the kinetic model we describe in our 2016 paper, ***Detailed kinetic modeling of lignin pyrolysis for process optimization*** (a link to the paper will be added when it is published).

Please read the documentation for instructions on using ligpy.

**ligpy documentation:**  
**Cite ligpy:**

-------
### Software dependencies and license information

**Programming language:**  
Python version 2.7 (https://www.python.org)

**Python packages needed:**  
NumPy (version 1.10.4 was used but any updated version should be compatible)

The ODE solver that we used for our research is a modified version of DDASAC that is unfortunately not open source.  We chose this solver because it performed the best on the stiff set of ODEs in this model, but future users can modify the code (by replacing our `ddasac_utils.py` module) to use other solvers, such as those in the python package scipy.integrate.

**License information:**   
ligpy is licensed under a BSD 2-clause “Simplified” License. The objective behind this choice of licensing is to make the content reproducible and make it useful for as many people as possible. We want to maximize the two-way collaborations with minimum restrictions, so that developers of other projects can easily utilize, patch, improve, and cite this code. Please refer to the [license](https://github.com/houghb/ligpy/blob/master/LICENSE) for full details.

----------
### Summary of folder contents
