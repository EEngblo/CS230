/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 *
 * by CS20160385 Jinyoung Oh
 *
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);
void tr_32(int M, int N, int A[N][M], int B[M][N]);
void tr_64(int M, int N, int A[N][M], int B[M][N]);
void tr_61(int M, int N, int A[N][M], int B[M][N]);
void tr_8(int M, int N, int A[N][M], int B[M][N]);
/* 
 *
 transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */

void tr_8(int M, int N, int A[N][M], int B[M][N]){

        int row, col, bigrow, bigcol, diagonal;
        for(bigrow = 0; bigrow < 1; bigrow++){
                for(bigcol = 0; bigcol < 2; bigcol++){
                        for(row = 8*bigrow; row < 8*bigrow + 8; row++){
                                for(col = 8*bigcol; col < 8*bigcol + 8; col++){
                                        if(row == col) diagonal = A[row][col];
                                        else B[col][row] = A[row][col];
                                }
                                if (bigrow == bigcol) B[row][row] = diagonal;
                        }
                }
        }
}


void tr_32(int M, int N, int A[N][M], int  B[M][N]){
        int row, col, bigrow, bigcol, diagonal;
        for(bigrow = 0; bigrow < 4; bigrow++){
                for(bigcol = 0; bigcol < 4; bigcol++){
                        for(row = 8*bigrow; row < 8*bigrow + 8; row++){
                                for(col = 8*bigcol; col < 8*bigcol + 8; col++){
                                        if(row == col) diagonal = A[row][col];
                                        else B[col][row] = A[row][col];
                                }
                                if (bigrow == bigcol) B[row][row] = diagonal;
                        }
                }
        }
}


void tr_61(int M, int N, int A[N][M], int B[M][N]) {

	int row, col, bigrow, bigcol, diagonal;

	for (bigrow = 0; bigrow < 5; bigrow++) {
		for (bigcol = 0; bigcol < 4; bigcol++) {
			for (row = 16 * bigrow; row < 16 * bigrow + 16 && row < N; row++) {
				for (col = 16 * bigcol; col < 16 * bigcol + 16 && col < M; col++) {
					if (row == col && bigrow == bigcol) diagonal = A[row][col];
					else B[col][row] = A[row][col];


				}
				if (bigrow == bigcol) B[row][row] = diagonal;
			}




		}
	
	
	}
}




void tr_64(int M, int N, int A[N][M], int  B[M][N]){
        int row, col, bigrow, bigcol, diagonal;
        for(bigrow = 0; bigrow < 16; bigrow++){
                for(bigcol = 0; bigcol < 16; bigcol++){
                        for(row = 4*bigrow; row < 4*bigrow + 4; row++){
                                for(col = 4*bigcol; col < 4*bigcol + 4; col++){
                                        if(row == col) diagonal = A[row][col];
                                        else B[col][row] = A[row][col];
                                }
                                if (bigrow == bigcol) B[row][row] = diagonal;
                        }
                }
        }

}

void tr_64_h(int M, int N, int A[N][M], int  B[M][N]) {
	int index, bigrow, bigcol;
	int r1, r2, r3, r4, r5, r6, r7, r8, r9;
	for (bigrow = 0; bigrow < 8; bigrow++) {
		for (bigcol = 0; bigcol < 8; bigcol++) {
			for (index = 0; index < 4; index++) {

				r1 = A[8 * bigrow + index][8 * bigcol];
				r2 = A[8 * bigrow + index][8 * bigcol + 1];
				r3 = A[8 * bigrow + index][8 * bigcol + 2];
				r4 = A[8 * bigrow + index][8 * bigcol + 3];
				r5 = A[8 * bigrow + index][8 * bigcol + 4];
				r6 = A[8 * bigrow + index][8 * bigcol + 5];
				r7 = A[8 * bigrow + index][8 * bigcol + 6];
				r8 = A[8 * bigrow + index][8 * bigcol + 7];

				B[8 * bigcol][8 * bigrow + index] = r1;
				B[8 * bigcol + 1][8 * bigrow + index] = r2;
				B[8 * bigcol + 2][8 * bigrow + index] = r3;
				B[8 * bigcol + 3][8 * bigrow + index] = r4;
				B[8 * bigcol][8 * bigrow + index + 4] = r5;
				B[8 * bigcol + 1][8 * bigrow + index + 4] = r6;
				B[8 * bigcol + 2][8 * bigrow + index + 4] = r7;
				B[8 * bigcol + 3][8 * bigrow + index + 4] = r8;

			}

			for (index = 0; index < 4; index += 2) {
				r1 = B[8 * bigcol + index][8 * bigrow + 4];
				r2 = B[8 * bigcol + index][8 * bigrow + 5];
				r3 = B[8 * bigcol + index][8 * bigrow + 6];
				r4 = B[8 * bigcol + index][8 * bigrow + 7];
				r5 = B[8 * bigcol + 1 + index][8 * bigrow + 4];
				r6 = B[8 * bigcol + 1 + index][8 * bigrow + 5];
				r7 = B[8 * bigcol + 1 + index][8 * bigrow + 6];
				r8 = B[8 * bigcol + 1 + index][8 * bigrow + 7];

				B[8 * bigcol + index][8 * bigrow + 4] = A[8 * bigrow + 4][8 * bigcol + index];
				B[8 * bigcol + index][8 * bigrow + 5] = A[8 * bigrow + 5][8 * bigcol + index];
				B[8 * bigcol + index][8 * bigrow + 6] = A[8 * bigrow + 6][8 * bigcol + index];
				B[8 * bigcol + index][8 * bigrow + 7] = A[8 * bigrow + 7][8 * bigcol + index];
				B[8 * bigcol + 1 + index][8 * bigrow + 4] = A[8 * bigrow + 4][8 * bigcol + 1 + index];
				B[8 * bigcol + 1 + index][8 * bigrow + 5] = A[8 * bigrow + 5][8 * bigcol + 1 + index];
				B[8 * bigcol + 1 + index][8 * bigrow + 6] = A[8 * bigrow + 6][8 * bigcol + 1 + index];
				B[8 * bigcol + 1 + index][8 * bigrow + 7] = A[8 * bigrow + 7][8 * bigcol + 1 + index];

				B[8 * bigcol + 4 + index][8 * bigrow] = r1;
				B[8 * bigcol + 4 + index][8 * bigrow + 1] = r2;
				B[8 * bigcol + 4 + index][8 * bigrow + 2] = r3;
				B[8 * bigcol + 4 + index][8 * bigrow + 3] = r4;
				B[8 * bigcol + 5 + index][8 * bigrow] = r5;
				B[8 * bigcol + 5 + index][8 * bigrow + 1] = r6;
				B[8 * bigcol + 5 + index][8 * bigrow + 2] = r7;
				B[8 * bigcol + 5 + index][8 * bigrow + 3] = r8;

			}




			r1 = A[bigrow * 8+4][bigcol * 8 + 4];
			r2 = A[bigrow * 8 + 4][bigcol * 8 + 4 + 1];
			r3 = A[bigrow * 8 + 4][bigcol * 8 + 4 + 2];
			r4 = A[bigrow * 8 + 4][bigcol * 8 + 4 + 3];
			r5 = A[bigrow * 8 + 4 + 1][bigcol * 8 + 4];
			r6 = A[bigrow * 8 + 4 + 1][bigcol * 8 + 4 + 1];
			r7 = A[bigrow * 8 + 4 + 1][bigcol * 8 + 4 + 2];
			r8 = A[bigrow * 8 + 4 + 1][bigcol * 8 + 4 + 3];
			r9 = A[bigrow * 8 + 4 + 2][bigcol * 8 + 4];
			index = A[bigrow * 8 + 4 + 2][bigcol * 8 + 4 + 1];

			B[bigcol * 8 + 4][bigrow * 8 + 4] = r1;
			B[bigcol * 8 + 4][bigrow * 8 + 4 + 1] = r5;
			B[bigcol * 8 + 4][bigrow * 8 + 4 + 2] = r9;
			B[bigcol * 8 + 4 + 1][bigrow * 8 + 4] = r2;
			B[bigcol * 8 + 4 + 1][bigrow * 8 + 4 + 1] = r6;
			B[bigcol * 8 + 4 + 1][bigrow * 8 + 4 + 2] = index;


			r1 = A[bigrow * 8 + 4 + 3][bigcol * 8 + 4];
			r2 = A[bigrow * 8 + 4 + 3][bigcol * 8 + 4 + 1];
			r9 = A[bigrow * 8 + 4 + 3][bigcol * 8 + 4 + 2];
			r5 = A[bigrow * 8 + 4 + 3][bigcol * 8 + 4 + 3];
			r6 = A[bigrow * 8 + 4 + 2][bigcol * 8 + 4 + 2];
			index = A[bigrow * 8 + 4 + 2][bigcol * 8 + 4 + 3];

			B[bigcol * 8 + 4 + 2][bigrow * 8 + 4] = r3;
			B[bigcol * 8 + 4 + 2][bigrow * 8 + 4 + 1] = r7;
			B[bigcol * 8 + 4 + 2][bigrow * 8 + 4 + 2] = r6;


			B[bigcol * 8 + 4][bigrow * 8 + 4 + 3] = r1;
			B[bigcol * 8 + 4 + 1][bigrow * 8 + 4 + 3] = r2;
			B[bigcol * 8 + 4 + 2][bigrow * 8 + 4 + 3] = r9;
			B[bigcol * 8 + 4 + 3][bigrow * 8 + 4 + 3] = r5;
			B[bigcol * 8 + 4 + 3][bigrow * 8 + 4 + 2] = index;
			B[bigcol * 8 + 4 + 3][bigrow * 8 + 4 + 1] = r8;
			B[bigcol * 8 + 4 + 3][bigrow * 8 + 4] = r4;


/*
			for (index = 0; index < 4; index++) {
				B[8 * bigcol + 4 + index][8 * bigrow + 4] = A[8 * bigrow + 4][8 * bigcol + 4 + index];
				B[8 * bigcol + 4 + index][8 * bigrow + 5] = A[8 * bigrow + 5][8 * bigcol + 4 + index];
				B[8 * bigcol + 4 + index][8 * bigrow + 6] = A[8 * bigrow + 6][8 * bigcol + 4 + index];
				B[8 * bigcol + 4 + index][8 * bigrow + 7] = A[8 * bigrow + 7][8 * bigcol + 4 + index];

				//if (bigcol == bigrow) {
				//	diag = A[8 * bigrow + 4 + index][8 * bigcol + 4 + index];
				//}
				//else {
				//	B[8 * bigcol + 4 + index][8 * bigrow + 4 + index] = A[8 * bigrow + 4 + index][8 * bigcol + 4 + index];
				//}

			
			}
*/		}
	}
}


void tr_64_f(int M, int N, int A[N][M], int  B[M][N]) {
	int row,  bigrow, bigcol;
	int r1, r2, r3, r4;// r5, r6, r7, r8;
	for (bigrow = 0; bigrow < 16; bigrow++) {
		for (bigcol = 0; bigcol < 16; bigcol++) {
			for (row = 4 * bigrow; row < 4 * bigrow + 4; row++) {
				r1 = A[row][4 * bigcol];
				r2 = A[row][4 * bigcol+1];
				r3 = A[row][4 * bigcol+2];
				r4 = A[row][4 * bigcol+3];
				//r5 = A[row][8 * bigcol+4];
			//	r6 = A[row][8 * bigcol+5];
		//		r7 = A[row][8 * bigcol+6];
		//		r8 = A[row][8 * bigcol+7];

				B[4 * bigcol][row] = r1;
				B[4 * bigcol+1][row] = r2;
				B[4 * bigcol+2][row] = r3;
				B[4 * bigcol+3][row] = r4;
		//		B[8 * bigcol+4][row] = r5;
		//		B[8 * bigcol+5][row] = r6;
		//		B[8 * bigcol+6][row] = r7;
		//		B[8 * bigcol+7][row] = r8;

			}
		}

	}
} 

void tr_64_e(int M, int N, int A[N][M], int  B[M][N]){
        int row, col, bigrow, bigcol;//, diagonal;
        for(bigrow = 0; bigrow < 16; bigrow++){
                for(bigcol = 0; bigcol < 7; bigcol++){
                        for(row = 4*bigrow; row < 4*bigrow + 4; row++){
                                for(col = 8*bigcol; col < 8*bigcol + 8; col++){
                                       // if(row == col) diagonal = A[row][col];
                                        B[row][col+8] = A[row][col];
                                }



                                //if (bigrow == bigcol) B[row][row] = diagonal;
                        }
                }
        }





	for (bigrow = 0; bigrow < 8 /**/ - 1; bigrow++) {
		for (col = 8 * bigrow; col < 56; col++) {
			for (row = 8 * bigrow; row < 8 * bigrow + 8; row++) {
			/*	if (B[row][col + 8] != row + col*0.01) {
					B[col][row] = 0;
					printf("%d %d \n", bigcol, bigrow);
				} else*/	B[col][row] = B[row][col + 8];

			}
		}

		for (col = 8 * bigrow; col < 8 * bigrow + 8; col++) {
			for (row = 8 * bigrow + 8; row < 64; row++) {
		/*		if (B[row][col + 8] != row + col*0.01) {
					B[col][row] = 0;
					printf("%d %d \n", bigcol, bigrow);
				}
				else	*/B[col][row] = B[row][col + 8];
			}
		}
	}

/*
        for(bigrow = 0; bigrow < 8; bigrow++){
                for(bigcol = 0; bigcol < 7; bigcol++){
                        for(row = 4*bigrow; row < 4*bigrow + 4; row++){
				for(col = 8*bigcol; col < 8*bigcol + 8; col++){
					B[col][row] = B[row][col+8];
				}
                                //if (bigrow == bigcol) B[row][row] = diagonal;
                        }
                }
        }
	
*/

	for(bigrow = 0; bigrow < 8; bigrow++){
		bigcol = 7;
			for(row = 8*bigrow; row<8*bigrow+8; row++){
				for(col = 8*bigcol; col < 8*bigcol + 8; col++){

					B[col][row] = A[row][col];
				}
			}
		
		
	}

}



void tr_64_d(int M, int N, int A[N][M], int  B[M][N]){
int row, col, bigrow, bigcol, diagonal;
for(bigrow = 0; bigrow < 4; bigrow++){
	for(bigcol = 0; bigcol < 4; bigcol++){
		for(row = 16*bigrow; row < 16*bigrow + 16; row++){
			for(col = 16*bigcol; col < 16*bigcol + 16; col++){
				if(row == col) diagonal = A[row][col];
				else B[col][row] = A[row][col];
			}
			if (bigrow == bigcol) B[row][row] = diagonal;
		}
	}
}

}

void tr_64_c(int M, int N, int A[N][M], int B[M][N]){
	int bigrow, bigcol;
	int r1, r2, r3, r4, r5, r6,r7,r8, r9, r10;

	for(bigrow = 0; bigrow < 16; bigrow++){
		for(bigcol = 0; bigcol < 16; bigcol++){
			r1 = A[bigrow*4][bigcol*4];
			r2 = A[bigrow*4][bigcol*4+1];
			r3 = A[bigrow*4][bigcol*4+2];
			r4 = A[bigrow*4][bigcol*4+3];
			r5 = A[bigrow*4+1][bigcol*4];
			r6 = A[bigrow*4+1][bigcol*4+1];
			r7 = A[bigrow*4+1][bigcol*4+2];
			r8 = A[bigrow*4+1][bigcol*4+3];
			r9 = A[bigrow*4+2][bigcol*4];
			r10 = A[bigrow*4+2][bigcol*4+1];
			
			B[bigcol*4][bigrow*4] = r1;
			B[bigcol*4][bigrow*4+1] = r5;
			B[bigcol*4][bigrow*4+2] = r9;
			B[bigcol*4+1][bigrow*4] = r2;
			B[bigcol*4+1][bigrow*4+1] = r6;
			B[bigcol*4+1][bigrow*4+2] = r10;
	
	
			r1 = A[bigrow*4+3][bigcol*4];
			r2 = A[bigrow*4+3][bigcol*4+1];
			r9 = A[bigrow*4+3][bigcol*4+2];
			r5 = A[bigrow*4+3][bigcol*4+3];
			r6 = A[bigrow*4+2][bigcol*4+2];
			r10 = A[bigrow*4+2][bigcol*4+3];			
	
			B[bigcol*4+2][bigrow*4] = r3;
			B[bigcol*4+2][bigrow*4+1] = r7;
			B[bigcol*4+2][bigrow*4+2] = r6;
	
			
			B[bigcol*4][bigrow*4+3] = r1;
			B[bigcol*4+1][bigrow*4+3] = r2;
			B[bigcol*4+2][bigrow*4+3] = r9;
			B[bigcol*4+3][bigrow*4+3] = r5;
			B[bigcol*4+3][bigrow*4+2] = r10;
			B[bigcol*4+3][bigrow*4+1] = r8;
			B[bigcol*4+3][bigrow*4] = r4;

		}
	}

}

void tr_64_b(int M, int N, int A[N][M], int B[M][N]){
	int row, col, bigrow, bigcol;
	int r1, r2, r3, r4, r5, r6, r7, r8;

	for(bigrow = 0; bigrow < 16; bigrow++){
		for(bigcol = 0; bigcol < 8; bigcol++){
			for(row = 4*bigrow; row < 4*bigrow +4; row++){
				if (bigrow % 2 == 0){
					for(col = 8*bigcol; col < 8*bigcol + 4; col++){
						B[col][row] = A[row][col];
	//					printf("aaaaaaaaaaaaaa");
					}
	//				printf("\n");
					if (row == 4*bigrow){
						r1 = A[row][8*bigcol + 4];
						r2 = A[row][8*bigcol + 5];
						r3 = A[row][8*bigcol + 6];
						r4 = A[row][8*bigcol + 7];
					} else if (row == 4*bigrow + 1){
						r5 = A[row][8*bigcol + 4];
						r6 = A[row][8*bigcol + 5];
						r7 = A[row][8*bigcol + 6];
						r8 = A[row][8*bigcol + 7];
					} else if (row == 4*bigrow + 2){
						B[8*bigcol + 4][4*bigrow] = r1;
						B[8*bigcol + 5][4*bigrow] = r2;
						B[8*bigcol + 4][4*bigrow+1] = r5;
						B[8*bigcol + 5][4*bigrow+1] = r6;
						
						r1 = A[row][8*bigcol + 4];
						r2 = A[row][8*bigcol + 5];
						r5 = A[row][8*bigcol + 6];
						r6 = A[row][8*bigcol + 7];
						
					} else {
						B[8*bigcol + 6][4*bigrow] = r3;
						B[8*bigcol + 6][4*bigrow + 1] = r7;
						B[8*bigcol + 4][4*bigrow + 2] = r1;
						B[8*bigcol + 5][4*bigrow + 2] = r2;
						B[8*bigcol + 6][4*bigrow + 2] = r5;


						r1 = A[row][8*bigcol + 4];
						r2 = A[row][8*bigcol + 5];
						r3 = A[row][8*bigcol + 6];
						r5 = A[row][8*bigcol + 7];

						B[8*bigcol + 4][4*bigrow + 3] = r1;
						B[8*bigcol + 5][4*bigrow + 3] = r2;
						B[8*bigcol + 6][4*bigrow + 3] = r3;
						B[8*bigcol + 7][4*bigrow + 3] = r5;
						B[8*bigcol + 7][4*bigrow + 2] = r6;
						B[8*bigcol + 7][4*bigrow + 1] = r8;
						B[8*bigcol + 7][4*bigrow]     = r4;

					}	
				} else{
	//				printf("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb\n");
					for(col = 8*bigcol; col < 8*bigcol+8; col++){
						B[col][row] = A[row][col];
					}
				}
			}
		}
	}
	
}



char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N]){
	
	switch(N){
		case 8 : tr_8(M,N,A,B); break;
		case 32 : tr_32(M,N,A,B); break;
		case 64 : tr_64_h(M,N,A,B); break;
		case 67 : tr_61(M,N,A,B); break;
	
	}

	return;
	int row, col, bigrow, bigcol,diagonal;
	int size = M / 4;	
	for(bigrow = 0; bigrow<size; bigrow++){
		for(bigcol = 0; bigcol<size; bigcol++){
			for(row = 4*bigrow; row < 4*bigrow + 4; row++){
				for(col = 4*bigcol; col < 4*bigcol + 4; col++){
					if(row == col) diagonal = A[row][col];
					else B[col][row] = A[row][col];
				}
				if(bigrow == bigcol) B[row][row] = diagonal;
			}
		}
	}

}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

