#!/usr/bin/env python3

import math
import sys #import sys for command line arguments
def pythag(a: float, b: float) -> float:
	return math.sqrt(a**2 + b**2)
	
def main():
	if len(sys.argv) != 3: #ensures there are enough command line  arguments
		print("Usage: python pythag3.py <side a> <side b>")
		sys.exit(1)
	
	
    # parse the command-line arguments
    # print an error and quit if there aren't the right number

    # convert the command line arguments from strings to floats
    try:
    	a = float(sys.argv([1])
    	b = float(sys.argv([2])
    except ValueError:
    	print("Please provide vakid numbers for sides a and b")
    	sys.exit(1)
    	
    print("Sides {a} and {b}, hypotenuse = {pythag(a, b):.4f}")
    print("%.4f" % pythag(a, b))


if __name__ == "__main__":
    main()
