/* Program to assist in the challenge of solving sudoku puzzles.

   Skeleton program written by Alistair Moffat, ammoffat@unimelb.edu.au,
   August 2021, with the intention that it be modified by students
   to add functionality, as required by the assignment specification.

   Student Authorship Declaration:

   (1) I certify that except for the code provided in the initial skeleton
   file, the  program contained in this submission is completely my own
   individual work, except where explicitly noted by further comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students, or by
   non-students as a result of request, solicitation, or payment, may not be
   submitted for assessment in this subject.  I understand that submitting for
   assessment work developed by or in collaboration with other students or
   non-students constitutes Academic Misconduct, and may be penalized by mark
   deductions, or by other penalties determined via the University of
   Melbourne Academic Honesty Policy, as described at
   https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will I
   do so until after the marks are released. I understand that providing my
   work to other students, regardless of my intention or any undertakings made
   to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring service,
   or drawing the attention of others to such services and code that may have
   been made available via such a service, may be regarded as Student General
   Misconduct (interfering with the teaching activities of the University
   and/or inciting others to commit Academic Misconduct).  I understand that
   an allegation of Student General Misconduct may arise regardless of whether
   or not I personally make use of such solutions or sought benefit from such
   actions.

   Signed by: [Can Senyurt 1079752]
   Dated:     [06/07/2021]

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* these #defines provided as part of the initial skeleton */

#define NDIM 3		/* sudoku dimension, size of each inner square */
#define NDIG (NDIM*NDIM)
			/* total number of values in each row */
#define NGRP 3		/* number of sets each cell is a member of */
#define NSET (NGRP*NDIG)
			/* total number of sets in the sudoku */
#define NCLL (NDIG*NDIG)
			/* total number of cells in the sudoku */

#define ERROR	(-1)	/* error return value from some functions */

/* these global constant arrays provided as part of the initial skeleton,
   you may use them in your code but must not alter them in any way,
   regard them as being completely fixed. They describe the relationships
   between the cells in the sudoku and provide a basis for all of the
   sudoku processing loops */

/* there are 27 different different sets of elements that need to be
   checked against each other, this array converts set numbers to cells,
   that's why its called s2c */
int s2c[NSET][NDIM*NDIM] = {
	/* the first group of nine sets describe the sudoku's rows */
	{  0,  1,  2,  3,  4,  5,  6,  7,  8 },
	{  9, 10, 11, 12, 13, 14, 15, 16, 17 },
	{ 18, 19, 20, 21, 22, 23, 24, 25, 26 },
	{ 27, 28, 29, 30, 31, 32, 33, 34, 35 },
	{ 36, 37, 38, 39, 40, 41, 42, 43, 44 },
	{ 45, 46, 47, 48, 49, 50, 51, 52, 53 },
	{ 54, 55, 56, 57, 58, 59, 60, 61, 62 },
	{ 63, 64, 65, 66, 67, 68, 69, 70, 71 },
	{ 72, 73, 74, 75, 76, 77, 78, 79, 80 },
	/* the second group of nine sets describes the sudoku's columns */
	{  0,  9, 18, 27, 36, 45, 54, 63, 72 },
	{  1, 10, 19, 28, 37, 46, 55, 64, 73 },
	{  2, 11, 20, 29, 38, 47, 56, 65, 74 },
	{  3, 12, 21, 30, 39, 48, 57, 66, 75 },
	{  4, 13, 22, 31, 40, 49, 58, 67, 76 },
	{  5, 14, 23, 32, 41, 50, 59, 68, 77 },
	{  6, 15, 24, 33, 42, 51, 60, 69, 78 },
	{  7, 16, 25, 34, 43, 52, 61, 70, 79 },
	{  8, 17, 26, 35, 44, 53, 62, 71, 80 },
	/* the last group of nine sets describes the inner squares */
	{  0,  1,  2,  9, 10, 11, 18, 19, 20 },
	{  3,  4,  5, 12, 13, 14, 21, 22, 23 },
	{  6,  7,  8, 15, 16, 17, 24, 25, 26 },
	{ 27, 28, 29, 36, 37, 38, 45, 46, 47 },
	{ 30, 31, 32, 39, 40, 41, 48, 49, 50 },
	{ 33, 34, 35, 42, 43, 44, 51, 52, 53 },
	{ 54, 55, 56, 63, 64, 65, 72, 73, 74 },
	{ 57, 58, 59, 66, 67, 68, 75, 76, 77 },
	{ 60, 61, 62, 69, 70, 71, 78, 79, 80 },
};


/* there are 81 cells in a dimension-3 sudoku, and each cell is a
   member of three sets, this array gets filled by the function 
   fill_c2s(), based on the defined contents of the array s2c[][] */
int c2s[NCLL][NGRP];

void
fill_c2s() {
	int s=0, d=0, c;
	for ( ; s<NSET; s++) {
		/* record the first set number each cell is part of */
		for (c=0; c<NDIM*NDIM; c++) {
			c2s[s2c[s][c]][d] = s;
		}
		if ((s+1)%(NGRP*NDIM) == 0) {
			d++;
		}
	}
#if 0
	/* this code available here if you want to see the array
	   cs2[][] that gets created, just change that 0 two lines back
	   to a 1 and recompile */
	for (c=0; c<NCLL; c++) {
		printf("cell %2d: sets ", c);
		for (s=0; s<NGRP; s++) {
			printf("%3d", c2s[c][s]);
		}
		printf("\n");
	}
	printf("\n");
#endif
	return;
}

/* find the row number a cell is in, counting from 1
*/
int
rownum(int c) {
	return 1 + (c/(NDIM*NDIM));
}

/* find the column number a cell is in, counting from 1
*/
int
colnum(int c) {
	return 1 + (c%(NDIM*NDIM));
}

/* find the minor square number a cell is in, counting from 1
*/
int
sqrnum(int c) {
	return 1 + 3*(c/NSET) + (c/NDIM)%NDIM;
}

/* If you wish to add further #defines, put them below this comment,
   then prototypes for the functions that you add

   The only thing you should alter above this line is to complete the
   Authorship Declaration 
*/

#include <string.h>
#define SETHAS 9 /* each set has this many elements */

/****************************************************************/

/****************************************************************/

int
strat1(int cell, int ERRORSETS[NCLL][9]){
    int set_to_check, i, potnums[9],k, pot_counter=0, return_val;

    /* using deduction, decides if an unknown cell can only take one single 
    value by checking what sets the cell is a member of, if so, returns 
    the value */

    if(cell){
        return 0;
    }

    for (i=0;i<NGRP;i++){
        set_to_check = c2s[cell][i];
        for(k=0;k<9;k++){
            if (!(ERRORSETS[set_to_check][k])){
                potnums[k] = 1;
            } else {potnums[k] = 0;}
        }
    }
    for(i=0;i<9;i++){
        if (potnums[i] == 1){
            pot_counter ++;
        }
    }
    if (pot_counter == 1){
       for(i=0;i<9;i++){
           if (potnums[i]){
               return_val = potnums[i];
           }
        return return_val;
       } 
    }
    return 0;
}


int
unknown_counter(int p1){
    /* counts the number of unknowns in NUMS */

    int j, unknowns=0;

    for(j=0;j < NCLL ;j++){
        if (!(p1+j)){
            unknowns++;
        }
    }
    return unknowns;
}


/* main program controls all the action
*/
int
main(int argc, char *argv[]) {

    fill_c2s();
    int n, *p, NUMS[NCLL], i=0, set_of_3 = 0, line = 0, no_of_unknown = 0, k;
    int set, has_error = 0, set_error = 0, set_already_count;
    static int ERRORSETS[NCLL][SETHAS] = {{0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};

    p = NUMS;

    /* stage 1 reads in the values from the given text file and imports the 
    integers into array NUMS. Then prints out the values in a nicely 
    formatted way, also counts how many unknown values there are in the
    sudoku */

    printf("\n");
    while(i<=NCLL){
        scanf("%d",&n);
        NUMS[i] = n;
        i++;
    }
    for(i=0; i<=(NCLL-3);i += 3){
        set_of_3++;
        for(k=0; k<3 ; k++){
            if (*(p+i+k) == 0){
            no_of_unknown ++;
            printf(". ");
            }else{
            printf("%d ",*(p+i+k));
            }       
        }
        if (set_of_3%3==0){
            printf("\n");
            line ++;
            if (((line)%3 == 0) && (line != 9)){
                printf("------+-------+------\n");
            }
        } else {
            printf("| ");
        }
    }

    printf("\n%d cells are unknown\n\n", no_of_unknown);

    /* stage 2 checks if the sudoku is legal by counting the amount
    of times each value is in a set, if there are any illegal values,
    prints where and what the error is */
    

    /* fills out a 2D array ERRORSETS with the amount of times a value is 
    seen in each set */

    for(set=0; set < NSET ; set++){
        for(k=0; k<SETHAS; k++){ 
            if (NUMS[s2c[set][k]] != 0){
                ERRORSETS[set][NUMS[s2c[set][k]]-1] ++;
                }   
            }  
        }

    /* if a value is seen more than once, prints out the error message */

    for(set=0; set < NSET ; set++){
        set_already_count = 0;
        for(n=0; n<SETHAS; n++){
            if(ERRORSETS[set][n] > 1){
                has_error++;
                if(!set_already_count){
                    set_already_count = 1;
                    set_error ++;
                }
                if (set < 9){
                printf("set %d (row %d): %d instances of %d\n", set, set+1,
                 ERRORSETS[set][n], n+1);
            } else if (set < 18){
                printf("set %d (col %d): %d instances of %d\n", set, set-8,
                 ERRORSETS[set][n], n+1);
            } else {
                printf("set %d (sqr %d): %d instances of %d\n", set, set-17,
                 ERRORSETS[set][n], n+1);
            }
        }
    }
    }

    if(has_error){
    printf("\n%d different sets have violations\n%d violations in total\n",
        set_error, has_error);
    }

    /* stopping the program if there is any errors */
    if(has_error){
        return 0;
    }

    /* stage 3 loops over NUMS while there still are unknown values
    and if there is an unknown value, checks whether a value can be deduced by
    using strat1 and if so, assigns the value to the cell */

    for(i=0;i < NCLL; i++){
        if(unknown_counter(*(p+i))){
            printf("strategy one\n");
            for(i=0;i < NCLL ;i++){
            NUMS[i] = strat1(i, ERRORSETS);
            }
        }
    }


	/* algorithms are fun */

	return 0;
}


/****************************************************************/

