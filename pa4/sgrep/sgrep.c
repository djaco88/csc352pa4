/*
Author: Jacob Davis
Purpose:
*/

#include <stdio.h>
#include <string.h>





int checkFlags(char flagStr, int * e, int * o, int * i){
  if(flagStr == 'e'){
    *e = 1;
    return 0;
  } else if(flagStr == 'o'){
    *o = 1;
    return 0;
  } else if (flagStr == 'i'){
    *i = 1;
    return 0;
  }
  printf("ERROR: flags must be -e,-o, or -i\n");
  return 1;
}





int argOps(int argc, char * argv[], int * searchWordIndex, int * eFlag,
           int * oFlag, int * iFlag){
  int searchWordFound = 0; // flag to make sure there is only one search phrase

  for (int i = 1; i < argc; i++){
    if (argv[i][0] == '-'){
      if (strlen(argv[i]) != 2){
	printf("ERROR: flags must be one character long\n");
        return 1; // true, there is an error
      } else if (checkFlags(argv[i][1], eFlag, oFlag, iFlag) == 1){
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





int match(int lineIndex, char line[], char phrase[], int e, int i){
  int phraseIndex = 1;
  while(line[lineIndex] != '\0'){

    if (phrase[phraseIndex] == '\0'){
      return lineIndex;
    }

    else if (e == 1 && phrase[phraseIndex] == '#' && 
             phrase[phraseIndex+1] != '\0'){
      phraseIndex++;
      while(line[lineIndex] != '\0'){
        if (line[lineIndex] == phrase[phraseIndex]){
          phraseIndex++;
          break;
        }
        lineIndex++;
      }
    } 

    else if(phrase[lineIndex] == '.' && e == 1){
      phraseIndex++;
      lineIndex++;
    } 

    else if(line[lineIndex] == phrase[phraseIndex]){
      phraseIndex++;
      lineIndex++;
    } 

    else {
      return -1;
    }
  }
  return -1;
} 





int findOcc(char phrase[], int e, int o, int i, char line[],
            int * start, int * stop){
  int index = 0;
  
  while(index<strlen(line)){
    if (line[index] == '\0'){
      *stop = index;
      break;
    } 
    int result = -1;
    if (line[index] == phrase[0]){
      result = match(index+1, line, phrase, e, i);
      if(result != -1){
        if (o == 1){
          for (int j = index; j < result; j++){
            printf("%c", line[j]);
          }
          printf("\n");
          index = result;
        } else {
          printf("%s", line);
          return 0;
        }
      }
    }
    index++;
  }
  return 0;
}




int checkPhrase(char phrase[], int e){
  int index = 0;
  int flag = 0; //flag to check if there are two # in a row
  while(phrase[index] !='\0'){
    printf("%c", phrase[index]);
    // makes sure the input is '.','#', char, or int
    if (phrase[index] != '.' && phrase[index] != '#'){
      if(phrase[index] < 'a' || phrase[index] > 'z'){
        if(phrase[index] > 'Z' || phrase[index] < 'A'){
          if (phrase[index] < '0' || phrase[index] > '9'){
            printf("%c", phrase[index]);
            printf("HERE");
            return 1;
          }
          // if we dont want a number after/before a #:...............................................
          // flag = 1
        }
      }
    // if we accept '#' and '.' without the -e flag ..................................................
    // the next two if statements need to include '&& e == 1'.........................................
    }else if(phrase[index] == '#'){
      if (index == 0 || e == 0 || phrase[index + 1] == '\0'){
        return 1;
      } else if (flag == 1) {
        return 1;
      } else {
        flag = 1;
      }
    }else if (phrase[index] == '.'){
      if (flag == 1 || e == 0){
        return 1;
      } else {
        flag = 1;
      }
    } else {
      flag = 0;
    }
    index++;
  }
  return 0;
} 




int main(int argc, char * argv[]){
  if (argc < 2){
    printf("Requires more command-line arguments.\n");
    return 1;
  }
  int searchWordIndex = -1;
  int eFlag = 0;
  int oFlag = 0;
  int iFlag = 0;
  
  // decyphers argv[]. put flags in an array
  // and get the index of search phrase
  // also identifies any input errors
  if (argOps(argc, argv, &searchWordIndex, &eFlag, &oFlag, &iFlag) == 1){
    return 1;
  } else if (checkPhrase(argv[searchWordIndex], eFlag) == 1){
    printf("Invalid search term.\n");
    return 2;
  }
  
  // for testing purposes999999999999999999999999999999999999999999
  printf("Flags:\n");
  if (eFlag == 1){
    printf("c\n");
  }
  if (oFlag == 1){
    printf("o\n");
  }
  if (iFlag == 1){
    printf("i\n");
  }
  printf("Search phrase: %s\n", argv[searchWordIndex]);
  //999999999999999999999999999999999999999999999999999999999999999

  char buffer[129];
  while (fgets(buffer, 128, stdin) != NULL){
    // create indices to return a section of the
    // current line
    int start = 0;
    int stop = 127;

    findOcc(argv[searchWordIndex], eFlag, oFlag, iFlag, buffer,
            &start, &stop); 
  }
  return 0;
}

