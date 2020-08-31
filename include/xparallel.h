#ifndef XPARALLEL_H_
#define XPARALLEL_H_

#include <vector>
#include <map>
#include <omp.h> // 병렬
#include "xobject_manager.h"

// https://github.com/jakaspeh/concurrency
// https://github.com/jeonggunlee/Parallel_Programming_2018_Fall
// https://www.ibm.com/support/knowledgecenter/en/SSXVZZ_16.1.1/com.ibm.xlcpp1611.lelinux.doc/compiler_ref/prag_omp_dis_psimd.html
// https://github.com/TApplencourt/OvO/blob/master/test_src/cpp/hierarchical_parallelism
// https://www.samsungsds.com/global/ko/news/story/1203227_2919.html
// OpenMP 병렬 프로그래밍 : 멀티 코어를 위한 C, C++ 멀티스레딩의 표준

void _My_map_parallel()
{
    double _Tbegin = 0.0;
    double _Tend = 0.0;
    
    std::int32_t _Priority = 100000;
    my::xobject *_Ptr = nullptr;

    _Tbegin = omp_get_wtime();
    for (auto &_Elem : my::xobject_manager::instance().xobjects())
    {
        my::xobject *_Tmp = _Elem.second.get();
        if (_Priority > _Tmp->priority() )
        {
            _Ptr = _Tmp;
            _Priority = _Tmp->priority();
        }
    }
    std::cout << "#1 " << _Priority << std::endl;
    _Tend = omp_get_wtime() - _Tbegin;
    printf( "#1 %d threads took %fs\n", 1, _Tend );
 
    _Priority = 100000;
    _Ptr = nullptr;
    
    // >>>>> 방안1: 병렬 처리 <싱클코어 보다 느린 속도>
    _Tbegin = omp_get_wtime();
    std::int32_t _Size = my::xobject_manager::instance().xobjects().size();
    #pragma omp parallel for schedule(dynamic)
    for (std::int32_t _Num=0; _Num<_Size; _Num++)
    {
        auto _Iter =  my::xobject_manager::instance().xobjects().begin();
        std::advance( _Iter, _Num); // 엄청느리다.
        
        my::xobject *_Tmp = _Iter->second.get();
        #pragma omp critical
        {
            if (_Priority > _Tmp->priority() )
            {
                _Ptr = _Tmp;
                _Priority = _Tmp->priority();
            }
        }
    }
    std::cout << "#1-1 " << _Priority << std::endl;
    _Tend = omp_get_wtime() - _Tbegin;
    printf( "#1-1 %d threads took %fs\n", omp_get_max_threads(), _Tend );
 
    _Priority = 100000;
    _Ptr = nullptr;
    
    // >>>>> 방안2: 병렬 처리 
    _Tbegin = omp_get_wtime();
    #pragma omp parallel single
    for (auto &_Elem : my::xobject_manager::instance().xobjects())
    {
        my::xobject *_Tmp = _Elem.second.get();
        if (_Priority > _Tmp->priority() )
        {
            _Ptr = _Tmp;
            _Priority = _Tmp->priority();
        }
    }
    std::cout << "#1-2 " << _Priority << std::endl;
    _Tend = omp_get_wtime() - _Tbegin;
    printf( "#1-2 %d threads took %fs\n", omp_get_max_threads(), _Tend );
}


void _My_vector_parallel( my::xobject *_Ptr )
{
    double _Tbegin = 0.0;
    double _Tend = 0.0;
    
    std::int32_t _Sum = 0;
    
    _Tbegin = omp_get_wtime();
    for (auto &_Elem : _Ptr->submodels())
    {
        _Sum += _Elem;
    }
    std::cout << "#2 " << _Sum << std::endl;
    _Tend = omp_get_wtime() - _Tbegin;
    printf( "#2 %d threads took %fs\n", 1, _Tend );
    
    _Sum = 0;
    
    // >>>>> 방안1: 병렬 처리
    _Tbegin = omp_get_wtime();
    std::int32_t _Size = _Ptr->submodels().size();
    #pragma omp parallel for schedule(dynamic) reduction(+:_Sum)
    for (std::int32_t _Num=0; _Num<_Size; _Num++)
    {
        auto _Iter =  _Ptr->submodels().begin();
        std::advance( _Iter, _Num);
      
        _Sum += *_Iter;
    }
    std::cout << "#2 " << _Sum << std::endl;
    _Tend = omp_get_wtime() - _Tbegin;
    printf( "#2-1 %d threads took %fs\n", omp_get_max_threads(), _Tend );

    _Sum = 0;
    
    // >>>>> 방안2: 병렬 처리
    _Tbegin = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic) reduction(+:_Sum)
    for (auto _Iter = _Ptr->submodels().begin(); _Iter < _Ptr->submodels().end(); _Iter++)
    {
        _Sum += *_Iter;
    }
    std::cout << "#2 " << _Sum << std::endl;
    _Tend = omp_get_wtime() - _Tbegin;
    printf( "#2-1 %d threads took %fs\n", omp_get_max_threads(), _Tend );
    
}

#endif /* XPARALLEL_H_ */
