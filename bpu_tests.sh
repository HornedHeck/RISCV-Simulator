#./cmake-build-debug/Simulator bpu_tests/build/ifs_test.riscv

for f in bpu_tests/build/*.riscv
do
  ./cmake-build-debug/Simulator $f
done