#include <matrix.hh>
#include <matrixTool.hh>

int main(){
  using namespace PLib ; 
  Matrix_FLOAT a(4,4) ;
  int i,j ;

  for(i=0;i<a.rows();++i)
    for(j=0;j<a.cols();++j) 
      a(i,j) = float(maximum(i,j)) ; //+float(i*j)/float(j+1.0) ;
  
  Matrix_FLOAT b(a) ;
  Matrix_FLOAT c(a) ;
  
  c = a+a ;
  cout << "a+a = \n" << c ;
  
  c = a*a ;
  cout << "a*a = \n" << c ;

  a.resize(5,3) ;
  for(i=0;i<a.rows();++i)
    for(j=0;j<a.cols();++j) 
      a(i,j) = float(maximum(i,j)) ; //+float(i*j)/float(j+1.0) ;

  cout << "b =\n" << a << endl ; 
  cout << "b^T=\n" << a.transpose() << endl ; 
   
  return 1 ;
}
