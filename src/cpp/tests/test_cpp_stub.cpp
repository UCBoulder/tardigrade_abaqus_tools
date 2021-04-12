/**
  * \file test_abaqus_tools.cpp
  *
  * Tests for abaqus_tools
  */

#include<abaqus_tools.h>
#include<sstream>
#include<fstream>

#define BOOST_TEST_MODULE test_abaqus_tools
#include <boost/test/included/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

struct cout_redirect{
    cout_redirect( std::streambuf * new_buffer)
        : old( std::cout.rdbuf( new_buffer ) )
    { }

    ~cout_redirect( ) {
        std::cout.rdbuf( old );
    }

    private:
        std::streambuf * old;
};

BOOST_AUTO_TEST_CASE( testSayHello ){
    /*!
     * Test message printed to stdout in sayHello function
     */

    std::stringbuf buffer;
    cout_redirect rd(&buffer);

    std::string message = "World!";
    boost::test_tools::output_test_stream result; 
    {
        cout_redirect guard( result.rdbuf() );
        cppStub::sayHello(message);
    }

    std::string answer = "Hello World!\n";

    BOOST_CHECK( result.is_equal( answer ) );

}
