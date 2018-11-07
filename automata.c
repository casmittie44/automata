#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "convert.h"

/***********************************************
 * Define the number of cells to keep track of,
 * what symbols represent one and zero cells
 ***********************************************/
#define MAX 100
// #define ONE "\u25A0" // black square
#define ONE "*"
#define ZERO " "

/***********************************************************************
 * Applies the rules encoded in the character array rules to ith
 * element of the array cells which has length len Assumes that rules
 * is an 8 element array and cells contain entries that are either 0
 * or 1. Returns the result of applying the rule.
 * Ex: suppose that rules contains 10001100
 * The (i-1), i, (i+1)th elements of cells are 0,1,0 respectively.
 * Then this function will return 1
 **********************************************************************/
char applyRule(char* rules, char* cells, int i, int len) {
   char right, cur, left;
   cur = cells[i];
   if(i == 0)
      // left = 0;
      return 0;
 
   else if(i == (len-1)) 
      //    right = 0;
      return 0;

   else {
      left = cells[i-1];
      right = cells[i+1];
   }

   if(left == 1 && cur == 1 && right == 1)
      return rules[0];
   else if(left == 1 && cur == 1 && right == 0)
      return rules[1];
   else if(left == 1 && cur == 0 && right == 1)
      return rules[2];
   else if(left == 1 && cur == 0 && right == 0)
      return rules[3];
   else if(left == 0 && cur == 1 && right == 1)
      return rules[4];
   else if(left == 0 && cur == 1 && right == 0)
      return rules[5];
   else if(left == 0 && cur == 0 && right == 1)
      return rules[6];
   else
      return rules[7];
}

/********************************************************************
 * Takes an integer, and an array of length at least 8.
 * It fills the array with the value of the integer in binary,
 * with the most significant digits in the lowest indexes
********************************************************************/
void convertRule(int ruleNumber, char* ret) {
   int len = 8;
   unsigned char* binaryRule = convert(ruleNumber, 2);
   for(int i = 0; i < len; i++)
      ret[i] = binaryRule[len-i-1];

   free(binaryRule);
}

/********************************************************************
 * Generates the result of applying the elementary cellular automata
 * with rule number 'rule' to the elements of 'cells'.
 * Returns a dynamically allocated array of cells,
 * WHICH MUST BE FREED.
 ********************************************************************/
char* simpleEvolve(char* rules, char* cells, int len) {
   char* ret = (char*)malloc(len);
   for(int i=0; i<len; i++) 
      ret[i] = applyRule(rules, cells, i, len);
   
   return ret;
}

/*******************************************************************
 * Applies a random evolution rule at each stage.
 * It takes a dummy first parameter, so that it matches the
 * signature needed by the Evolution function pointer used in main()
*******************************************************************/
char* randomEvolve(char* dummy, char* cells, int len) {
   char rules[8];

   /*The following block uses a completely random rule every time.
    * It is pretty boring, since random rules tend to be ugly really
    * simple.
     convertRule(rand() % 256 + 1, rules);
   */

   /* This block randomly picks from a set of "interesting rules": */
   int choices[] = {30, 60, 54, 90, 110, 188, 182, 126, 124, 220, 24};
   int index = rand() % (sizeof (choices) / sizeof(choices[0]));
   convertRule(choices[index], rules);
   char* ret = (char*)malloc(len);
   for(int i=0; i<len; i++) 
      ret[i] = applyRule(rules, cells, i, len);
   
   return ret;
}

/********************************************************************
 * Prints out a stage in the evolution of a cellular automaton.
 * It uses the #defined constants ZERO, ONE to display the characters
 * chosen to represent these states. Generally, either asterisks or black
 * unicode squares are used to represent 1 and a space is used to represent
 * 0.
 *******************************************************************/
void printCells(char* cells, int len) {
   for(int i = 0; i < len; i++) {
      if(cells[i] == 0) 
	 printf("%s", ZERO);
      else
	 printf("%s", ONE);

   }

   printf("\n");
}

int main(int argc, char** argv) {
   char* (*Evolution)(char*, char*, int);
   char rules[8];
   int ruleNumber, numSteps = 20;
   
   if(argc < 2) {
      srand(time(0));
      Evolution = randomEvolve;
      numSteps = 50;
   }

   else {
      ruleNumber = atoi(argv[1]);
      if(argc > 2)
	 numSteps = atoi(argv[2]);

      convertRule(ruleNumber, rules);
      Evolution = simpleEvolve;
      // Print rule number
      printf("Rule: ");
      for(int i = 0; i < 8; i++)
	 printf("%d", rules[i]);
      printf("\n");
   }
  
   // Set up inital conditions
   // Read from file cells for setup
   char* lastStep = (char*)malloc(MAX);
   FILE* initCondsFile = fopen("cells", "r");
   if(initCondsFile == NULL)
      // If file error, setup with one inital black cell
      // in center of the field.
      lastStep[MAX / 2 - 1] = 1;
   else {
      // NEED AN ERROR CHECK IN CASE WE HIT EOF
      int charsRead = fread(lastStep, 1, MAX, initCondsFile);
      if(charsRead < MAX)
      {
	 memset(lastStep + charsRead, 0, MAX - charsRead - 1); 
      }
      
      // Convert '0' and '1' to 0 and 1
      for(int i = 0; i < MAX; i++) {
	 if(lastStep[i] == '0' || lastStep[i] == 0)
	    lastStep[i] = 0;
	 else
	    lastStep[i] = 1;
      }	 
   }

   char* nextStep;
   for(int i = 0; i < numSteps; i++) {
      printCells(lastStep, MAX);
      nextStep = Evolution(rules, lastStep, MAX);
      free(lastStep);
      lastStep = nextStep;
   }

   free(lastStep);
   return 0;
}
