# Mbed OS docs-only examples

This repository contains example applications snippets that only exist in the Mbed OS docs.

## Contributions

Contributions to the example folder need to meet these requirements:

- Every individual example snippet needs to contain a `main.cpp` that compiles. You must place this file into a folder with all other required files.
- The path to the folder has to be in the second-level folder structure `Repo_ROOT/<Level1>/<Level2>/main.cpp`. We recommend you follow our conventions: `Repo_ROOT/Category_Topic/Module_Example`.
- A `README.md` file in the snippet folder is optional. Contribute the main instructions and explanatory documents to the [mbed-os-5-docs](https://github.com/ARMmbed/mbed-os-5-docs) repository. 
- The `Level2` folder name, for example `<Module_Example>`, needs to be unique compared to any other `Level2` folder in this repository. It can contain no more than 34 characters.

The CI on this repository checks on the above criteria and also makes sure the snippets can build.

