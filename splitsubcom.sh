CC=../../obfuscator-9.0/llvm/bin/clang
OP=../../obfuscator-9.0/llvm/bin/opt

clang -emit-llvm -c test.c -o test.bc

opt -load ./constSplit.so -constsplit test.bc -o test_split.bc

$CC -mllvm -sub test_split.bc -o test_split_sub.o

$CC -mllvm -sub_loop=3 -mllvm -bcf_loop=3 -mllvm -bcf_prob=100 -mllvm -fla -mllvm -split_num=3 test_split.bc -o test_with_split.o

$CC -mllvm -sub_loop=3 -mllvm -bcf_loop=3 -mllvm -bcf_prob=100 -mllvm -fla -mllvm -split_num=3 test.bc -o test_without_split.o

$CC -mllvm -sub -mllvm -bcf -mllvm -bcf_prob=100 -mllvm -fla -mllvm -split test_split.bc -o test_with_split_ease.o

$CC -mllvm -sub -mllvm -bcf -mllvm -bcf_prob=100 -mllvm -fla -mllvm -split test.bc -o test_without_split_ease.o
