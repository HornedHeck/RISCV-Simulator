import subprocess
from os import listdir
from os import remove as remove_file
from os import path

import pandas
import numpy as nmp

# config
pandas.set_option('display.max_columns', None)
pandas.set_option('display.width', 1000)

is_build = True

if is_build:
    print('Run build ...')
    subprocess.call(
        '/home/hornedheck/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7660.37/bin/cmake/linux/bin/cmake --build '
        '/home/hornedheck/CLionProjects/to_be_or_not_to_be/cmake-build-debug --target Simulator -- -j 9'.split(),
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL
    )
    print('Build finished')
else:
    print('Build skipped')

# run tests
test_results_name = 'test_res'
if path.exists(test_results_name):
    remove_file(test_results_name)

print('Starting tests')
tests_path = 'bpu_tests/build/'
names = []
for f in listdir(tests_path):
    if f.endswith('.riscv'):
        names.append(f.replace('.riscv', ' ').replace('_', ' ').upper())
        subprocess.call(f'./cmake-build-debug/Simulator {tests_path}{f}'.split(), stdout=subprocess.DEVNULL)

print('Tests finished. Reading tests results')

test_res = pandas.read_csv(test_results_name, delim_whitespace=True, header=None)
test_res.columns = ['All', 'Success', 'Time (ms)', 'Cycles', 'Instructions']
test_res.insert(0, 'Name', names)

test_res.insert(3, 'Accuracy %', test_res.iloc[:, 1].to_numpy() / test_res.iloc[:, 2].to_numpy() * 100.0)
test_res.insert(7, 'CPI(Avg.)', test_res.iloc[:, 5].to_numpy() / test_res.iloc[:, 6].to_numpy())

predicted_branches = nmp.sum(test_res.iloc[:, 1].to_numpy())
all_branches = nmp.sum(test_res.iloc[:, 2].to_numpy())
time = nmp.sum(test_res.iloc[:, 4].to_numpy())
cycles = nmp.sum(test_res.iloc[:, 5].to_numpy())
instr = nmp.sum(test_res.iloc[:, 6].to_numpy())
test_res.loc[10] = ['SUMMARY', predicted_branches, all_branches, predicted_branches / all_branches * 100.0, time,
                    cycles, instr, cycles / instr]

print(test_res)

filename = input('Enter filename to save results or leave empty to skip: ')
if not filename.isspace():
    test_res.to_excel(filename + '.xlsx')
