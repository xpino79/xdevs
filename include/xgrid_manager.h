#ifndef XGRID_MANAGER_H_
#define XGRID_MANAGER_H_

#include "../include/geometry/xgrid_container.h"

namespace my {

class xgrid_manager
{
private:
    xgrid_manager()
    {
    }
    xgrid_manager(const xgrid_manager &) = delete; 
    xgrid_manager &operator=(const xgrid_manager &) = delete; 
    
    static std::unique_ptr<xgrid_manager> _Myinstance;
    static std::once_flag _Myonce_flag;
    
    std::unique_ptr<xgrid_container> *_Mygrid_container;

public:
    static xgrid_manager& instance();
    
};

} /* namespace my */

#endif /* XGRID_MANAGER_H_ */
