#include "unique_ptr.hpp"
#include <boost/test/unit_test.hpp>
#include <string>

BOOST_AUTO_TEST_SUITE(s_test_unique_ptr)

class foo
{
public:
  foo(int i)
    :i_(i)
  {
    std::cout << "foo(), this = " << this << std::endl;
  }
  ~foo()
  {
    std::cout << "~foo(), this = " << this << std::endl;
  }
  int show()
  {
    return i_;
  }

  void set(int i)
  {
    i_ = i;
  }
private:
  int i_;
};

cc::unique_ptr<foo> SomeFunction()
{
  return cc::unique_ptr<foo>(new foo(120));
}

void deleter(foo* ptr)
{
  std::cout << "call deleter" << std::endl;
  delete ptr;
  ptr = nullptr;
}

BOOST_AUTO_TEST_CASE(t_1)
{
  foo* p = new foo(10);
  cc::unique_ptr<foo> up(p);
  BOOST_CHECK_EQUAL(p, up.get());
  BOOST_CHECK_EQUAL(up->show(), 10);

  (*up).set(20);

  cc::unique_ptr<foo> up1(up.release());
  BOOST_CHECK_EQUAL(up1->show(), 20);

  cc::unique_ptr<foo> up2(new foo(100));
  BOOST_CHECK_EQUAL(up2->show(), 100);
  up2.reset(up1.release());
  BOOST_CHECK_EQUAL(up2->show(), 20);

  cc:unique_ptr<foo> up3(up2.release());
  BOOST_CHECK_EQUAL(up3->show(), 20);
  if (!up2)
    BOOST_TEST_MESSAGE("It's ok!");
  else
    BOOST_TEST_MESSAGE("It's error!");

  cc::unique_ptr<foo>&& up4 = SomeFunction();
  BOOST_CHECK_EQUAL(up4->show(), 120);

  cc::unique_ptr<foo> up5;
  up5 = std::move(up4);
  BOOST_CHECK_EQUAL(up5->show(), 120);

  cc::unique_ptr<foo, decltype(deleter)*> up6(new foo(200), deleter);
  up6.reset(up5.release());
    
}

BOOST_AUTO_TEST_SUITE_END()