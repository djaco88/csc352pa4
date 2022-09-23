/*
Author: Jacob Davis
Purpose:
*/

#include <stdio.h>
#include <string.h>





int argOps(int argc, char * argv[], char flags[], int * searchWordIndex){
  int flagsIndex = 0;
  int searchWordFound = 0; // flag to make sure there is only one search phrase

  for (int i = 1; i < argc; i++){
    if (argv[i][0] == '-'){
      if (strlen(argv[i]) != 2){
        printf("ERROR: flags must be one character long");
        return 1; // 1 is true, meaning there was an error
      }
      flags[flagsIndex] = argv[i][1];
      flagsIndex++;
      flags[flagsIndex] = '\n';
    } else if (searchWordFound == 1){
      printf("ERROR: there can only be flags, one search phrase, and one file");
      return 1; // true, there was an error
    } else {
      *searchWordIndex = i;
    } 
  }
  return 0;
}
      
     





int main(int argc, char * argv[]){
  char flags[argc-1];
  flags[0]='\n'; // flag to mark the end of the funtions
  int searchWordIndex = -1;
  
  // decyphers argv[]. put flags in an array
  // and get the index of search phrase
  if (argOps(argc, argv, flags, &searchWordIndex) == 1){
    return 1;
  }
  
  printf("Flags:\n");
  for (int i = 0; i < strlen(flags); i++){
    if (flags[i] == '\n'){
      break;
    }
    printf("%c\n", flags[i]);
  }
  printf("Search phrase: %s\n", argv[searchWordIndex]);
  return 0;// move this

  // TODO: check for valid flags
  // checkFLags();

/* 
  //get input and send to appropriate function
  char buffer[129];
  while (fgets(buffer, 128, stdin) != NULL){
    if (delim == 'l'){
      l(buffer, cols);
    } else {
      wAndC(buffer, cols, delim);
    }
  }
*/ 
}

