#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Initialise functions and structs
int len();
void cpy(char *s1, char *s2);
struct Data split(char *str);

// Data struct
typedef struct Data {
  char source[4096];
  char dest[4096];
  char time[4096];
} Data;

// Find the length of a string
int len(char str[]) {
  int i = 0;
  while (str[i] != '\0') {
    i++;
  }
  return i;
}

// Copy data from one variable to another
void cpy(char *s1, char *s2) {
  while ((*s1 = *s2) != '\0') {
    s1++;
    s2++;
  }
}

// Compare two strings and return true only if identical
bool cmp(char s1[], char s2[]) {
  if (len(s1) != len(s2)) {
    return false;
  }

  for (int i = 0; i < len(s1); i++) {
    if (s1[i] != s2[i]) {
      return false;
    }
  }

  return true;
}

/* Given data string in form <source>::<destination>::<time>, split up the
string and store within Data struct {source, dest, time} */
struct Data split(char *str) {
  // Reset the data struct each time split is used
  static const Data emptyStruct;
  Data d;
  d = emptyStruct;

  int start = 0;
  int count = 0;
  for (int i = 0; i < len(str); i++) {
    if (i == len(str) - 1) {
      for (int j = 0; j < i - start + 1; j++) {
        if (count == 2) {
          d.time[j] = str[start + j];
        }
      }
      d.time[len(d.time) - 1] = '\0';
      i++;
    } else if (str[i] == ':' && str[i + 1] == ':') {
      for (int j = 0; j < i - start; j++) {
        if (count == 0) {
          d.source[j] = str[start + j];
        } else if (count == 1) {
          d.dest[j] = str[start + j];
        }
      }
      count++;
      start = i + 2;
      i++;
    }
  }

  return d;
}

/* Converts time string in form hh:mm:ss to integer representing seconds
since midnight */
int strToTime(char *str) {
  int result = 0;

  /* If time string format is incorrect, return -1. Otherwise, add time in
  seconds to the result */
  if (len(str) != 8) {
    return -1;
  }

  for (int i = 0; i < 8; i++) {
    if (i == 2 || i == 5) {
      if (str[i] != ':') {
        printf("%s\n", "1");
        return -1;
      }
    } else if (i == 0 || i == 1) {
      if (str[0] == '0' || str[0] == '1') {
        if (str[1] != '0' && str[1] != '1' && str[1] != '2' && str[1] != '3' && str[1] != '4' && str[1] != '5' && str[1] != '6' && str[1] != '7' && str[1] != '8' && str[1] != '9') {
          printf("%s\n", "2");
          return -1;
        } else {
          result += (int) str[0] * 36000 + (int) str[1] * 3600;
        }
      } else if (str[0] == '2') {
        if (str[1] != '0' && str[1] != '1' && str[1] != '2' && str[1] != '3') {
          printf("%s\n", "3");
          return -1;
        } else {
          result += (int) str[0] * 36000 + (int) str[1] * 3600;
        }
      } else {
        printf("%s\n", "4");
        return -1;
      }
    } else if (i == 3) {
      if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5') {
        printf("%s\n", "5");
        return -1;
      } else {
        result += (int) str[3] * 600;
      }
    } else if (i == 6) {
      if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5') {
        printf("%s\n", "6");
        return -1;
      } else {
        result += (int) str[6] * 10;
      }
    } else if (i == 4) {
      if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9') {
        printf("%s\n", "7");
        return -1;
      } else {
        result += (int) str[4] * 60;
      }
    } else if (i == 7) {
      if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9') {
        printf("%s\n", "8");
        return -1;
      } else {
        result += (int) str[7];
      }
    }
  }

  return result;
}

// Main function
int main(int argc, char *argv[]) {
  // If not enough arguments, exit program
  if (argc != 4) {
    printf("Please provide <source> <destination> <time> as command line arguments\n");
    exit(0);
  }

  char str[4096]; // Store next line from file
  char nextTrainTime[9]; // Store next train departure time
  struct Data d;
  while (fgets(str, 4096, stdin) != NULL) {
    d = split(str);

    /* If we have the required source and destination, sort through data and
    update nextTrainTime variable for each earlier departure time */
    if (cmp(d.source, argv[1])) {
      if (cmp(d.dest, argv[2])) {
        if (strToTime(d.time) != -1 && strToTime(argv[3]) != -1) {
          if (strToTime(d.time) - strToTime(argv[3]) > 0) {
            if (nextTrainTime[0] == '\0') {
              cpy(nextTrainTime, d.time);
            } else if (strToTime(d.time) - strToTime(argv[3]) < strToTime(nextTrainTime) - strToTime(argv[3])) {
              cpy(nextTrainTime, d.time);
            }
          }
        }
      }
    }
  }

  // Final output message
  if (nextTrainTime[0] == '\0') {
    printf("No suitable trains can be found\n");
  } else {
    printf("The next train to %s from %s departs at %s\n", argv[2], argv[1], nextTrainTime);
  }

  return 0;
}
