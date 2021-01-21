/* gcc -fopenmp */

#include <stdio.h>

void _My_openmp_for()
{
  int sum = 0;
  #pragma omp for schedule(static)
  for(i=0; i<n; i++)
  {
    a[i] = work1(i);
  }
}
