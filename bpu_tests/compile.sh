rm -rf build

mkdir "build"

#riscv64-unknown-elf-gcc -march=rv64i empty_test.c lib/lib.c -o build/empty_test.riscv
#riscv64-unknown-elf-gcc -march=rv64i ifs_test.c lib/lib.c -o build/ifs_test.riscv

for f in *.c
do
  riscv64-unknown-elf-gcc -march=rv64i $f lib/lib.c -o build/${f%.*}.riscv
done