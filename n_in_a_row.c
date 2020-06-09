///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2019 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        n_in_a_row.c
// This File:        n_in_a_row.c
// Other Files:      none
// Semester:         CS 354 Fall 2019
//
// Author:           Ojas Rade
// Email:            rade@wisc.edu
// CS Login:         ojas
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          None
//                  
//
// Online sources:   None
//                  
//                                     
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>  
#include <stdlib.h>
#include <string.h>     

char *COMMA = ",";  

/* COMPLETED:       
 * Retrieves from the first line of the input file,
 * the size of the board (number of rows and columns).
 * 
 * fp: file pointer for input file
 * size: pointer to size
 */
void get_dimensions(FILE *fp, int *size) {      
    char *line = NULL;
    size_t len = 0;
    if (getline(&line, &len, fp) == -1) {
        printf("Error in reading the file\n");
        exit(1);
    }

    char *token = NULL;
    token = strtok(line, COMMA);
    *size = atoi(token);
}   

/*
 * Helper method which checks if the colums is in a row
 *
 * col: starting point
 * XO: x or o
 * size: 
 */
int colCheck(int **board, int col, int XO, int size){
    int **p;
    p = board;
    for(int i=0;i<size;i++){
	if(*(*(p+i)+col) != XO){
	    return 0;
	}
    }
    return 1;
}

/*
 * Helper method to check if a row is in a row
 *
 * row: start point
 * XO: if x or o
 * size: size of table
 */
int rowCheck(int **board, int row, int XO, int size){
    int **p;
    p = board;
    for(int i=0;i<size;i++){
	 if(*(*(p+row)+i) != XO){
	      return 0;
	 }
    }
    return 1;    
}

/*
 * Helper method to check if a Diagnol from left to right is in a row
 *
 * diag: start point
 * XO: if x or o
 * size: size of table
 * 
 */
int diagCheckLR(int **diag, int XO, int size){
    int **p;
    p = diag;
    for(int i=0;i<size;i++){
	if(*(*(p+i)+i) != XO){
	    return 0;
	}
    }
    return 1;
}

/*
 * Helper method to check Diagonal from right to left is in a row
 *
 * diag: start point
 * XO: if x or o
 * size: size of table
 */
int diagCheckRL(int **diag, int XO, int size){
    int **p;
    p = diag;
    int j = 0;
    for(int i=size-1; i>=0;i--){
	if(*(*(p+i)+j) != XO){
	    return 0;
	}
	j++;
    }
    return 1;
}



/* TODO:
 * Returns 1 if and only if the board is in a valid state.
 * Otherwise returns 0.
 * 
 * board: heap allocated 2D board
 * size: number of rows and columns
 */
int n_in_a_row(int **board, int size) {
    int winners = 0;//row of X's or 1
    int invalid = 0;
    int x = 0;
    int o = 0;
    int **p;
    p = board;
    //1 or 0  more X than O 
    for(int i=0;i<size;i++){
	for (int j=0;j<size;j++){
	    if(*(*(p+i)+j) == 1){
	    	x++;
	    }     
	    if(*(*(p+i)+j) == 2){
		o++;
	    }    
	}
    }
    if(x-o>1 || x-o<0 ){
	 return invalid;
    }

    //Checking columns
    p = board;
    for(int i=0;i<size;i++){
	if(*(*p+i) == 1){
	    if(colCheck(board,i,1,size)==1){
		winners++;	
	    }
	}else if(*(*p+i) ==2){
	    if(colCheck(board,i,2,size)==1){
		winners++;
	    }
	}
    }

    //Checking rows
    p = board;

    for(int i=0;i<size;i++){
	if(**(p+i) == 1){
	    **p = **(p+i);
	    if(rowCheck(board,i,1,size)==1){
		winners++;
	    }
	}else if(**(p+i) == 2){
	    if(rowCheck(board,i,2,size)==1){
	        winners++;
	    }
	}
    }

    //Checking diagnols
    p = board;
    if(**p == 1){
	if(diagCheckLR(board,1,size)==1){
	    	winners++;
	}
    }
    if(**p == 2){
	if(diagCheckLR(board,2,size)==1){
	    winners++;
	}
    }
    **p = *(*p+size-1);
    if(**p == 1){
	if(diagCheckRL(p,1,size)==1){
	    winners++;
	}
    }
    if(**p == 2){
	if(diagCheckRL(p,2,size)==1){
	    winners++;
	}
    }
    if(winners > 1){
	    return invalid;
    }
    return 1;    
   
}     

/* PARTIALLY COMPLETED:
 * This program prints Valid if the input file contains
 * a game board with either 1 or no winners; and where
 * there is at most 1 more X than O.
 * 
 * argc: CLA count
 * argv: CLA value
 */
int main(int argc, char *argv[]) {              

    //Check if number of command-line arguments is correct.
    if (argc != 2) {
    	printf("Not the correct number of command-line arguments");
    }	

    //Open the file and check if it opened successfully.
    FILE *fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        printf("Cannot open file for reading\n");
        exit(1);
    }


    //Declare local variables.
    int size;

    //TODO: Call get_dimensions to retrieve the board size.
     get_dimensions(fp,&size);	
    
    //TODO: Dynamically allocate a 2D array of dimensions retrieved above.
    int **board = malloc(sizeof(int*)*size);
    for(int i=0;i<size;i++){
	   board[i] = malloc(sizeof(int)*size);
    } 

    //Read the file line by line.
    //Tokenize each line wrt comma to store the values in your 2D array.
    char *line = NULL;
    size_t len = 0;
    char *token = NULL;
    int  **p;
    p=board;
    for(int i=0;i<size;i++){
        if(getline(&line, &len, fp) == -1) {
            printf("Error while reading the file\n");
            exit(1);
	}
        token = strtok(line, COMMA);
        for(int j = 0; j < size; j++) {  
       	    *(*(p+i)+j)  = atoi(token);
            token = strtok(NULL, COMMA);
        }
    }
    //TODO: Call the function n_in_a_row and print the appropriate
    //output depending on the function's return value.
    int valid = n_in_a_row(board, size);
    if(valid == 0){
	printf("invalid\n");
    }else{
	printf("valid\n");
    }

    //TODO: Free all dynamically allocated memory.
    free(board);

    //Close the file.
    if (fclose(fp) != 0) {
        printf("Error while closing the file\n");
        exit(1);
    } 
 
    return 0;       
}       
