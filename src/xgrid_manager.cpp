#include "../include/xgrid_manager.h"

namespace my
{
std::unique_ptr<xgrid_manager> xgrid_manager::_Myinstance;
std::once_flag xgrid_manager::_Myonce_flag;

xgrid_manager::xgrid_manager()
{
}

xgrid_manager& xgrid_manager::instance()
{
    std::call_once(_Myonce_flag, []() {
        _Myinstance.reset(new xgrid_manager);
    });
    return *(_Myinstance.get());
}

} /* namespace my */
