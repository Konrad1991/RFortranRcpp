#include <Rcpp.h>



/*
This will not work. Cannot be called by fortran
*/
// [[Rcpp::export]]
void Rfct(SEXP fct) {

  Rcpp::Function f = fct;
  f();
}

// R function has to be part f package
Rcpp::Environment pkg = Rcpp::Environment::namespace_env("fortranfctpassing");
Rcpp::Function f = pkg["hello"];

// [[Rcpp::export]]
void Rfct2() {
  f();
}




// this is called by fortran later
extern "C" {
  void Rfct() {
    Rfct2();
  }
}


// call fortran which calls R
extern "C" {
  void test3_();
}


// [[Rcpp::export]]
void call_fortran_which_callsR() {
  test3_();
}
