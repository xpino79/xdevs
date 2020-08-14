#ifndef XPOINTER_CAST_HPP
#define XPOINTER_CAST_HPP

namespace my {

//static_pointer_cast overload for raw pointers
template<class T, class U>
inline T* static_pointer_cast(U *ptr)
{
    return static_cast<T*>(ptr); 
}

//dynamic_pointer_cast overload for raw pointers
template<class T, class U>
inline T* dynamic_pointer_cast(U *ptr)
{ 
    return dynamic_cast<T*>(ptr);
}

} /* namespace my */

#endif /* POINTER_CAST_HPP */
