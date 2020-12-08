///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Main File:        cache2Dcols.c
// This File:        cache2Dcols.c
// Other Files:       
// Semester:         CS 354 Spring 2020
//
// Author:           Mei Sun
// Email:            msun252@wisc.edu
// CS Login:         sun
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
////////////////////////////////////////////////////////////////////////////////


int arr2D[3000][500];

int main(){
	for(int col = 0; col < 500; col++){
		for(int row = 0; row < 3000; row++){
			arr2D[row][col] = row + col;
		}
	}
}
