/*
Author: Jacob Davis
Purpose:
*/

#include <stdio.h>;

int getArgs(int argc, char * argv[], char funcs[], int * searchWordIndex){
  for (int i = 1; i < argc; i++){
    if (argv[i][0] == '-'){
     





int main(int argc, char * argv[])
  char funcs[4];
  funcs[0]='\n'; // flag to mark the end of the funtions
  int searchWordIndex = -1;
  
  // decyphers argv[]
  getArgs(argc, argv, funcs, &searchWordIndex) 
  //get input and send to appropriate function
  char buffer[129];
  while (fgets(buffer, 128, stdin) != NULL){
    if (delim == 'l'){
      l(buffer, cols);
    } else {
      wAndC(buffer, cols, delim);
    }
  } 
  return 0;a
}

