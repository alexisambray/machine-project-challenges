/*
    Do NOT forget to encode your name, section and date of submission.

    LASTNAME1, FIRSTNAME1: y                              SECTION: S11

    DATE SUBMITTED     :

        Make sure that you do the following:

        1. COMPILE your C source code with -Wall directive.

               Example: CCPROG2> gcc -Wall 02-C4.c -o 02-C4.exe

           where 02 is an example group number and C4 is the Challenge number.

           You must replace 02 with your own group number!

        2. RUN the program's exe file in the command line with input and output
   (I/O) redirection.

                        Example: CCPROG2> 02-C4 < AMZN.txt > 02-C4-OUTPUT.txt

       The text file 02-C4-OUTPUT.txt will contain the actual output of your
   program.

    3. COMPARE your program's output your program with the accompanying
   C4-EXPECTED.txt file using bbtest.c.

            In case you do not have bbtest.exe, produce it first by compiling
   bbtest.c as shown below:

                        Example: CCPROG2> gcc -Wall bbtest.c -o bbtest.exe

                Thereafter, run bbtest.exe with I/O redirection as shown below:

                        Example: CCPROG2> bbtest C4-EXPECTED.txt
   02-C4-OUTPUT.TXT > 02-C4-BBTEST.txt

                The output file 02-C4-BBTEST.txt contains the results of the
   comparison.  If you see Differences = 0 towards the end of the file, then it
   means that your program's output matches the expected output. Otherwise, if
   you see a Differences value higher than 0, then there's a strong probability
   that you either have a logical error in your program, or you did NOT follow
   the MP specifications (including the directions in this file).

                Debug your C source file, and redo the steps above until you get
   Differences = 0.

                Take note, however, that Differences = 0 does NOT necessarily
   mean that your solutions is 100% logically correct.  The bbtest.exe only
   tests if two files have the same contents.  It is not meant to test the logic
                of your C program.

        4. TEST your solution using the stock historical data for other
   companies other than AMZN.txt.  Note that there are not expected output files
   provided for other companies.  You'll have to figure out how to verify the
           correctness of your program's output on your own.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "C4.h"  // read and understand the contents of this file

/* Do NOT include other files. */

/*
        HARD REQUIREMENTS: NON-COMPLIANCE WILL MAKE YOUR SOLUTION INCORRECT or
   CAUSE POINT DEDUCTIONS!

        1. Similar to Challenge #2, you must apply arrays and strings in solving
   Challenge #4.
        2. Do NOT use struct data type yet for this particular challenge.
        3. Segregate your program's logic into multiple functions.
   Non-compliance will result to a 5 point deduction for this Challenge.
        4. Document your codes with SENSIBLE comments.
        5. You are NOT allowed to use library functions that were NOT discussed
   in our subject.
*/

/*
        You may #define any constants that you need below this comment.
*/
#define MAX 700
#define COMPANY_CODE_MAX_CHARS 5
#define NUM_OHLC_VALUES 4

/*
    You may declare any typedef that you need below this comment.
*/

// StrDate alias is to be used with a string that represents a date
typedef char StrDate[11];
typedef StrDate StrDates[MAX];
typedef double OhlcValue[NUM_OHLC_VALUES];
typedef OhlcValue OhlcValues[MAX];
typedef double VolumeValues[MAX];
typedef char CompanyCode[COMPANY_CODE_MAX_CHARS + 1];

/*
    TO DO: Define the functions that you need below this comment.  You are the
   one responsible in deciding what should be the function's a. return data type
        b. name
        c. formal parameters
        d. local variables and statements inside the body.

        You SHOULD write a SENSIBLE comment describing briefly what the function
   is supposed to accomplish BEFORE the function definition itself.
*/
void GetCompanyCodeAndTotalRecords(CompanyCode companyCode, int* totalRecords) {
  scanf("%s %d", companyCode, totalRecords);
}

void AddDate(StrDates strDates, const StrDate strDate, const int i) {
  strcpy(strDates[i], strDate);
}

void AddOhlcValue(OhlcValues ohlcValues,
                  const OhlcValue ohlcValue,
                  const int i) {
  for (int j = 0; j < NUM_OHLC_VALUES; j++) {
    ohlcValues[i][j] = ohlcValue[j];
  }
}

void AddVolumeValue(VolumeValues volumeValues,
                    const double volumeValue,
                    const int i) {
  volumeValues[i] = volumeValue;
}

void ProcessLine(StrDates strDates,
                 OhlcValues ohlcValues,
                 VolumeValues volumeValues,
                 const int i) {
  StrDate strDate;
  OhlcValue ohlcValue;
  double volumeValue;

  scanf("%s %lf %lf %lf %lf %lf", strDate, &ohlcValue[0], &ohlcValue[1],
        &ohlcValue[2], &ohlcValue[3], &volumeValue);
  AddDate(strDates, strDate, i);
  AddOhlcValue(ohlcValues, ohlcValue, i);
  AddVolumeValue(volumeValues, volumeValue, i);
}

void ReadStockHistoricalData(StrDates strDates,
                             OhlcValues ohlcValues,
                             VolumeValues volumeValues,
                             CompanyCode companyCode,
                             int* totalRecords) {
  GetCompanyCodeAndTotalRecords(companyCode, totalRecords);

  for (int i = 0; i < *totalRecords; i++) {
    ProcessLine(strDates, ohlcValues, volumeValues, i);
  }
}

double ComputeAverageClose(const OhlcValues ohlcValues,
                           const int startIndex,
                           const int endIndex) {
  double sum = 0;
  for (int i = startIndex; i <= endIndex; i++) {
    sum += ohlcValues[i][NUM_OHLC_VALUES - 1];
  }
  double average = sum / (endIndex - startIndex + 1);
  return average;
}

int ComputeSMA(const int m,
               StrDate* dateSMA,
               double* SMA,
               const StrDates strDates,
               const OhlcValues ohlcValues,
               const int totalRecords) {
  for (int i = totalRecords - m, j = 0; i >= 0; i--, j++) {
    int endIndex = i + (m - 1);
    SMA[j] = ComputeAverageClose(ohlcValues, i, endIndex);
    strcpy(dateSMA[j], strDates[i]);
  }
  int count = totalRecords - (m - 1);
  return count;
}

/*
        TO DO: Complete the body of the main() function.
*/
int main() {
  /* TO DO: Declare your own local variables AFTER this comment.  You MUST
     declare and use variables for the following:
          1. a string for storing company symbol, example "AMZN"
          2. an integer for storing the number of rows of stock historical data
     (in the case of AMZN.txt this value will store 629) variable
          3. 1D array of string for storing the dates (assume that the date
     values in the text file are are already formatted as "MM/DD/YYYY")
          4. 2D array of double values for storing the OHLC values
          5. 1D array of double for storing the volume
  */
  int totalRecords;
  CompanyCode companyCode;
  StrDates strDates;
  OhlcValues ohlcValues;
  VolumeValues volumeValues;

  /* Do NOT change the next four lines of variable declarations.  */
  int i, j, m;
  int count;
  StrDate dateSMA[MAX];  // 1D array of dates with corresponding SMA values
  double SMA[MAX];       // 1D array of SMA values

  /* Do NOT change the next line of array definition. View the C4.h header file
   * to see the values of the macros. */
  int test_cases[3] = {TEST_NDAYS1, TEST_NDAYS2, TEST_NDAYS3};

  /*
          TO DO: Fill in the blank by CALLing the function that you defined
     above for reading the stock historical data.
  */
  ReadStockHistoricalData(strDates, ohlcValues, volumeValues, companyCode,
                          &totalRecords);

  /* NOTE: The statements below should produce the required output. You are
     allowed to change or edit ONLY those lines with blanks by filling-up the
     missing information.

     Refer to the accompanying C4-EXPECTED.txt to see the expected results using
     AMZN.txt as input file. */

  /* TO DO: Fill in the blank to print the company symbol. */
  printf("%s\n", companyCode);

  /* The following lines are used to test the function you defined for computing
     the m-day SMA. Three test values for m are used which correspond to the
     macros TEST_NDAYS1, TEST_NDAYS2, and TEST_NDAYS3.
      */
  for (i = 0; i < 3; i++) {  // for each test case
    m = test_cases[i];       // m is the number of prices that are averaged
    printf("**TEST-%d-day-SMA**\n", m);

    /* TO DO: Fill in the blank by calling the function that computes the m-day
       SMA. The function should return an integer value to be stored in count.
       It must also accept as 1st parameter the value of m, DateSMA as 2nd
       parameter, and SMA as 3rd parameter.  Supply the function name and the
       other parameters that you think you'll need to accomplish the
       requirement. */
    count = ComputeSMA(m, dateSMA, SMA, strDates, ohlcValues, totalRecords);

    /* The following will print the count value, the dates and SMA values.
       Again, refer to the accompanying C4-EXPECTED.txt to see the expected
       results using AMZN.txt as input file. */
    printf("count = %d\n", count);
    for (j = 0; j < count; j++)
      printf("%3d  %s  %.2lf\n", j + 1, dateSMA[j], SMA[j]);

    printf("\n");
  }

  return 0;
}
