# Introduction
	Constant Split and Interleaving is the plug-in of ollvm,
which target on improving the obfuscation of constant value.

# Usage
## get constSplit.so
Use command 
> make 
To get the constSplit.so, which is a share object file used by optcom.sh
## optcom.sh
After *make*, you can use the command below to obfucate your file
For example, if I want to obfuscate *test.c*.
> sh optcom.sh test

# ConstSplit
It will split the binary opration which contain constant value, 
and it usually use **substitution** subsequently.

For example.
> // Before constSplit
> a = b + 10
> 
> // After constSplit
> a = b + 110
> a = a - 100