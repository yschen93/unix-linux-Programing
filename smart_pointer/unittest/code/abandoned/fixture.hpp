#include <boost/test/unit_test.hpp>
#include <turtle/mock.hpp>

class base
{
public:
    void method(int, double) {  }
};

MOCK_BASE_CLASS(mock_class, base)
{
    //MOCK_METHOD(method, 2, void(int, double), identifer)
    MOCK_METHOD(method, 2)
};

namespace utf = boost::unit_test;

BOOST_AUTO_TEST_SUITE(suite1)

struct BackgroundFixture
{
    BackgroundFixture()
    {
        BOOST_TEST_MESSAGE("BackgroundFixture");
        mock_class_p = new mock_class();
    }

    ~BackgroundFixture()
    {
        BOOST_TEST_MESSAGE("~BackgroundFixture");
        delete mock_class_p;
        mock_class_p = nullptr;
    }

    mock_class *mock_class_p;
};


BOOST_AUTO_TEST_SUITE_END()