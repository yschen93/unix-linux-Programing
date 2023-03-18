#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <initializer_list>

using namespace std;

class StrBlobPtr;

class StrBlob
{
public:
    friend StrBlobPtr;
    typedef vector<string>::size_type size_type;
    StrBlob() = default;
    StrBlob(const initializer_list<string>& il)
    : data_(make_shared<vector<string>>(il))
    {

    }

    StrBlob(const StrBlob& rhs)
    :data_(rhs.data_)
    {

    }

    bool empty()
    {
        return data_->empty();
    }

    StrBlobPtr begin() const;

    void push_back(const string& ele) //这里可以用引用&
    {
        data_->push_back(ele);
    }

    void pop_back()
    {
        check(0, "pop_back on empty StrBlob");
        data_->pop_back();
    }

    string& front()
    {
        check(0, "front on empty StrBlob");
        return data_->front();
    }

    string& back()
    {
        check(0, "back on empty StrBlob");
        return data_->back();
    }

    size_type size() const { return data_->size(); }
private:
    shared_ptr<vector<string>> data_;
    void check(size_type i, const string& msg);
};

void StrBlob::check(size_type i, const string& msg)
{
    if (i >= size())
        throw out_of_range(msg);
}

class StrBlobPtr
{
public:
    StrBlobPtr()
    :curr_(0)
    {

    }
    StrBlobPtr(const StrBlob& blob, size_t curr = 0)
    :wptr_(blob.data_)
    ,curr_(curr)
    {

    }

    string& deref() const
    {
        auto p = check(curr_, "deref pass to the end");
        return (*p)[curr_];
    }

    StrBlobPtr& incr()
    {
        check(curr_, "incr pass to the end");
        ++curr_;
        return *this;
    }
private:
    shared_ptr<vector<string>> check(size_t curr, const string& msg) const
    {
        auto p = wptr_.lock();
        if (!p)
            throw runtime_error("unbounded StrBlob");
        if (curr >= p->size())
            throw out_of_range(msg);
        return p;
    }

    weak_ptr<vector<string>> wptr_;
    size_t curr_;
};

