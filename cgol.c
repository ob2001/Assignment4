#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cell{
  int x;
  int y;
  char isAlive;
};

int mChop(char *line);

int mTrim(char *line);

int main(int argc, char *argv[]){

  /* Declare and initialize variables */
  int cols = 40;
  int rows = 20;
  int x = 0;
  int y = 0;
  int i = 0;
  int j = 0;
  int k = 0;
  int currTick = 0;
  int origNumTicks = 0;
  int numTicks = 0;
  int numSame = 0;
  int flag = 0;
  int flag2 = 0;
  int liveNeighbors = 0;
  char line[(2 * cols) + 1];
  line[0] = '\0';
  FILE *fp;

  /* Get information from command line. Break on incorrect format */
  if((argv[1] == NULL) || (argv[2] == NULL)){
    printf("Error - usage: ./cgol.c <seedfilename> <ticks>\n");
    return(1);
  }

  if(atoi(argv[2]) == 0){
    printf("Please enter a valid integer for <ticks>\n");
    return(1);
  } else {
    origNumTicks = atoi(argv[2]);
    numTicks = origNumTicks;
  }

  /* Declare and initialize world and future world struct arrays */
  struct cell world[cols][rows];
  for(x = 0; x < cols; x++){
    for(y = 0; y < rows; y++){
      world[x][y].x = x;
      world[x][y].y = y;
      world[x][y].isAlive = ' ';
    }
  }

  struct cell futureWorld[cols][rows];
  for(x = 0; x < cols; x++){
    for(y = 0; y < rows; y++){
      futureWorld[x][y].x = x;
      futureWorld[x][y].y = y;
      futureWorld[x][y].isAlive = ' ';
    }
  }

  /* Open seed file to read if it exists */
  if((fp = fopen(argv[1], "r")) == NULL){
    printf("Error - cannot open file \"%s\"\n", argv[1]);
    return(1);
  }

  /* Copy contents of seed file to world struct array, close seed file */
  y = 0;
  while((fgets(line, (2 * cols) + 1, fp)) != NULL){
    k = 0;
    x = 0;
    while(*(line + k) != '\n'){
      if(*(line + k) == ' '){
        k++;
      } else if(*(line + k) == '0'){
        world[x][y].isAlive = ' ';
        k++;
        x++;
      } else if(*(line + k) == '1'){
        world[x][y].isAlive = 'X';
        k++;
        x++;
      }
    }
    y++;
  }

  fclose(fp);

  /* Print contents of initial world struct array */
  flag = 0;
  system("clear");
  x = 0;
  y = 0;
  printf(" ---------------------------------------- \n");
  while(y < rows){
    printf("|");
    x = 0;
    while(x < cols){
      printf("%c", world[x][y].isAlive);
      x++;
    }
    printf("|\n");
    y++;
  }
  printf(" ----------------------------------------%d\n", currTick);

  /* Ask user whether to begin simulation */
  printf("Would you like to begin simulation? [y or n]: ");
  while(flag != 1){
    fgets(line, 50, stdin);
    mChop(line);
    mTrim(line);
    if(strcmp(line, "n") == 0){
      return(0);
    } else if (strcmp(line, "y") != 0){
      printf("Only the single characters y or n are acceptable: ");
    } else {
      flag = 1;
    }
  }

  flag = 0;
  /* Simulation loop */
  while(currTick < numTicks && flag != 1){
    currTick++;
    x = 0;
    y = 0;

    /* Print contents of world struct array */
    system("clear");

    printf(" ---------------------------------------- \n");
    while(y < rows){
      printf("|");
      x = 0;
      while(x < cols){
        printf("%c", world[x][y].isAlive);
        x++;
      }
      printf("|\n");
      y++;
    }
    printf(" ----------------------------------------%d\n", currTick);
    system("sleep 0.25");

    /* Iterate over each cell to see if it dies or comes to life. Store result in future struct array*/
    for(x = 0; x < cols; x++){
      for(y = 0; y < rows; y++){
        i = -1;
        j = -1;
        liveNeighbors = 0;
        for(i = -1; i < 2; i++){
          for(j = -1; j < 2; j++){
            if((x + i) > -1 && (y + j) > -1 && (x + i) < cols && (y + j) < rows && !(i == 0 && j == 0)){
              if(world[x + i][y + j].isAlive == 'X'){
                liveNeighbors++;
              }
            }
          }
        }
        if(world[x][y].isAlive == 'X'){
          if(liveNeighbors < 2){
            futureWorld[x][y].isAlive = ' ';
          } else if (liveNeighbors == 2 || liveNeighbors == 3){
            futureWorld[x][y].isAlive = 'X';
          } else {
            futureWorld[x][y].isAlive = ' ';
          }
        } else if(world[x][y].isAlive == ' '){
          if(liveNeighbors == 3){
            futureWorld[x][y].isAlive = 'X';
          }
        }
      }
    }

    /* Copy contents of future struct array to world struct array while counting the number of cells that haven't changed*/
    x = 0;
    y = 0;
    numSame = 0;
    for(x = 0; x < cols; x++){
      for(y = 0; y < rows; y++){
        if(world[x][y].isAlive == futureWorld[x][y].isAlive){
          numSame++;
        }
        world[x][y].isAlive = futureWorld[x][y].isAlive;
      }
    }

    /* Check whether to break loop due to an unchanging system*/
    if(numSame == rows * cols){
      flag = 1;
    }

    /* Check whether to break loop due to reaching specified number of ticks*/
    if(currTick == numTicks && flag != 1){
      flag2 = 0;
      printf("Would you like to continue? [y or n]: ");
      while(flag2 != 1){
        fgets(line, 50, stdin);
        mChop(line);
        mTrim(line);
        if(*line == 'n'){
          flag = 1;
          flag2 = 1;
        } else if(*line != 'y'){
          printf("Only the single characters y or n are acceptable: ");
        } else {
          numTicks += origNumTicks;
          flag2 = 1;
        }
      }
    }
  }

  return(0);
}
