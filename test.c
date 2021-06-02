#include<stdio.h>

int main(int argc, char** argv){
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);

	if (a + b == 10){
		printf("%d",a);
	}
	else{
		for (int i=0;i<a+b;++i){
			printf("%d",i);
		}
	}
}