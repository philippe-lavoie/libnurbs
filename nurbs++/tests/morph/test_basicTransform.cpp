#include "../../morph/transform.h"
#include "../../image/image.h"
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace PLib;
using namespace PLib::Morph;

class TestBasicTransform : public CppUnit::TestCase {
  CPPUNIT_TEST_SUITE( TestBasicTransform );
  CPPUNIT_TEST( testErosion );
  CPPUNIT_TEST( testDilation );
  CPPUNIT_TEST_SUITE_END();
public:
  TestBasicTransform(): TestCase("TestBasicTranform"){;}
  TestBasicTransform(std::string name): TestCase(name) {; }

  void setUp();
  void tearDown();

  void testDilation();
  void testErosion();
protected:
  IM_Image m_image;
};

CPPUNIT_TEST_SUITE_REGISTRATION( TestBasicTransform );


void TestBasicTransform::setUp(){
  m_image.read("basic.png");
}

void TestBasicTransform::tearDown(){
}

void TestBasicTransform::testDilation(){
  N8Kernel<unsigned char> kernel;
  IM_Image resultB;
  IM_Image resultG;

  binaryDilation(m_image,kernel,resultB);
  resultB.write("dilationB.png");

  kernel.reset(0);
  grayDilation(m_image,kernel,resultG);
  resultG.write("dilationG.png");

  for(int i=0;i<m_image.rows();++i){
    for(int j=0;j<m_image.cols();++j){
      CPPUNIT_ASSERT_EQUAL((int)resultB(i,j),(int)resultG(i,j));
    }
  }
}

void TestBasicTransform::testErosion(){
  N8Kernel<unsigned char> kernel;
  IM_Image resultB;
  IM_Image resultG;

  binaryErosion(m_image,kernel,resultB);
  resultB.write("erosionB.png");

  kernel.reset(0);
  grayErosion(m_image,kernel,resultG);
  resultG.write("erosionG.png");

  for(int i=0;i<m_image.rows();++i){
    for(int j=0;j<m_image.cols();++j){
      CPPUNIT_ASSERT_EQUAL((int)resultB(i,j),(int)resultG(i,j));
    }
  }
}


#ifdef NO_IMPLICIT_TEMPLATES

namespace CppUnit{

  template TestSuiteFactory<TestBasicTransform>;
  template TestCaller<TestBasicTransform, CppUnit::NoExceptionExpected>;

}

#endif


#ifdef NO_IMPLICIT_TEMPLATES

namespace CppUnit{
  namespace TestAssert{

    template void CppUnit::TestAssert::assertEquals<int>(int const &, int const &, CppUnit::SourceLine, basic_string<char, string_char_traits<char>, __default_alloc_template<true, 0> > const &);

  }
}

#endif // #ifdef NO_IMPLICIT_TEMPLATES

