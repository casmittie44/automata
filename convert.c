#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*****************************************************************************
 * Takes an integer and target_base then returns a dynamically
 * allocated array of characters containing the digits of the number
 * in the target base, little-endian style. In other words, the least
 * significant digits are stored in the smallest indexes of the array.
 * The returned array is 32 characters long.
 *****************************************************************************/
unsigned char* convert(unsigned int number, unsigned int target_base) {
   int digits;
   long modulus = target_base;

   // Figure out how many digits we need to store number in binary
   for(digits=1; number >= modulus; digits++) {
      modulus *= target_base;
   }
   
   // Divide by largest power of target_base which is smaller than
   // number. Keep the integer part.
   unsigned char* ret = (unsigned char*)malloc(32);
   memset(ret, 0, 32);
   for(int i = 1; i < digits+1; i++) {
      modulus /= target_base;
      if(number >= modulus) {
	 ret[digits - i] = number / modulus;
	 number -= ret[digits - i] * modulus;
      }

      else
	 ret[digits - i] = 0;
   }
   
   return ret;
}

/*****************************************************************
 * Prints the significant digits stored in an array of characters,
 * little endian style. Ignores leading zeroes
 *****************************************************************/
void PrintDigits(unsigned char* ptr, int len) {
   int i = len-1;
   while(ptr[i] == 0)
      i--;

   while(i >= 0) {
      printf("%d", ptr[i]);
      i--;
   }

   printf("\n");
}

/************************************************
 * Test client code
int main(int argc, char** argv) {
   if(argc > 1) {
      int number = atoi(argv[1]);
      unsigned char* digits = convert(number, 2);
      PrintDigits(digits, 32);
   }

   else
      printf("Enter a number to be converted to binary.\n");
   
   return 0;
}
***************************************************/
