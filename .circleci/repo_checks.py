"""
Copyright (c) 2016-2020 ARM Limited. All rights reserved.

SPDX-License-Identifier: Apache-2.0

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations 
"""

from pathlib import Path
import glob
import os.path
import sys

level2_set= set()
dup_set = set()


def main():
    for filepath in Path('.').rglob('main.cpp'):
        level2dir=os.path.basename(os.path.dirname(filepath))
        level1dir=os.path.basename(os.path.dirname(os.path.dirname(filepath)))
        level0dir=os.path.dirname(os.path.dirname(os.path.dirname(filepath)))
        
        # check if length of folder name less then 34 
        if len(level2dir) > 34 :
            sys.stderr.write("ERROR: Snippet '{}' length of {} is {} exceed the requirement of 34".format(filepath,level2dir,len(level2dir)))
            sys.exit(1)

        # check if folder level less than 2 
        if level1dir == '':
            sys.stderr.write("ERROR: Snippet '{}' has only one level of folder, but 2 is required".format(filepath))
            sys.exit(1) 

        # check if folder level more than 2 
        if level0dir !=  '':
            sys.stderr.write("ERROR: Snippet '{}' has more than two level of folders, but 2 is required".format(filepath))
            sys.exit(1) 

        if level2dir not in level2_set:
            level2_set.add(level2dir)
        else:
            dup_set.add(level2dir)

    # check duplicated level2 folder names
    if len(dup_set) > 0 :
        for filepath in Path('.').rglob('main.cpp'):
            level2dir=os.path.basename(os.path.dirname(filepath))
            if level2dir in dup_set:
                sys.stderr.write("ERROR level2 name '{}' in path '{}' is has a duplicated with others".format(level2dir,filepath))
        sys.exit(1)


    print("All checks PASSED")


if __name__ == "__main__":
    main()