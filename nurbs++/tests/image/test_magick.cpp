#include "image.h"
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace PLib;

class TestMagick : public CppUnit::TestCase {
  CPPUNIT_TEST_SUITE( TestMagick );
  CPPUNIT_TEST( testColorReadWrite );
  CPPUNIT_TEST( testGrayReadWrite );
  CPPUNIT_TEST( testReadGrayFromColor );
  CPPUNIT_TEST( testReadColorFromGray );
  CPPUNIT_TEST_SUITE_END();
public:  
  TestMagick() : TestCase("TestMagick") {;}
  TestMagick(std::string name) : TestCase(name) {; }
  void setUp();
  void tearDown();

  void testColorReadWrite();
  void testGrayReadWrite();
  void testReadGrayFromColor();
  void testReadColorFromGray();

protected:
 
};


CPPUNIT_TEST_SUITE_REGISTRATION( TestMagick );

void TestMagick::setUp(){
}

void TestMagick::tearDown(){
}

/** \brief test the read/write featur of Image Magick
 */
void TestMagick::testColorReadWrite(){
  PLib::IM_ImageT<PLib::Color> imageA;
  IM_ColorImage imageB;

  imageA.resize(300,500);
  imageA.reset(Color(0,0,0));

  for(int i=0;i<imageA.rows();i+=3)
    for(int j=0;j<imageA.cols();j++){
      imageA(i,j) = Color(200,0,255);
      if(i==j){
	imageA(i,j) = Color(255,255,255);
      }
    }

  imageA.write("testColor.png");
  imageB.read("testColor.png");

  CPPUNIT_ASSERT_EQUAL(imageA.rows(),imageB.rows());
  CPPUNIT_ASSERT_EQUAL(imageB.cols(),imageB.cols());

  for(int i=0;i<imageA.rows();i++ )
    for(int j=0;j<imageB.cols();j++){
      CPPUNIT_ASSERT_EQUAL((int)imageA(i,j).r,(int)imageB(i,j).r);
      CPPUNIT_ASSERT_EQUAL((int)imageA(i,j).g,(int)imageB(i,j).g);
      CPPUNIT_ASSERT_EQUAL((int)imageA(i,j).b,(int)imageB(i,j).b);
    }
  
}

/** \brief test the read/write featur of Magick++
 */
void TestMagick::testGrayReadWrite(){
  IM_Image imageA;
  IM_Image imageB;

  imageA.resize(300,500);
  imageA.reset(0);

  for(int i=0;i<imageA.rows();i+=3)
    for(int j=0;j<imageA.cols();j++){
      imageA(i,j) = 200;
      if(i==j){
	imageA(i,j) = 255;
      }
    }

  imageA.write("testGray.png");
  imageB.read("testGray.png");

  CPPUNIT_ASSERT_EQUAL(imageA.rows(),imageB.rows());
  CPPUNIT_ASSERT_EQUAL(imageB.cols(),imageB.cols());

  for(int i=0;i<imageA.rows();i++ )
    for(int j=0;j<imageB.cols();j++){
      CPPUNIT_ASSERT_EQUAL((int)imageA(i,j),(int)imageB(i,j));
    }
}

void TestMagick::testReadGrayFromColor(){
  IM_ColorImage imageA;
  IM_Image imageB;

  imageA.resize(300,500);
  imageA.reset(0);

  for(int i=0;i<imageA.rows();i+=3)
    for(int j=0;j<imageA.cols();j++){
      imageA(i,j) = Color(200,200,200);
      if(i==j){
	imageA(i,j) = Color(255,255,255);
      }
    }

  imageA.write("testColor2.png");
  imageB.read("testColor2.png");

  CPPUNIT_ASSERT_EQUAL(imageA.rows(),imageB.rows());
  CPPUNIT_ASSERT_EQUAL(imageB.cols(),imageB.cols());

  for(int i=0;i<imageA.rows();i++ )
    for(int j=0;j<imageB.cols();j++){
      CPPUNIT_ASSERT_EQUAL((int)imageA(i,j).r,(int)imageB(i,j));
    }
}

void TestMagick::testReadColorFromGray(){
  IM_Image imageA;
  IM_ColorImage imageB;

  imageA.resize(300,500);
  imageA.reset(0);

  for(int i=0;i<imageA.rows();i+=3)
    for(int j=0;j<imageA.cols();j++){
      imageA(i,j) = 200;
      if(i==j){
	imageA(i,j) = 255;
      }
    }

  imageA.write("testGray2.png");
  imageB.read("testGray2.png");

  CPPUNIT_ASSERT_EQUAL(imageA.rows(),imageB.rows());
  CPPUNIT_ASSERT_EQUAL(imageB.cols(),imageB.cols());

  for(int i=0;i<imageA.rows();i++ )
    for(int j=0;j<imageB.cols();j++){
      CPPUNIT_ASSERT_EQUAL((int)imageA(i,j),(int)imageB(i,j).r);
      CPPUNIT_ASSERT_EQUAL((int)imageA(i,j),(int)imageB(i,j).g);
      CPPUNIT_ASSERT_EQUAL((int)imageA(i,j),(int)imageB(i,j).b);
    }
}


#ifdef NO_IMPLICIT_TEMPLATES

namespace CppUnit{

  template TestSuiteFactory<TestMagick>;
  template TestCaller<TestMagick, CppUnit::NoExceptionExpected>;

  namespace TestAssert{
    #if GCC_VERSION >= 30000
    template void assertEquals<Color>(Color const&, Color const&, CppUnit::SourceLine, std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&);
    template void assertEquals<int>(int const&, int const&, CppUnit::SourceLine, std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&);
    #else
    template void CppUnit::TestAssert::assertEquals<int>(int const &, int const &, CppUnit::SourceLine, basic_string<char, string_char_traits<char>, __default_alloc_template<true, 0> > const &);
    template void CppUnit::TestAssert::assertEquals<PLib::Color>(PLib::Color const &, PLib::Color const &, CppUnit::SourceLine, basic_string<char, string_char_traits<char>, __default_alloc_template<true, 0> > const &);
    #endif
  }

}



#endif

