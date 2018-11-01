#include <stdlib.h>
#include "convert.h"
#include "util.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <string.h>

void testCONVERT(void);

int main() {
   // Initialize test registery
   if(CUE_SUCCESS != CU_initialize_registry())
      fatal("Could not initialize registry.");
   CU_basic_set_mode(CU_BRM_VERBOSE);

   // Add suite to registry
   CU_pSuite pSuite = NULL;
   pSuite = CU_add_suite("Convert tests", NULL, NULL);
   CU_add_test(pSuite, "convert(number, base)", &testCONVERT);
   CU_basic_run_tests();

   CU_cleanup_registry();
   return CU_get_error();
}
     
void testCONVERT(void) {
   // convert stores its return value little endian style
   // Zero should be 0
   unsigned char* convertedNumber = convert(0, 3);
   unsigned char digits[32] = {0};
   CU_ASSERT(memcmp(convertedNumber, digits, 32) == 0);
   free(convertedNumber);
   
   // Convert 4 to binary: should be 100
   convertedNumber = convert(4, 2);
   digits[2] = 1;
   CU_ASSERT(memcmp(convertedNumber, digits, 32) == 0);
   free(convertedNumber);

   // Convert 34 to base-3: should be 1021
   convertedNumber = convert(34, 3);
   memset((void*)digits, 0, 32);
   digits[0] = 1;
   digits[1] = 2;
   digits[3] = 1;
   CU_ASSERT(memcmp(convert(34, 3), digits, 32) == 0);
   free(convertedNumber);
   
   // Convert 432432 to decimal: should be 432432
   convertedNumber = convert(432432, 10);
   memset((void*)digits, 0, 32);
   digits[0] = 2;
   digits[1] = 3;
   digits[2] = 4;
   digits[3] = 2;
   digits[4] = 3;
   digits[5] = 4;
   CU_ASSERT(memcmp(convert(432432, 10), digits, 32) == 0);
   free(convertedNumber);
   
   // Convert 47 to binary: should be 101111
   memset((void*)digits, 0, 32);
   convertedNumber = convert(47, 2);
   digits[0] = 1;
   digits[1] = 1;
   digits[2] = 1;
   digits[3] = 1;
   digits[4] = 0;
   digits[5] = 1;
   CU_ASSERT(memcmp(convert(47, 2), digits, 32) == 0);
   free(convertedNumber);
}
