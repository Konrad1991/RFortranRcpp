# RFortranRcpp
Testing communication between fortran, Rcpp and R

 Showing the possibility to pass Rcpp fct to fortran and vice versa.
 It is also possible to pass a fortran fct (e.g.from user) to Rcpp which afterwards can be passed to fortran.
 This is done using an external pointer and the C interface of fortran.
 
 It is also possible to pass a R function to fortran.
 
# How to pass a Fortran function to Fortran

* Define a function which should do something

```Fortran
SUBROUTINE TEST(X, Y)
        
	use ISO_C_BINDING, only : C_DOUBLE, C_PTR
	IMPLICIT NONE
	REAL(C_DOUBLE), intent(out) :: X, Y	
	
	X = X + 10
	Y = Y*2
		
	print *, x
	print *, y

END SUBROUTINE
```

* Define fortran code which calls the previously defined function
```Fortran
SUBROUTINE call_fortran2()

	use ISO_C_BINDING, only : C_CHAR, C_INT, C_FLOAT, C_DOUBLE, C_PTR
	
	IMPLICIT NONE
	REAL(C_DOUBLE) :: X, Y
	
	INTERFACE
	  SUBROUTINE fortranfct(a, b) BIND(C, name ='fct')
            import C_DOUBLE
	    REAL(C_DOUBLE) :: a, b
	  END SUBROUTINE fortranfct
	END INTERFACE
	

	X = 10.
	Y = 12.
	
	print*, X
	print*, Y
	
	
	call fortranfct(X, Y)

END SUBROUTINE
```

* Define extern C wrapper for both Fortran functions
* call the outer Fortran function via Rcpp

```C++
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
```

```r
library(fortranfctpassing)
call_fortran_which_call_fortran_via_c()
```



# Call R from Fortran

```C++
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
```

```Fortran
SUBROUTINE callr()
	use ISO_C_BINDING, only : C_DOUBLE, C_PTR
	IMPLICIT NONE

	INTERFACE
	  SUBROUTINE Rfct() BIND(C, name ='Rfctinput_')
	  END SUBROUTINE Rfct
	END INTERFACE
	
	call Rfct()

END SUBROUTINE
```



```r
hello <- function() {
  print("Hello World")
}

library(fortranfctpassing)
call_fortran_which_callsR()
```
