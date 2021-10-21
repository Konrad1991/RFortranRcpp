SUBROUTINE call_fortran2()

	use ISO_C_BINDING, only : C_CHAR, C_INT, C_FLOAT, C_DOUBLE, C_PTR
	
	IMPLICIT NONE
	REAL(C_DOUBLE) :: X, Y
	
	INTERFACE
	  SUBROUTINE fortranfct(a, b) BIND(C, name ='test_')
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
