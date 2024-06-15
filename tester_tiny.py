import subprocess as sp
import argparse

def test(prog):
    sp.call(f"g++ {prog}.cpp -o {prog}")
    with open("in.txt", "r") as f:
        sp.call(f"./{prog}.exe", stdin=f)


parser = argparse.ArgumentParser(usage="python tester.py [A-Z]")
parser.add_argument("prog")
args = parser.parse_args()
test(args.prog)