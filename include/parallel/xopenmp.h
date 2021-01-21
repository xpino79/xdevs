/* gcc -fopenmp */

#include <stdio.h>

void _My_openmp_for()
{
    int _Sum = 0;

#pragma omp for schedule(static) reduction(+: _Sum)
    for (int _Idx = 0; _Idx < 10; ++_Idx)
    {
        _Sum += _Idx;
    }

#pragma omp for schedule(static) collapse(2) reduction(+: _Sum)
    for (int _Idx_x = 0; _Idx_x < 10; ++_Idx_x)
    {
        for (int _Idx_y = 0; _Idx_y < 10; ++_Idx_y)
        {
            _Sum += _Idx_y;
        }
    }

    int _Max = 0;
#pragma omp for schedule(static)
    for (int _Idx = 0; _Idx < 10; ++_Idx)
    {
        /* 교착상태 방지 */
        if (_Idx > _Max)
        {
#pragma omp critical
            {
                if (_Idx > _Max)
                {
                    _Max = _Idx;
                    _Sum += _Idx;
                }
            }
        }
    }
}
