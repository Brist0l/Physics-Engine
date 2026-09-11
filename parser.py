#!/bin/python3

import argparse

parser = argparse.ArgumentParser(
                    prog = "Physics simulator",
                    description = "Simulates physics duh")
parser.add_argument("-e","--euler",help = "Calculate values using semi implicit euler",action="store_true")

args = parser.parse_args()

print(args.euler,end="\0")
