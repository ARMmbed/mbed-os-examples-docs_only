# Mbed OS Docs-Only Examples
This repository contains example applications snippets that currently only exist in the Mbed OS docs.

## Contributions

Contribute the the example folder need to following bellow requirements
- Every individual example snippet need to contain a compile-able `main.cpp` and placed into one folder with all required files.
- The path to the folder has to be in the 2 level folder structure `Repo_ROOT/<Level1>/<Level2>/main.cpp` we recommend to following our conventions: `Repo_ROOT/Category_Topic/Module_Example`
- A `README.md` file in the snippet folder is optional, the main instruction and explanatory documents should be contributed to [mbed-os-docs](https://github.com/ARMmbed/mbed-os-5-docs). 
- the `Level2` folder name, e.g. `<Module_Example>`, need to be unique to any other `Level2` folder in this repository and contains no more than 34 characters.
- The CI on this repository will check on the above criteria and also make sure the snippets able to be built 

