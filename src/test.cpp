 #include <Rcpp.h>

typedef void (*fp)();

// c interface to fortran fct
extern "C" {
  void test_();
}

// call fortran from rcpp
// [[Rcpp::export]]
void call() {
  test_();
}

// get XPTr to fortran fct or C interface of fortran fct
// [[Rcpp::export]]
Rcpp::XPtr<fp> test_get_fortran() {
  Rcpp::XPtr<fp> xpfun = Rcpp::XPtr<fp>(new fp(&test_));

  return xpfun;
}

// call fortran fct via xptr
// [[Rcpp::export]]
void call2() {
  Rcpp::XPtr<fp> p = test_get_fortran();
  fp fc = *p;
  fc();
}



// same as call2
void test() {
  Rcpp::XPtr<fp> p = test_get_fortran();
  fp fc = *p;
  fc();
}


// this is called by fortran later
extern "C" {
  void fct(double* a, double* b) {
    test();
  }
}



extern "C" {
  void test2_();
}

// [[Rcpp::export]]
void call_fortran_which_call_fortran_via_c() {
  test2_();
}
