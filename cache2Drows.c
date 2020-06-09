// File:             cache2Drows.c
// Semester:         CS 354 Fall 2019
// Author:           Ojas Rade
// Email:            rade@wisc.edu
// CS Login:         ojas
//
int a[3000][500];
int main(){
    for(int i=0;i<3000;i++){
	for(int j=0;j<500;j++){
	    a[i][j]=i+j;
	}
    }
}
