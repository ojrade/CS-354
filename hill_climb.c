//////////////////////////////////////////////////////////////////////////////
//
// Copyright 2019 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
///////////////////////////////////////////////////////////////////////////////
// Main File:        (name of file with main function)
// This File:        (name of this file)
// Other Files:      (name of all other files if any)
// Semester:         CS 354 Fall 2019
//
// Author:           (your name)
// Email:            (your wisc email address)
// CS Login:         (your CS login name)
//
/////////////////////////// OTHER SOURCES OF HELP /////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of 
//                   of any information you find.
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>   
#include <stdlib.h>     
#include <string.h>  

char *COMMA = ",";

/*
 * USE THIS:
 * Structure representing the Matrix
 * numRows: number of rows
 * numCols: number of columns
 * matrix: 2D heap allocated array of integers
 */
typedef struct {    
    int numRows;
    int numCols;
    int **matrix;
} Matrix;

/* TODO:
 * Get the dimensions of the matrix that are on
 * the first line of the input file.
 * 
 * infp: file pointer for input file
 * nRows: pointer to number of rows in the matrix   
 * nCols: pointer to number of columns in the matrix
 */
void get_dimensions(FILE *infp, int *nRows, int *nCols) {         
    // Read the dimensions on the first line from infp
    char *line = NULL;
    size_t len = 0;
    if (getline(&line,&len,infp) == -1) {
	printf("Error in reading the file\n");
	exit(1);
    }
    char *token = NULL;
    token = strtok(line, COMMA);
    *nRows = atoi(token);
    token = strtok(NULL, COMMA);
    *nCols = atoi(token);
}            

/* TODO:
 * Continually find and print the largest neighbor
 * that is also larger than the current position
 * until nothing larger is found.       
 * 
 * outfp: file pointer for output file  
 * mstruct: pointer to the Matrix structure
 */
void hill_climb(FILE *outfp, Matrix *mstruct) {  
    int curRow=0;//current row of position being checkeed
    int curCol=0;//current column of position being checked
    int **p;//pointer to traverse through array
    p=mstruct->matrix;
    int curVal=**p;
    int maxVal=curVal;
    int check=0;
    int numRows=mstruct->numRows;
    int numCols=mstruct->numCols;

    // Write the intial starting number to outfp
       //done in loop
    // Find the largest neighbor that is also larger than the current position
    // 1  2  3
    // 4 cur 5
    // 6  7  8
    while(check!=9){
    //1
    fprintf(outfp,"%d ",curVal);
    if(curRow>0 && curCol>0){
        if(*(*(p-1)+curCol-1)>maxVal){
	    maxVal = *(*(p-1)+(curCol-1));
	    check = 1;
	}
    }
    //2
    if(curRow>0){
        if(*(*(p-1)+curCol)>maxVal){
      	    maxVal = *(*(p-1)+curCol);
            check = 2;
        }
    }
    //3
    if(curRow>0 && curCol<numCols-1){
        if(*(*(p-1)+curCol+1)>maxVal){
	    maxVal = *(*(p-1)+(curCol+1));
	    check = 3;
        }
    }
    //4
    if(curCol>0){
        if(*(*p+(curCol-1))>maxVal){
	    maxVal = *(*p+curCol-1);
	    check = 4;
        }
    }
    //5
    if(curCol<numCols-1){
        if(*(*p+(curCol+1))>maxVal){
	    maxVal = *(*p+curCol+1);
	    check = 5;
	}
    }
    //6
    if(curRow<numRows-1 && curCol>0){
        if(*(*(p+1)+curCol-1)>maxVal){
	    maxVal = *(*(p+1)+(curCol-1));
	    check = 6;
        }
    }
    //7
    if(curRow<numRows-1){
        if(*(*(p+1)+curCol)>maxVal){
	    maxVal = *(*(p+1)+curCol);
	    check = 7;
        }
    }
    //8
    if(curRow<numRows-1 && curCol<numCols-1){
        if(*(*(p+1)+curCol+1)>maxVal){
	    maxVal = *(*(p+1)+(curCol+1));
	    check = 8;
        }
    }
    // Move to that position  
    switch(check){
	case 1:
	    p--;
	    curRow--;
	    curCol--;
	    break;
	case 2:
	    p--;
	    curRow--;
	    break;
	case 3:
	    p--;
	    curRow--;
	    curCol++;
	    break;
	case 4:
	    curCol--;
	    break;
	case 5:
	    curCol++;
	    break;
	case 6:
	    p++;
	    curRow++;
	    curCol--;
      	    break;
	case 7:
	    p++;
	    curRow++;
	    break;
	case 8:
	    p++;
	    curRow++;
	    curCol++;
            break;
       default:
	    printf("Already highest value");
	    break;	   
    }
    // Write that number to outfp
    // Done at beginning
    if(curVal == maxVal){
	break;
    }
    // Repeat until you can't find anything larger (you may use any loop)
    curVal = maxVal;
    }
}    

/* TODO:
 * This program reads an m by n matrix from the input file
 * and outputs to a file the path determined from the
 * hill climb algorithm.    
 *
 * argc: CLA count
 * argv: CLA values
 */
int main(int argc, char *argv[]) {
    // Check if number of command-line arguments is correct
    if(argc != 3) {
	printf("Not the correct number of command-line arguments\n");
    }
    
    // Open the input file and check if it opened successfully
    FILE *infp = fopen(*(argv + 1),"r");
    if(infp == NULL) {
	printf("Cannot open file for reading\n");
        exit(1);
    }
    
    // Declare local variables including the Matrix structure
    Matrix mtx;
    int **p;//used to traverse through board, points to first array in board


    // Call the function get_dimensions
    get_dimensions(infp, &(mtx.numRows),&(mtx.numCols));
    
    // Dynamically allocate a 2D array in the Matrix structure
    mtx.matrix = (int**)malloc(sizeof(int*)*(mtx.numRows));
    for(int i=0;i<mtx.numRows;i++){
	mtx.matrix[i] = (int*)malloc(sizeof(int)*(mtx.numCols));
    }

    // Read the file line by line base on the number of rows 
    // Tokenize each line wrt comma to store the values in the matrix
    char *line = NULL;//Line to be read
    size_t len = 0;
    char *token = NULL;//Current token to be added
    p=mtx.matrix;
    for(int i=0;i<mtx.numRows;i++){
	if(getline(&line,&len,infp)==-1){
	    printf("Error while reading the file22\n");
	    exit(1);
	}
	token = strtok(line,COMMA);
	for(int j=0;j<mtx.numCols;j++){
	    *(*(p+i)+j)=atoi(token);
	    token=strtok(NULL,COMMA);
	}
    }   

    // Open the output file  
    FILE *outfp = fopen(*(argv+2),"w");
    if(outfp==NULL){
	printf("Cannot open file for writing\n");
	exit(1);
    }
    
    // Call the function hill_climb
    hill_climb(outfp,&mtx); 
    fprintf(outfp,"\n");

    // Free the dynamically allocated memory
    free(mtx.matrix);
    
    // Close the input file  
    if(fclose(infp) != 0){
	printf("Error while closing input file\n");
    }
    
    // Close the output file
    if(fclose(outfp) != 0){
	printf("Error while closing output file\n");
    }
    
    return 0; 
}  
