import subprocess as sp
import argparse

inputs = [
"""\
8
aaaaa
baba
cabacb
aaabaaa
bitset
ab
abbaaaabbb
yearnineteeneightyfour
"""
]
outputs = [
"""\
4
4
1
16
1
2
3
1
"""
]

def test(prog, testcase, answer):
    sp.call(f"g++ {prog}.cpp -o {prog}")
    ingen = sp.Popen(f"echo {testcase}", stdout=sp.PIPE)
    run = sp.Popen(f"./{prog}.exe", stdin=ingen.stdout, stdout=sp.PIPE)
    output, _ = run.communicate()
    output = output.decode()
    print(output, end='')
    output = output.split()
    answer = answer.split()
    if len(output) != len(answer):
        print("Output and answer has different number of lines")
        return
    for o, a in zip(output, answer):
        if o != a:
            print(f"Line {output.index(o)}: {o} should be {a}")

parser = argparse.ArgumentParser(usage="python tester.py [A-Z]")
parser.add_argument("prog")
args = parser.parse_args()
for i, o in zip(inputs, outputs):
    test(args.prog, i, o)