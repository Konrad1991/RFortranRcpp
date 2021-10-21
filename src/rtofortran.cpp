#include <Rcpp.h>

// [[Rcpp::export]]
void Rfct2() {
  // Has to be in function if the function is not defined in a package
  Rcpp::Environment global = Rcpp::Environment::global_env();
  Rcpp::Function hello = global.get("hello");
  hello();
}

// this is called by fortran later
extern "C" {
  void Rfctinput_() {
    Rfct2();
  }
}


// call fortran which calls R
extern "C" {
  void callr_();
}


// [[Rcpp::export]]
void call_fortran_which_callsR() {
  callr_();
}
