#include <stdlib.h>
#include <stdio.h>

// Print an error message and then exit the program
void fatal(char* message) {
   printf("[!!]Fatal Error: %s", message);
   printf("\n");
   exit(0);
}
