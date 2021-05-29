CC=../../build-4.0/bin/clang
OPT=../../build-4.0/bin/opt

TAR=$1
PASS=$2
COMMAND=`echo "$PASS" | tr '[:upper:]' '[:lower:]'`

$CC -c -emit-llvm -O0 ${TAR}.c -o ${TAR}.bc

$OPT -load ./${PASS}.so -${COMMAND} ${TAR}.bc -o ${TAR}_${PASS}.bc

exit

llvm-dis ${TAR}.bc -o ${TAR}.ll
llvm-dis ${TAR}_${PASS}.bc -o ${TAR}_${PASS}.ll

$CC -cc1 -O0 ${TAR}.bc -o ${TAR}
$CC -cc1 -O0 ${TAR}_${PASS}.bc -o ${TAR}_${PASS}

# ../../build-4.0/bin/clang ${TAR}_split.bc -mllvm -sub -o ${TAR}_split_sub.o