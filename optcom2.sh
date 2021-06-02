CC=../../obfuscator-9.0/llvm/bin/clang
OPT=../../obfuscator-9.0/llvm/bin/opt

TAR=$1
PASS=$2
COMMAND=`echo "$PASS" | tr '[:upper:]' '[:lower:]'`

$CC -c -emit-llvm -O0 ${TAR}.c -o ${TAR}.bc

$OPT -load ./lib/${PASS}.so -${COMMAND} ${TAR}.bc -o ${TAR}_${PASS}.bc

llvm-dis ${TAR}.bc -o ./text/${TAR}.ll
llvm-dis ${TAR}_${PASS}.bc -o ./text/${TAR}_${PASS}.ll




$CC  ${TAR}.bc -o ./bin/${TAR}.o # normal
#$CC  ${TAR}_${PASS}.bc -o ${TAR}_${PASS}.o # split

$CC ${TAR}.bc -mllvm -sub -o ./bin/${TAR}_sub.o # sub
$CC ${TAR}.bc -mllvm -fla -o ./bin/${TAR}_fla.o # fla
$CC ${TAR}.bc -mllvm -bcf -mllvm -bcf_prob=100 -o ./bin/${TAR}_bcf.o # bcf

$CC ${TAR}.bc -mllvm -sub -mllvm -fla -mllvm -bcf -mllvm -bcf_prob=100 -o ./bin/${TAR}_sub_fla_bcf.o # sub fla bcf

$CC ${TAR}_${PASS}.bc -mllvm -sub -mllvm -fla -mllvm -bcf -mllvm -bcf_prob=100 -o ./bin/${TAR}_${PASS}_sub_fla_bcf.o # split sub fla bcf