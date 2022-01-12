# Introduction
Constant Split and Interleaving is the plug-in of [ollvm](https://github.com/obfuscator-llvm/obfuscator),
which target on improving the obfuscation of constant value.

# Usage
## Get constSplit.so
Use command 
> $ make 

To get the constSplit.so, which is a share object file used by optcom.sh
## Use optcom.sh
After **make**, you can use the command below to obfucate your file
For example, if I want to obfuscate **test.c**.
> $ sh optcom.sh test

# ConstSplit
It will split the binary opration which contain constant value, 
and it usually use [substitution](https://github.com/obfuscator-llvm/obfuscator/wiki/Instructions-Substitution) subsequently.
