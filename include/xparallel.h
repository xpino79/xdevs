#ifndef XPARALLEL_H_
#define XPARALLEL_H_

#include <vector>
#include <map>
#include <chrono>
#include <tbb/tbb.h> // 병렬
#include "xobject_manager.h"

// tbb-2018.2-9.el8.x86_64.rpm  tbb-devel-2018.2-9.el8.x86_64.rpm
    
void _My_tbb_parallel_for()
{
    std::chrono::high_resolution_clock::time_point _Tbegin;
    std::chrono::high_resolution_clock::time_point _Tend;
    std::chrono::nanoseconds _Tnanoseconds;
    std::chrono::seconds _Tseconds;
    
    tbb::concurrent_unordered_map<int,int> _CUmap;
    for (int i=0;i < 900000;i++)
    {
        _CUmap.insert(tbb::concurrent_unordered_map<int,int>::value_type(i,i*10));
    }

    _Tbegin = std::chrono::high_resolution_clock::now();
    tbb::parallel_for(_CUmap.range(),[](const tbb::concurrent_unordered_map<int,int>::range_type& _Range)
    {
        for (auto _Iter = _Range.begin(); _Iter != _Range.end(); _Iter++)
        {
            // printf("key : %d\t value : %d\n",_Iter->first,_Iter->second);
        }
    }, tbb::auto_partitioner() );

    _Tend = std::chrono::high_resolution_clock::now();
    _Tnanoseconds = _Tend-_Tbegin;
    _Tseconds = std::chrono::duration_cast<std::chrono::seconds>(_Tnanoseconds);
    std::cout << _Tseconds.count() << endl;

    _Tbegin = std::chrono::high_resolution_clock::now();
    for (auto _Iter = _CUmap.begin(); _Iter != _CUmap.end(); _Iter++)
    {
        // printf("key : %d\t value : %d\n",_Iter->first,_Iter->second);
    }

    _Tend = std::chrono::high_resolution_clock::now();
    _Tnanoseconds = _Tend-_Tbegin;
    _Tseconds = std::chrono::duration_cast<std::chrono::seconds>(_Tnanoseconds);
    std::cout << _Tseconds.count() << endl;
 
}
 
#endif /* XPARALLEL_H_ */
