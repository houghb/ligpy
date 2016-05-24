## Some notes on unit testing this package.

I did not write unit tests for modules that are specific to the computational environment at the University of Washington (`ddasac_utils.py`, `generate_bash_script.py`) because these modules will need to be replaced by any users at other institutions so future testing of them is not important.

`revisions_to_faravelli.py` is not unit tested because it is included in the package just for reference and should not need to be run in the future.
