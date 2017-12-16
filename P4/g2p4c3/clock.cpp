/* clock example: frequency of primes */
#include <stdio.h>      /* printf */
#include <iostream>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>       /* sqrt */

using namespace std;

int frequency_of_primes (int n) {
  int i,j;
  int freq=n-1;
  for (i=2; i<=n; ++i) for (j=sqrt(i);j>1;--j) if (i%j==0) {--freq; break;}
  return freq;
}

int main ()
{
  clock_t t;
  int f;
  t = clock();

  cout<< "Give the largest number  \n"<<endl;
  int numax;
  
  cin >> numax;
  cout << ("A calcular...") << endl;
  f = frequency_of_primes (numax);
  t = clock() - t;
  cout<< "Demorou "<< t<< "clicks, ou seja, "<< ((float)t)/CLOCKS_PER_SEC << endl;

  return 0;
}
