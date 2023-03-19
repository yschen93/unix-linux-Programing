#include "unique_ptr.hpp"
#include <boost/test/unit_test.hpp>
#include "fixture.hpp"

//BOOST_AUTO_TEST_SUITE(s_test_unique_ptr)

// BOOST_AUTO_TEST_CASE(t_1, *boost::unit_test::label("trival"))
// {
//     StrBlob blob({"hello", "c++11"});
//     StrBlobPtr blob_ptr(blob);
    
//     BOOST_REQUIRE_EQUAL(blob_ptr.deref(), "hello");
// }

namespace utf = boost::unit_test;

BOOST_AUTO_TEST_SUITE(suite1)

  BOOST_FIXTURE_TEST_CASE(test_case1, BackgroundFixture)
  {
    BOOST_TEST(true);
    //MOCK_EXPECT(mock_class_p->identifer).once().with(mock::any, mock::any);
    //MOCK_EXPECT(mock_class_p->method).once().with(mock::any, mock::any).calls(
    //  [] (int i, double d)
    //  {}
    //);

    MOCK_EXPECT(mock_class_p->method).once().with(42, 3.14).calls(
      [this] (int i, double d) {
        std::cout << "i: " << i << ", d: " << d << std::endl;
      }
    );

    mock_class_p->method(42, 3.14);
  }

  BOOST_AUTO_TEST_CASE(test_case2)
  {
    BOOST_TEST(true);
  }


  BOOST_AUTO_TEST_CASE(test_case3)
  {
    BOOST_TEST(true);
  }

BOOST_AUTO_TEST_SUITE_END()

// TO DO:
/* 1. BackgroundFixture用 * boost::unit_test::fixture<BackgroundFixture()>时，在BOOST_AUTO_TEST_CASE
 * 里不能用mock_class_p
 * 2. 如果fixture.hpp的methd为int method(int, double)。则在BOOST_AUTO_TEST_CASE里的如下语句编译出错：
 * MOCK_EXPECT(mock_class_p->method).once().with(42, 3.14).returns(42).calls(
      [this] (int i, double d) {
        std::cout << "i: " << i << ", d: " << d << std::endl;
      }
    );
**/
