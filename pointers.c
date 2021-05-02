/*****************************************************************************
 * This model program in C language demonstrates how to create and use 
 * pointers, including pointers to functions and arrays of them.
 *****************************************************************************/

// gcc pointers.c -std=c17 -Wall -Wextra -o zzz

#include <stdio.h> 
#include <stdlib.h>



int func(int i, const char* str)
{
	printf("%d) %s\n", i, str);
	return 0;
}

int add(int a, int b)
{
	printf("%d + %d = %d\n", a, b, a + b);
	return a + b;
}

int subtract(int a, int b)
{
	printf("%d - %d = %d\n", a, b, a - b);
	return a - b;
}

int multiply(int a, int b)
{
	printf("%d * %d = %d\n", a, b, a * b);
	return a * b;
}



int main()
{
	{
		// Pointers to different type variables
		char ch = '#';
		char* p_ch = &ch;
		printf("%c, %p, %lu bytes.\n", *p_ch, p_ch, sizeof(p_ch));  // lu - long unsigned int
		
		int i = 12345;
		int* p_i = &i;
		printf("%d, %p, %lu bytes.\n", *p_i, p_i, sizeof(p_i));
		
		double d = 2.7182818;
		double* p_d = &d;
		printf("%f, %p, %lu bytes.\n", *p_d, p_d, sizeof(p_d));
		
		void* p;
		p = &ch;
		printf("%c, %p, %lu bytes.\n", *((char*)p), p, sizeof(p));
		p = &i;
		printf("%d, %p, %lu bytes.\n", *((int*)p), p, sizeof(p));
	}
	
	{
		int n = 777;
		int* p1 = &n;
		int* p2 = p1;
		if ( *p2 == n && p1 == p2 )  puts("Equal");
	}
	
	{
		int arr[10];
		int* p1 = arr;
		int* p2 = &arr[0];  // The same as the previous line
		if ( p1 == p2 )  puts("p1 equals p2");
//		++arr;  // Compilation error: lvalue required as increment operand
		++p1;
		++p2;
	}

	{
		char str[] = "abcde";
		char* p = str;
		while ( *p )  *p++ = '#';
		puts(str);
	}

	{
		char str[] = "C Programming Language";
		char* p_str = str;
		char buf[30];
		char* p_buf = buf;
		// This is a copying of c-string
		while ( *(p_buf++) = *(p_str++) ) ;  // warning: suggest parentheses around assignment
		p_buf = buf;  p_str = str;
		while ( (*(p_buf++) = *(p_str++)) ) ;
		puts(buf);
		p_buf = buf;  p_str = str;
		// Since postfix increment ++ has higher precedence than dereference *,
		// we can simply write:
		while ( (*p_buf++ = *p_str++) ) ;
		puts(buf);
	}
	
	{
		double d = 14.134725;
		double* p_d = &d;       // Pointer to a variable
		double** p_p_d = &p_d;  // Pointer to a pointer to a variable
		printf("%f\n", **p_p_d);
	}
	
	{
		func(1, "aaaaa");
		int (*p_func)(int, const char*);  // A pointer to function; parentheses are required
		p_func = func;
		(*p_func)(2, "bbbbb");  // Call the function via pointer
		p_func(3, "ccccc");     // The same, but little shorter
		
		// Initialized array of pointers to functions
		int ((*p_oper[3])(int, int)) = {add, subtract, multiply};
		for ( int i = 0; i < 3; ++i )  p_oper[i](i + 2, i + 1);
	}
	
	{
		int *p1 = malloc(5 * sizeof(int));  // Allocates enough for an array of 5 int
		int *p2 = malloc(sizeof(int[5]));   // Same, naming the type directly
		int *p3 = malloc(5 * sizeof(*p3));   // Same, without repeating the type name
		if ( p1 ) 
		{
			for ( int i = 0; i < 5; ++i )  p1[i] = i;
			printf("p1[%d] == %d\n", 2, p1[2]);
		}
 		free(p1);
		free(p2);
		free(p3);
	}
}
