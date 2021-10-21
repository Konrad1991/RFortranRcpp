SUBROUTINE TEST(X, Y)
        
	use ISO_C_BINDING, only : C_DOUBLE, C_PTR
	IMPLICIT NONE
	REAL(C_DOUBLE), intent(out) :: X, Y	
	
	X = X + 10
	Y = Y*2
		
	print *, x
	print *, y

END SUBROUTINE
