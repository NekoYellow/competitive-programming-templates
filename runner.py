# `python runner.py [A-Z]` to complie and run `in.txt > [A-Z].cpp` in windows
from subprocess import call
from argparse import ArgumentParser

p = ArgumentParser()
p.add_argument('prog')
a = p.parse_args()

call(['g++', a.prog+'.cpp', '-o', a.prog, '-std=c++20'])
with open('in.txt', 'r') as f:
    call(f'./{a.prog}.exe', stdin=f)
