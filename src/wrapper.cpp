#include <Rcpp.h>

typedef void (*fp)(double*a, double* b);

// c interface to fortran fct 'test'
extern "C" {
 void test_(double* x, double* y);
}

// fortran function which calls fortran
extern "C" {
  void call_fortran2_();
}

// [[Rcpp::export]]
void call_fortran_which_call_fortran_via_c() {
 call_fortran2_();
}
