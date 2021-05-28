#include<stdio.h>

int main(void){
	int a = 1;
	int b = 2;
	
	int c = b + 3;
	if (c>3){
		a = b + 4;
	}else{
		a = c + 4;
	}
	
	printf("value: %d",a);
}