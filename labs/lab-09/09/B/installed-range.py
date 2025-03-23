#!/usr/bin/env python3
"""
Obtain and print the names of the packages without the cpu architecture (similar to A\installed4.py) that were installed within
the range of dates provided by the user (i.e., variables date_from and date_to). 

* Dates provided by the user should follow the format yyyy-mm-dd
* The output for each package belonging to the specified range should be:
yyyy-mm-dd: NAME_OF_PACKAGE
* An example of output from the program is described in range-2020-07-15-to-2020-07-16.txt

"""

import re
import sys

def main():
    if len(sys.argv) < 3:
        sys.exit(0)

    date_from = sys.argv[1]
    date_to   = sys.argv[2]

    # Regex pattern: match lines like "2020-07-15 13:27:45 install linux-headers-4.15.0-111:amd64 ..."
    pattern = re.compile(r" installed ((.+):(.+)) .*")

    with open("dpkg.log", "r") as file:
        for line in file:
            line = line.rstrip()

            if len(line) < 10:
                continue
            log_date = line[:10]
            if date_from <= log_date <= date_to:
                m = pattern.search(line)
                if m:
                    print(f"{log_date}: {m.group(2)}")

if __name__ == "__main__":
    main()
