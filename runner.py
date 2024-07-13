# `python runner.py [A-Z]` to complie and run `in.txt > [A-Z].cpp` in windows
from subprocess import call
from argparse import ArgumentParser

p = ArgumentParser()
p.add_argument('i')
a = p.parse_args()

call(f'g++ {a.i}.cpp -o {a.i}')
with open('in.txt', 'r') as f:
    call(f'./{a.i}.exe', stdin=f)
