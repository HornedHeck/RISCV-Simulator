rm -rf build

mkdir "build"


for f in *.c
do
  riscv64-unknown-elf-gcc -march=rv64i "$f" lib/lib.c -o build/"${f%.*}".riscv
done