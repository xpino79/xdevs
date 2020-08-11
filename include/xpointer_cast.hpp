namespace my {

template<class T, class U>
inline T* static_pointer_cast(U *ptr)
{ return static_cast<T*>(ptr); }

template<class T, class U>
inline T* dynamic_pointer_cast(U *ptr)
{ return dynamic_cast<T*>(ptr); }

} /* namespace my */
