#include <stdio.h>
#include <math.h>

float factorial(int);


main(void)
{
      float x=1.0, n=1.0, ans[6], a1=1.0, a2=1.0, sinh=0.0, cosh=0.0;
      int i=0;
      float  nFact=0;
      float toll = 1*pow(10, -10);
      printf("The toll fee is %.7f\n", toll);
      
      //open a file to print to and print a header
      FILE *file;
      file = fopen("ans", "wt");
      fprintf(file, "#x   Exact          Method 1       Method 2       Method 3       Method 4       Method 5\n");
      
      //lets do some diagnostics
      FILE *diag;
      diag = fopen("diag", "wt");

      for(x=1; x<=10.0; x++)
      {
            //try the answer for built in function
            ans[0] = exp(-x);

            //brute force
            //reset my parameters
            ans[1] = 0.0;
            a1=1.0, a2=1.0;
            for(n=1.0; fabs(a2) >= toll; n++)
            {
                  ans[1] += a1;
                  nFact = factorial((int)(n));
                  //to test
                  //int one = pow(-1,n);
                  //float power = pow(x, n);
                  a2 = pow(-1,n)*pow(x,n)/(float)(nFact);
                  //fprintf(diag, "%.1f %.1f %.7f %f %.7f %i\n", x, n, ans[1], nFact, a2, fabs(a2)>=toll);
                  //increment to the next step
                  a1 = a2;
            }
            
            //brute force then inversion
            //reset my parameters
            ans[2] = 0.0;
            a1=1.0, a2=1.0;
            for(n=1.0; fabs(a2) >= toll; n++)
            {
                  ans[2] += a1;
                  nFact = factorial((int)(n));
                  a2 = pow(x,n)/(float)(nFact);
                  a1 = a2;
            }
            //no to invert the answer
            ans[2] = 1/ans[2];

            //brute force with recursion
            //reset my prarameter
            ans[3] = 0.0;
            a1=1.0, a2=1.0;
            for(n=1.0; fabs(a2) >= toll; n++)
            {
                  //sum up the a's
                  ans[3] += a1;
                  a2 = -(x/n)*a1;
                  //fprintf(diag, "%.1f %.1f %.7f %.7f %i\n", x, n, ans[3], a2, fabs(a2)>=toll);
                  //increment to the next step
                  a1=a2;
            }
            printf("stage1 %.9f\n", n);

            //fprintf(diag, "\nsinh\n");
            //sinh and cosh summation
            //reset my parameters
            ans[4] = 0.0;
            //first do sinh
            a1 = x, a2 = 1.0, sinh=0.0;
            for(n=1.0; fabs(a2) >= toll; n++)
            {
                  //sum up the rcursive parameters
                  sinh += a1;
                  a2 = a1*pow(x,2)/(n*(4.0*n+2.0));
                  //fprintf(diag, "%.1f %.1f %.7f %.7f %i\n", x, n, sinh, a2, fabs(a2)>=toll);
                  //recurse
                  a1 = a2;
            }
            //fprintf(diag, "\ncosh\n");
            //for cosh
            a1 = 1.0, a2 = 1.0, cosh = 0.0;
            for(n=1.0; fabs(a2) >= toll; n++)
            {
                  //sum up the recursive parameters
                  cosh += a1;
                  a2 = a1*(pow(x,2))/(n*(4.0*n-2.0));
                  //fprintf(diag, "%.1f %.1f %.7f %.7f %i\n", x, n, cosh, a2, fabs(a2)>=toll);
                  //recurse
                  a1 = a2;
            }
            //now add the two terms
            ans[4] = cosh - sinh;

            //recursion with inversion
            //reset my parameters
            ans[5] = 0.0;
            a1 = 1.0, a2 = 1.0;
            for(n=1.0; fabs(a2) >= toll; n++)
            {
                  ans[5] += a1;
                  a2 = (x/n)*a1;
                  fprintf(diag, "%.1f %.1f %.7f %.7f %i\n", x, n, ans[5], a2, fabs(a2)>=toll);
                  //recurse
                  a1 = a2;
            }
            //now invert
            ans[5] = 1/ans[5];

            /*
            //sinh cosh pairs (grad student part)
            //reset my parameters
            ans[5] = 0.0;
            sinh = x, cosh = 1.0;
            a1 = cosh - sinh, a2 = 1.0;
            for(n=1.0; fabs(a2)>=toll; n++)
            {
                  ans[5] += a1;
                  sinh = sinh*pow(x,2)/(n*(4.0*n+2.0));
                  cosh = cosh*pow(x,2)/(n*(4.0*n-2.0));
                  a2 = cosh - sinh;
                  a1=a2;
            }*/


            //now save the data to a file
            fprintf(file, "%-03.1f  ", x);
            for(i=0; i<=5; i++)
            {
                  fprintf(file, "%-.7e  ", ans[i]);
            }
            fprintf(file, "\n");
            fprintf(diag, "\n\n");
      }
      fclose(file);
      fclose(diag);

}

//jsut making a simple factorial function
float factorial(int n)
{
      double output=1;
      while(n>0)
      {
            output *= n;
            n--;
      }
      
      return output;
}

