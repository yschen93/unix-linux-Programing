#include <iostream>
#include <cassert>

using namespace std;

namespace cc
{   

template<typename Tp>
class unique_ptr
{
public:
    unique_ptr();
    ~unique_ptr();
    explicit unique_ptr(Tp* ptr);
    unique_ptr(const unique_ptr& rhs) = delete;
    unique_ptr& operator=(const unique_ptr& rhs) = delete;
    unique_ptr(unique_ptr&& rhs) noexcept;
    unique_ptr& operator=(unique_ptr&& rhs) noexcept;
    Tp* get() const;
    Tp& operator*();
    void reset(Tp* ptr = nullptr);
    Tp* release();
    Tp* operator->();
    operator bool() const;

private:
    Tp* ptr_;
};

//default constructor
template<typename Tp>
unique_ptr<Tp>::unique_ptr()
    :ptr_(nullptr)
{

}


template<typename Tp>
unique_ptr<Tp>::unique_ptr(Tp* ptr)
    :ptr_(ptr)
{

}

template<typename Tp>
unique_ptr<Tp>::~unique_ptr()
{
    if (nullptr != ptr_)
    {
        delete ptr_;
        ptr_ = nullptr;
    }
}

template<typename Tp>
unique_ptr<Tp>::unique_ptr(unique_ptr<Tp>&& rhs) noexcept
{
    std::cout << "constructor(&&)" << std::endl;
    ptr_ = rhs.ptr_;
    rhs.ptr_ = nullptr;
}

template<typename Tp>
unique_ptr<Tp>& unique_ptr<Tp>::operator=(unique_ptr<Tp>&& rhs) noexcept
{
    std::cout << "operator=(&&)" << std::endl;
    if (&rhs == this)
        return *this;
    delete ptr_;
    ptr_ = rhs.ptr_;
    rhs.ptr_ = nullptr;
}

template<typename Tp>
Tp* unique_ptr<Tp>::get() const
{
    return ptr_;
}

template<typename Tp>
Tp& unique_ptr<Tp>::operator*()
{
    assert(nullptr != ptr_);
    return *ptr_;
}

template<typename Tp>
void unique_ptr<Tp>::reset(Tp* ptr)
{
    if (nullptr != ptr_)
        delete ptr_;
    ptr_ = ptr;
}

template<typename Tp>
Tp* unique_ptr<Tp>::release()
{
    if (nullptr != ptr_)
    {
        Tp* tmp = ptr_;
        ptr_ = nullptr;
        return tmp;
    }
    return ptr_;
}

template<typename Tp>
Tp* unique_ptr<Tp>::operator->()
{
    assert(nullptr != ptr_);
    return ptr_;
}

template<typename Tp>
unique_ptr<Tp>::operator bool() const
{
    return nullptr != ptr_;
}

}

