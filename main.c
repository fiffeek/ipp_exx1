#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "treeStruct.h"
#include "constants.h"

bool checkTwoInts(char *input, int k) {
  int i = 0;

  while (i < k && input[i] != ' ') {
    if (!((input[i] >= 'a' && input[i] <= 'z')
      || (input[i] >= 'A' || input[i] <= 'Z'))) {
      fprintf(stderr, "%s\n", "ERROR");
      return false;
    }

    i++;
  }

  if (input[i] != ' ') {
    fprintf(stderr, "%s\n", "ERROR");
    return false;
  }
  i++;

  while (i < k && input[i] != ' ') {
    if (input[i] < '0' || input[i] > '9') {
      fprintf(stderr, "%s\n", "ERROR");
      return false;
    }

    i++;
  }

  if (input[i] != ' ') {
    fprintf(stderr, "%s\n", "ERROR");
    return false;
  }
  i++;

  while (i < k && input[i] != '\n') {

    if (input[i] < '0' || input[i] > '9') {
      fprintf(stderr, "%s\n", "ERROR");
      return false;
    }

    i++;
  }

  if (input[i] != '\n') {
    fprintf(stderr, "%s\n", "ERROR");
    while(fgetc(stdin) != '\n'){};
    return false;
  }

  return true;
}

bool checkOneInt(char *input, int k) {
  int i = 0;

  while (i < k && input[i] != ' ') {
    if (!((input[i] >= 'a' && input[i] <= 'z')
      || (input[i] >= 'A' || input[i] <= 'Z'))) {
      fprintf(stderr, "%s\n", "ERROR");
      return false;
    }

    i++;
  }

  if (input[i] != ' ') {
    fprintf(stderr, "%s\n", "ERROR");
    return false;
  }
  i++;

  while (i < k && input[i] != '\n') {
    if (input[i] < '0' || input[i] > '9') {
      fprintf(stderr, "%s\n", "ERROR");
      return false;
    }

    i++;
  }

  if (input[i] != '\n') {
    fprintf(stderr, "%s\n", "ERROR");
    while(fgetc(stdin) != '\n'){};
    return false;
  }
  i++;

  return true;
}

bool toTheEndOfTheLine(char *input) {
  int k = strlen(input);

  if (input[k - 1] != '\n') {
    while(fgetc(stdin) != '\n'){};
  }

  fprintf(stderr, "%s\n", "ERROR");

  return false;
}

bool checkLine(char *input) {
  int k = strlen(input);

  if (k == 0 || input[0] == '\n')
    return false;

  if (input[0] == '#') {
    if (input[k - 1] != '\n') {
      while(fgetc(stdin) != '\n'){};
    }

    return false;
  }

  if (input[0] == 'a') {
    return checkTwoInts(input, k);
  } else if (input[0] == 'd') {
    if (k < 4) {
      return toTheEndOfTheLine(input);
    }

    if (input[3] == 'M') {
      return checkTwoInts(input, k);
    } else if (input[3] == 'U') {
      return checkOneInt(input, k);
    } else {
      return toTheEndOfTheLine(input);
    }
  } else if (input[0] == 'm') {
    return checkTwoInts(input, k);
  } else {
    return toTheEndOfTheLine(input);
  }
}

void copyStrings(char *input, int start) {
  int k = strlen(input);

  for (int i = 0; (i + start) < k; i++) {
    // copying with /n char
    input[i] = input[i + start];
  }

  return;
}

int main() {
  char *input = (char *)malloc(sizeof(char) * MAX_INPUT_SIZE);

  if (input == NULL)
    exit(EXIT_STATUS);

  initNode(0);

  while(fgets(input, MAX_INPUT_SIZE, stdin) != NULL) {
    //printf("polecenie : %s\n", input);
    if (!checkLine(input)) {
      continue;
    } else {
      bool err = false;
      int parentID, userID, movieRating,k;

      if (strncmp(input, "addUser", ADD_USER_SIZE) == 0) {
        copyStrings(input, ADD_USER_SIZE + 1);

        if (!sscanf(input, "%d %d", &parentID, &userID))
            err = true;

        if (!addChild(parentID, userID) || err) {
          // prompt about failure to stderr
          fprintf(stderr, "%s\n", "ERROR");
        } else {
          // adds the node
          fprintf(stdout, "%s\n", "OK");
        }
      } else if (strncmp(input, "delUser", ADD_USER_SIZE) == 0) {
        copyStrings(input, ADD_USER_SIZE + 1);

        if (!sscanf(input, "%d", &userID))
            err = true;

        if (!deleteChild(userID) || err) {
          fprintf(stderr, "%s\n", "ERROR");
        } else {
          printf("OK\n");
        }
      } else if (strncmp(input, "addMovie", ADD_MOVIE_SIZE) == 0) {
        copyStrings(input, ADD_MOVIE_SIZE + 1);

        if (!sscanf(input, "%d %d", &userID, &movieRating))
            err = true;

        if (!addMovie(userID, movieRating) || err) {
          fprintf(stderr, "%s\n", "ERROR");
        } else {
          printf("OK\n");
        }
      } else if (strncmp(input, "delMovie", ADD_MOVIE_SIZE) == 0) {
        copyStrings(input, ADD_MOVIE_SIZE + 1);

        if (!sscanf(input, "%d %d", &userID, &movieRating))
            err = true;

        if (!deleteMovie(userID, movieRating) || err) {
          fprintf(stderr, "%s\n", "ERROR");
        } else {
          printf("OK\n");
        }
      } else if (strncmp(input, "marathon", ADD_MOVIE_SIZE) == 0) {
        copyStrings(input, ADD_MOVIE_SIZE + 1);

        if (!sscanf(input, "%d %d", &userID, &k))
            err = true;

        if (!bestMovies(userID, k) || err) {
          fprintf(stderr, "%s\n", "ERROR");
        }
      } else {
        while(fgetc(stdin) != '\n'){};
        fprintf(stderr, "%s\n", "ERROR");
      }
    }
  }


  freeTree(getZeroPointer());
  free(input);
  return 0;
}
