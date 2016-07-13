#include <stdio.h>
int multiply(int x, int y);
int add(int x, int y);
int multiply(int x, int y) {
    return x*y;
}
int add(int x, int y) {
    return x+y;
}
int main(void) {
	int x=4,y=10;
	int (*mul_to_func) (int,int);
	int (*add_to_func) (int, int);
	mul_to_func = multiply;
	add_to_func = add;
	printf("%d*%d=%d\n",x,y,(*mul_to_func)(x,y));
	printf("%d+%d=%d\n",x,y,(*add_to_func)(x,y));
	return 0;
}

