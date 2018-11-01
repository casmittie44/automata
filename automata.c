#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convert.h"

/***********************************************
 * Define the number of cells to keep track of,
 * what symbols represent one and zero cells
 ***********************************************/
#define MAX 100
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
      left = 0;
 
   else if(i == (len-1)) 
      right = 0;

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

/********************************************************************
 *
 *******************************************************************/
void printCells(char* cells, int len) {
   for(int i = 0; i < len; i++) {
      if(cells[i] == 0)
	 printf(ZERO);
      else
	 printf(ONE);
   }

   printf("\n");
}

int main(int argc, char** argv) {
   if(argc < 2) {
      printf("Usage: Enter an elementary cellular automaton rule number to be evolved.\n");
      exit(0);
   }

   int numSteps = 20;
   int ruleNumber = atoi(argv[1]);
   if(argc > 2)
      numSteps = atoi(argv[2]);
   
   char rules[8];
   convertRule(ruleNumber, rules);

   // Debug message
   printf("Debug: rule is: ");
   for(int i = 0; i < 8; i++)
      printf("%d", rules[i]);
   printf("\n");
  
   char* lastStep = (char*)malloc(MAX);
   lastStep[MAX / 2 - 1] = 1;
   char* nextStep;
   for(int i = 0; i < numSteps; i++) {
      printCells(lastStep, MAX);
      nextStep = simpleEvolve(rules, lastStep, MAX);
      free(lastStep);
      lastStep = nextStep;
   }

   free(lastStep);
   return 0;
}
