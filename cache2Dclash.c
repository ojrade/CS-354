// File:             cache2Dclash.c
// Semester:         CS 354 Fall 2019
// Author:           Ojas Rade
// Email:            rade@wisc.edu
// CS Login:         ojas


int a[128][8];
int main(){
    for(int x=0;x<100;x++){
	for(int i=0;i<128;i+=64){
	    for(int j=0;j<8;j++){
		a[i][j]=x+i+j;
	    }
	}
    }
}
