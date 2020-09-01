#ifndef XPARALLEL_H_
#define XPARALLEL_H_

#include <vector>
#include <map>
#include <chrono>
#include <tbb/tbb.h> // 병렬
#include "xobject_manager.h"

// TBB 설치방법
// tbb-2018.2-9.el8.x86_64.rpm  tbb-devel-2018.2-9.el8.x86_64.rpm 설치
// Makefile 에 -ltbb 라이브러리 추가 

void _My_tbb_parallel_for()
{
    std::chrono::system_clock::time_point _Tbegin;
    std::chrono::system_clock::time_point _Tend;
    std::chrono::duration<double> _Tseconds;
    
    tbb::concurrent_unordered_map<int,int> _CUmap;
    for (int i=0;i < 900000;i++)
    {
        _CUmap.insert(tbb::concurrent_unordered_map<int,int>::value_type(i,i*10));
    }

    _Tbegin = std::chrono::system_clock::now();
    tbb::parallel_for(_CUmap.range(),[](const tbb::concurrent_unordered_map<int,int>::range_type& _Range)
    {
        for (auto _Iter = _Range.begin(); _Iter != _Range.end(); _Iter++)
        {
            // printf("key : %d\t value : %d\n",_Iter->first,_Iter->second);
        }
    }, tbb::auto_partitioner() );

    _Tend = std::chrono::system_clock::now();
    _Tseconds = _Tend-_Tbegin;
    std::cout << _Tseconds.count() << " sec" << std::endl;

    _Tbegin = std::chrono::high_resolution_clock::now();
    for (auto _Iter = _CUmap.begin(); _Iter != _CUmap.end(); _Iter++)
    {
        // printf("key : %d\t value : %d\n",_Iter->first,_Iter->second);
    }

    _Tend = std::chrono::system_clock::now();
    _Tseconds = _Tend-_Tbegin;
    std::cout << _Tseconds.count() << " sec"<< std::endl;
 
}
 
#endif /* XPARALLEL_H_ */
