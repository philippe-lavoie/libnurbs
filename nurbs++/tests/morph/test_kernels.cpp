#include "../../morph/kernel.h"
#include "../../image/image.h"
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace PLib;
using namespace PLib::Morph;

class TestKernels : public CppUnit::TestCase {
  CPPUNIT_TEST_SUITE( TestKernels );
  CPPUNIT_TEST( testDisk );
  CPPUNIT_TEST( testConicDisk );
  CPPUNIT_TEST( testGaussianDisk );
  CPPUNIT_TEST_SUITE_END();
public:
  TestKernels(): TestCase("TestKernels"){;}
  TestKernels(std::string name): TestCase(name) {; }

  void setUp();
  void tearDown();

  void testDisk();
  void testConicDisk();
  void testGaussianDisk();
protected:
  IM_Image m_image;
};

CPPUNIT_TEST_SUITE_REGISTRATION( TestKernels );


void TestKernels::setUp(){
}

void TestKernels::tearDown(){
}

void TestKernels::testDisk(){
  DiskKernel<unsigned char> disk(100,255);

  IM_Image image;
  image = disk;
  image.write("disk100.png");
}

void TestKernels::testConicDisk(){
  ConicDiskKernel<unsigned char> disk(100,128,255);

  IM_Image image;
  image = disk;
  image.write("conic100.png");
}

void TestKernels::testGaussianDisk(){
  GaussianDiskKernel<unsigned char> disk(100,128,255);

  IM_Image image;
  image = disk;
  image.write("gaussian100.png");
}


#ifdef NO_IMPLICIT_TEMPLATES

namespace CppUnit{

  template TestSuiteFactory<TestKernels>;
  template TestCaller<TestKernels, CppUnit::NoExceptionExpected>;



}

#endif

