#include <stdio.h>

//int factorial(int);

main(void)
{
      int n = 5, output = 3;
      int A[];
      A[] = {n, output}
      arr(&A);
      //output = factorial(n);
      printf("Here is %i = %i\n", n, output); 
      return(0);
}

int factorial(int n)
{
      int fact = 1;

      while(n>0)
      {
            fact *= n;
            n--;
      }

      return fact;
}

int arr(int *A[])
{
      //so will this work, pitting in two ints as an array?
      *A[0] = *A[1];
      return 0;
}

