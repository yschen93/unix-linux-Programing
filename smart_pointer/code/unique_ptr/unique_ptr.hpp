#include <iostream>
#include <cassert>
#include <memory>

using namespace std;

namespace cc
{   

template<typename Tp, typename Deleter = std::default_delete<Tp>>
class unique_ptr
{
public:
    unique_ptr(Tp* ptr = nullptr, Deleter deleter = Deleter());
    ~unique_ptr();
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
    Deleter deleter_;
};

template<typename Tp, typename Deleter>
unique_ptr<Tp, Deleter>::unique_ptr(Tp* ptr, Deleter deleter)
    :ptr_(ptr), deleter_(deleter)
{

}

template<typename Tp, typename Deleter>
unique_ptr<Tp, Deleter>::~unique_ptr()
{
    if (nullptr != ptr_)
    {
        deleter_(ptr_);
        ptr_ = nullptr;
    }
}

template<typename Tp, typename Deleter>
unique_ptr<Tp, Deleter>::unique_ptr(unique_ptr<Tp, Deleter>&& rhs) noexcept
{
    ptr_ = rhs.release();
    deleter_ = std::move(rhs.deleter_);
}

template<typename Tp, typename Deleter>
unique_ptr<Tp, Deleter>&
    unique_ptr<Tp, Deleter>::operator=(unique_ptr<Tp, Deleter>&& rhs) noexcept
{
    if (&rhs == this)
        return *this;
    reset(rhs.release());
    deleter_ = std::move(rhs.deleter_);
    return *this;
}

template<typename Tp, typename Deleter>
Tp* unique_ptr<Tp, Deleter>::get() const
{
    return ptr_;
}

template<typename Tp, typename Deleter>
Tp& unique_ptr<Tp, Deleter>::operator*()
{
    assert(nullptr != ptr_);
    return *ptr_;
}

template<typename Tp, typename Deleter>
void unique_ptr<Tp, Deleter>::reset(Tp* ptr)
{
    if (nullptr != ptr_)
        deleter_(ptr_);
    ptr_ = ptr;
}

template<typename Tp, typename Deleter>
Tp* unique_ptr<Tp, Deleter>::release()
{
    Tp* tmp = ptr_;
    ptr_ = nullptr;
    return tmp;
}

template<typename Tp, typename Deleter>
Tp* unique_ptr<Tp, Deleter>::operator->()
{
    assert(nullptr != ptr_);
    return ptr_;
}

template<typename Tp, typename Deleter>
unique_ptr<Tp,Deleter>::operator bool() const
{
    return nullptr != ptr_;
}

}

