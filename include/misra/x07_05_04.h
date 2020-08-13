/**
 * Copyright 2020. xpino79@gmail.com All rights reserved.
 */

#ifndef x07_05_04_H_
#define x07_05_04_H_

#include "xtypedefs.h"

namespace my {

std::int32_t MISRA_CPP_07_05_04(std::int32_t _Num)
{
    if (_Num == 0) {
        return 0;    
    }
    return MISRA_CPP_07_05_04(_Num - 1);
}

}

#endif /* x07_05_04_H_ */
