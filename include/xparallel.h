#ifndef XPARALLEL_H_
#define XPARALLEL_H_

#include <vector>
#include <map>
#include <omp.h> // 병렬
#include "xobject_manager.h"

void _My_map_parallel()
{
    std::int32_t _Priority = 100000;
    my::xobject *_Ptr = nullptr;

    for (auto &_Elem : my::xobject_manager::instance().xobjects())
    {
        my::xobject *_Tmp = _Elem.second.get();
        if (_Priority > _Tmp->priority() )
        {
            _Ptr = _Tmp;
            _Priority = _Tmp->priority();
        }
    }
    std::cout << "#1 " << _Ptr->key() << " "<< _Priority << std::endl;  

    // >>>>> 방안1: 병렬 처리
    #pragma omp parallel
    {
        for (auto &_Elem : my::xobject_manager::instance().xobjects())
        {
            #pragma single nowait
            {
                my::xobject *_Tmp = _Elem.second.get();
                if (_Priority > _Tmp->priority() )
                {
                    _Ptr = _Tmp;
                    _Priority = _Tmp->priority();
                }                
            }
        }
        std::cout << "#2 " << _Ptr->key() << " "<< _Priority << std::endl;        
    }
    
}

void _My_vector_parallel()
{
  
}
  


#endif /* XPARALLEL_H_ */
