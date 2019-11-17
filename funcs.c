#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mChop (char *line){
  int i = 0;

  for(i = 0; i < 500; i++){
    if(*(line + i) == '\n'){
      *(line + i) = ' ';
      break;
    }
  }

  return(0);
}

int mTrim(char *line){
  int i = 0;
  int j = 0;

  if(*line < 33){
    i = 0;
    while(*(line + i) < 33){
      i++;
    }
    while(*(line + j - 1) != '\0'){
      *(line + j) = *(line + i + j);
      j++;
    }
    *(line + i + j) = '\0';
  }

  i = 0;
  j = 0;
  while(*(line + i) != '\0'){
    i++;
  }

  while(*(line + i - j) < 33){
    *(line + i - j) = '\0';
    j++;
  }

  return (0);
}
