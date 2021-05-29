CC=../../obfuscator-9.0/llvm/bin/clang
OPT=../../obfuscator-9.0/llvm/bin/opt

TAR=$1
PASS=$2
COMMAND=`echo "$PASS" | tr '[:upper:]' '[:lower:]'`

$CC -c -emit-llvm -O0 ${TAR}.c -o ${TAR}.bc

$OPT -load ./${PASS}.so -${COMMAND} ${TAR}.bc -o ${TAR}_${PASS}.bc

llvm-dis ${TAR}.bc -o ${TAR}.ll
llvm-dis ${TAR}_${PASS}.bc -o ${TAR}_${PASS}.ll

$CC  ${TAR}.bc -o ${TAR}.o
$CC  ${TAR}_${PASS}.bc -o ${TAR}_${PASS}.o

# ../../obfuscator-9.0/llvm/bin/clang ${TAR}_split.bc -mllvm -sub -o ${TAR}_split_sub.o