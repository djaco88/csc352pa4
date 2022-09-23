/*
Author: Jacob Davis
Purpose:
*/

#include <stdio.h>
#include <string.h>





int checkFlags(char flagStr, int * c, int * o, int * i){
  if(flagStr == 'c'){
    *c = 1;
    return 0;
  } else if(flagStr == 'o'){
    *o = 1;
    return 0;
  } else if (flagStr == 'i'){
    *i = 1;
    return 0;
  }
  printf("ERROR: flags must be -c,-o, or -i\n");
  return 1;
}





int argOps(int argc, char * argv[], int * searchWordIndex, int * cFlag,
           int * oFlag, int * iFlag){
  int searchWordFound = 0; // flag to make sure there is only one search phrase

  for (int i = 1; i < argc; i++){
    if (argv[i][0] == '-'){
      if (strlen(argv[i]) != 2){
	printf("ERROR: flags must be one character long\n");
        return 1; // true, there is an error
      } else if (checkFlags(argv[i][1], cFlag, oFlag, iFlag) == 1){
        return 1; // 1 is ture, there is an error
      }
    } else if (searchWordFound == 1){
      printf("ERROR: there can only be flags, one search phrase, and one file\n");
      return 1; // true, there was an error
    } else {
      searchWordFound = 1;
      *searchWordIndex = i;
    } 
  }
  return 0;
}
      




int main(int argc, char * argv[]){
  int searchWordIndex = -1;
  int cFlag = 0;
  int oFlag = 0;
  int iFlag = 0;
  
  // decyphers argv[]. put flags in an array
  // and get the index of search phrase
  // also identifies any input errors
  if (argOps(argc, argv, &searchWordIndex, &cFlag, &oFlag, &iFlag) == 1){
    return 1;
  }
  
  printf("Flags:\n");
  if (cFlag == 1){
    printf("c\n");
  }
  if (oFlag == 1){
    printf("o\n");
  }
  if (iFlag == 1){
    printf("i\n");
  }
  printf("Search phrase: %s\n", argv[searchWordIndex]);


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
  return 0;
}

