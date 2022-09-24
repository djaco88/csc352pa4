/*
Author: Jacob Davis
Purpose: Simulate the grep bash command, supporting
flags: -o, -e, -i
*/

#include <stdio.h>
#include <string.h>




// Checks to make sure only valid (e, o, i)
// flags are given. Also stores 1 occurrence 
// of the flag
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





// Goes through the given args and checks for correctness
// Finds the index of the search phrase
int argOps(int argc, char * argv[], int * searchWordIndex, int * eFlag,
           int * oFlag, int * iFlag){
  int searchWordFound = 0; // flag to make sure there is only one search phrase

  for (int i = 1; i < argc; i++){
    // check flags
    if (argv[i][0] == '-'){
      if (strlen(argv[i]) != 2){
	printf("ERROR: flags must be one character long\n");
        return 1; // true, there is an error
      } else if (checkFlags(argv[i][1], eFlag, oFlag, iFlag) == 1){
        return 1; // 1 is true, there is an error
      }
    } 
    // checks that there is only one search phrase
    else if (searchWordFound == 1){
      printf("ERROR: there can only be flags, one search phrase, and one file\n");
      return 1; // true, there was an error
    } 
    // find the searchword
    else {
      searchWordFound = 1;
      *searchWordIndex = i;
    } 
  }
  return 0;
}





// Turns any lowercase letter into a capital letter
char allCaps(char x){
  if (x >= 97 && 122 >= x){
      x = x - 32;
  }
  return x;
}





// if the first letter of the search phrase is found
// this function will loop through the current line
// and search phrase for a match. All -e special
// characters are handled here
int match(int lineIndex, char line[], char phrase[], int e, int i){
  int phraseIndex = 1;

  while(line[lineIndex] != '\0'){
    // handle the -i case
    char lineChar = line[lineIndex];
    char phraseChar = phrase[phraseIndex];
    if (i == 1){
      lineChar = allCaps(lineChar);
      phraseChar = allCaps(phraseChar);
    }

    // matched word found, returns the 
    // current index of the line
    if (phrase[phraseIndex] == '\0'){
      return lineIndex;
    }

    // handles -e '#' case
    else if (e == 1 && phraseChar == '#' && 
             phrase[phraseIndex+1] != '\0'){
      // update -i case
      phraseIndex++;
      phraseChar = phrase[phraseIndex];
      if (i == 1){
	phraseChar = allCaps(phraseChar);
      }
      // loop until mismatch or match
      while(lineChar != '\0'){
        if (lineChar == phraseChar){
          phraseIndex++;
          lineIndex++;
          break;
        }
        lineIndex++;
        // -i case
        lineChar = line[lineIndex];
        if (i == 1){
          lineChar = allCaps(lineChar);
        }
        // returns special value if the end of the line
        // is hit with no matches.
        // ends all searches on the current line
        if(lineChar == '\0'){
          return -2;
        } 
      }
    } 
 
    // -e '.' case
    else if(phraseChar == '.' && e == 1){
      phraseIndex++;
      lineIndex++;
    } 


    // normal match
    else if(lineChar == phraseChar){
      phraseIndex++;
      lineIndex++;
    } 
  
    // no match
    else {
      return -1;
    }
  }
  // end of file hit, no match
  return -1;
} 




// main searching function
// loops through the entire line
// to find potential matches
// prints results as they appear
int findOcc(char phrase[], int e, int o, int i, char line[]){
  int index = 0;
  
  while(index<strlen(line)){
    // end of line
    if (line[index] == '\n'){
      break;
    } 
    
    // -i case
    char lineChar = line[index];
    char phraseChar = phrase[0];
    if (i == 1){
      lineChar = allCaps(lineChar);
      phraseChar = allCaps(phraseChar);
    }

    // check for first letter match
    int result = -1;
    if (lineChar == phraseChar){
      // send to match()
      result = match(index+1, line, phrase, e, i);
      // special case: # hit the end of the line
      // no possible matches 
      if (result == -2){
        return 0;
      }
      // match
      if(result != -1){
        // -o case, print and continue
        if (o == 1){
          for (int j = index; j < result; j++){
            printf("%c", line[j]);
          }
          printf("\n");
          index = result;
        // normal case, print whole line and
        // move on to the next line
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



// checks the search phrase for any errors
int checkPhrase(char phrase[], int e){
  int index = 0;
  int flag = 0; //flag to check if there are two # in a row

  while(phrase[index] !='\0'){
    // makes sure the input is '.','#', char, or int
    if (phrase[index] != '.' && phrase[index] != '#'){
      if(phrase[index] < 'a' || phrase[index] > 'z'){
        if(phrase[index] > 'Z' || phrase[index] < 'A'){
          if (phrase[index] < '0' || phrase[index] > '9'){
            printf("HERE");
            return 1;
          }
          // if we dont want a number after/before a #:
          // flag = 1
        }
      }
      flag = 0;
    // check special characters for -e restrictions
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
        if (phrase[index-1] == '#'){
          return 1;
        }
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





// MAIN
int main(int argc, char * argv[]){
  if (argc < 2){
    printf("Requires more command-line arguments.\n");
    return 1;
  }
  int searchWordIndex = -1;
  int eFlag = 0;
  int oFlag = 0;
  int iFlag = 0;
  
  // error handling and arg ops 
  if (argOps(argc, argv, &searchWordIndex, &eFlag, &oFlag, &iFlag) == 1){
    return 1;
  } else if (checkPhrase(argv[searchWordIndex], eFlag) == 1){
    printf("Invalid search term.\n");
    return 2;
  }
  
  // try to find matches for input
  char buffer[201];
  while (fgets(buffer, 200, stdin) != NULL){
    findOcc(argv[searchWordIndex], eFlag, oFlag, iFlag, buffer);
  }
  return 0;
}

