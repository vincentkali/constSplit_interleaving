CC=../../obfuscator-9.0/llvm/bin/clang
OPT=../../obfuscator-9.0/llvm/bin/opt

TAR=$1
PASS=$2
COMMAND=`echo "$PASS" | tr '[:upper:]' '[:lower:]'`

$CC -c -emit-llvm -O0 ${TAR}.c -o ${TAR}.bc

$OPT -load ./lib/${PASS}.so -${COMMAND} ${TAR}.bc -o ${TAR}_${PASS}.bc

llvm-dis ${TAR}.bc -o ${TAR}.ll
llvm-dis ${TAR}_${PASS}.bc -o ${TAR}_${PASS}.ll

$CC  ${TAR}.bc -o ${TAR}.o
$CC  ${TAR}_${PASS}.bc -o ${TAR}_${PASS}.o

../../obfuscator-9.0/llvm/bin/clang ${TAR}_${PASS}.bc -mllvm -sub -o ${TAR}_${PASS}_sub.o

../../obfuscator-9.0/llvm/bin/clang ${TAR}_${PASS}.bc -mllvm -sub -mllvm -sub_loop=3 -o ${TAR}_${PASS}_subLoop3.o
../../obfuscator-9.0/llvm/bin/clang ${TAR}.bc -mllvm -sub -mllvm -sub_loop=3 -o ${TAR}_subLoop3.o

../../obfuscator-9.0/llvm/bin/clang ${TAR}_${PASS}.bc -mllvm -sub -mllvm -sub_loop=3 -mllvm -fla -o ${TAR}_${PASS}_subLoop3_fla.o
../../obfuscator-9.0/llvm/bin/clang ${TAR}.bc -mllvm -sub -mllvm -sub_loop=3 -mllvm -fla -o ${TAR}_subLoop3_fla.o

../../obfuscator-9.0/llvm/bin/clang ${TAR}_${PASS}.bc -mllvm -sub -mllvm -sub_loop=3 -mllvm -fla -mllvm -split -o ${TAR}_${PASS}_subLoop3_fla_split.o
../../obfuscator-9.0/llvm/bin/clang ${TAR}.bc -mllvm -sub -mllvm -sub_loop=3 -mllvm -fla -mllvm -split -o ${TAR}_subLoop3_fla_split.o

../../obfuscator-9.0/llvm/bin/clang ${TAR}_${PASS}.bc -mllvm -sub -mllvm -sub_loop=3 -mllvm -fla -mllvm -split -mllvm -split_num=3 -o ${TAR}_${PASS}_subLoop3_fla_splitNum3.o
../../obfuscator-9.0/llvm/bin/clang ${TAR}.bc -mllvm -sub -mllvm -sub_loop=3 -mllvm -fla -mllvm -split -mllvm -split_num=3 -o ${TAR}_subLoop3_fla_splitNum3.o

../../obfuscator-9.0/llvm/bin/clang ${TAR}_${PASS}.bc -mllvm -sub -mllvm -sub_loop=3 -mllvm -fla -mllvm -split -mllvm -split_num=3 -mllvm -bcf -mllvm -bcf_prob=100 -o ${TAR}_${PASS}_subLoop3_fla_splitNum3_bcf.o
../../obfuscator-9.0/llvm/bin/clang ${TAR}.bc -mllvm -sub -mllvm -sub_loop=3 -mllvm -fla -mllvm -split -mllvm -split_num=3 -mllvm -bcf -mllvm -bcf_prob=100 -o ${TAR}_subLoop3_fla_splitNum3_bcf.o

../../obfuscator-9.0/llvm/bin/clang ${TAR}_${PASS}.bc -mllvm -sub -mllvm -sub_loop=3 -mllvm -fla -mllvm -split -mllvm -split_num=3 -mllvm -bcf -mllvm -bcf_loop=3 -mllvm -bcf_prob=100 -o ${TAR}_${PASS}_subLoop3_fla_splitNum3_bcfLoop3.o
../../obfuscator-9.0/llvm/bin/clang ${TAR}.bc -mllvm -sub -mllvm -sub_loop=3 -mllvm -fla -mllvm -split -mllvm  -split_num=3 -mllvm -bcf -mllvm -bcf_loop=3 -mllvm -bcf_prob=100 -o ${TAR}_subLoop3_fla_splitNum3_bcfLoop3.o

