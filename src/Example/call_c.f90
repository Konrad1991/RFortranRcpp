MODULE MULTIPLY

	use ISO_C_BINDING, only : C_CHAR, C_INT, C_FLOAT, C_DOUBLE, C_PTR
	IMPLICIT NONE
	REAL*8 X, Y

	INTERFACE
	  SUBROUTINE addnums(a, b) BIND(C, name ='fct')
            import C_DOUBLE
	    REAL(C_DOUBLE) :: a, b
	  END SUBROUTINE addnums
	END INTERFACE
END MODULE


SUBROUTINE TEST2()
	
	use MULTIPLY 
        IMPLICIT NONE
	
	X = 10.
	Y = 12.
	
	call addnums(X, Y)
	
	print *, x
	print *, y

END SUBROUTINE
