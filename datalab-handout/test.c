#include <stdio.h>

void func(int a);

int main(){
	int a;
	printf("the size of array is : ");
 	scanf("%d", &a);
	func(a);
	return 0;
}

void func(int a){
	int A[5][5];
	A[0][0] = 1;
	A[a][a] = a;
	printf("%d %d\n", A[0][0], A[0][2]);
}


