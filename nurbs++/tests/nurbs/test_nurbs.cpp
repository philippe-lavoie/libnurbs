#include "plib_config.h"

#ifdef HAS_CPPUNIT

#include "nurbs.h"
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace PLib;

class TestNurbs: public CppUnit::TestCase {
  CPPUNIT_TEST_SUITE( TestNurbs );
  CPPUNIT_TEST( testBasicEvaluation );
  CPPUNIT_TEST_SUITE_END();
public:
  TestNurbs() : TestCase("TestNurbs") {; }
  TestNurbs(std::string name) : TestCase(name) {; }

  void setUp();
  void tearDown();

  void testBasicEvaluation();

protected:
  PlNurbsCurvef curve;
  Vector_HPoint3Df control_points;
  Vector_HPoint3Df curve_points;
  Vector_FLOAT knots;
  int degree;
};

CPPUNIT_TEST_SUITE_REGISTRATION( TestNurbs );


void TestNurbs::setUp(){
  degree=2;
  control_points.resize(5);
  knots.resize(8);

  control_points[0] = HPoint3Df(0,0,1,1);
  control_points[1] = HPoint3Df(1,1,1,4);
  control_points[2] = HPoint3Df(3,2,1,1);
  control_points[3] = HPoint3Df(4,1,1,1);
  control_points[4] = HPoint3Df(5,-1,1,1);

  knots[0] = 0;
  knots[1] = 0;
  knots[2] = 0;
  knots[3] = 1;
  knots[4] = 2;
  knots[5] = 3;
  knots[6] = 3;
  knots[7] = 3;

  curve.reset(control_points,knots,degree);
}

void TestNurbs::tearDown(){
}

void TestNurbs::testBasicEvaluation(){
  HPoint3Df hpoint = curve(1.0); 
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0,hpoint.z(),0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(7.0/2.0,hpoint.x(),0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(3.0,hpoint.y(),0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(5.0/2.0,hpoint.w(),0.0001);
}

#ifdef NO_IMPLICIT_TEMPLATES

template CppUnit::TestSuiteFactory<TestNurbs>;
template CppUnit::TestCaller<TestNurbs, CppUnit::NoExceptionExpected>;


#endif


#endif
