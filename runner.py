import subprocess as sp
import argparse

parser = argparse.ArgumentParser(usage="python runner.py [A-Z]")
parser.add_argument("prog")
args = parser.parse_args()

sp.call(f"g++ {args.prog}.cpp -o {args.prog}")
with open("in.txt", "r") as f:
    sp.call(f"./{args.prog}.exe", stdin=f)
