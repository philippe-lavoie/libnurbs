pushd .
cd image
rename color.cc color.cpp
popd

pushd .
cd include
rename plib_config.hh.vc plib_config.hh
popd


pushd .
cd matrix
rename    barray2d_hpoint.cc     barray2d_hpoint.cpp 
rename    error.cc               error.cpp           
rename    point_nd.cc            point_nd.cpp        
rename    barray_hpoint.cc       barray_hpoint.cpp   
rename    hpoint_nd.cc           hpoint_nd.cpp       
rename    specialType.cc         specialType.cpp     
popd


cd examples

pushd .
cd numerical
rename *.C *.cpp
popd

pushd .
cd matrix
rename *.C *.cpp
popd

pushd .
cd nurbs
rename *.C *.cpp
popd

