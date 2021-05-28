CC=../../build/bin/clang
OP=../../build/bin/opt

$CC -c -emit-llvm -O0 $1.c -o $1.bc

$OP -load ./constSplit.so -constsplit $1.bc -o $1_split.bc

#llvm-dis $1.bc -o $1.ll
#llvm-dis $1_split.bc -o $1_split.ll

$CC -cc1 -O0 $1.bc -o $1
$CC -cc1 -O0 $1_split.bc -o $1_split

../../build/bin/clang $1_split.bc -mllvm -sub -o $1_split_sub.o

#rm *.bc