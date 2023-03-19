#include "unique_ptr.hpp"

using namespace std;

StrBlobPtr StrBlob::begin() const
{
    return StrBlobPtr(*this);
}