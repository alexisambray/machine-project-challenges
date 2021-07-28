/*
    Do NOT forget to encode your name, section and date of submission.

    LASTNAME1, FIRSTNAME1: AMBRAY, ALEXIS                SECTION: S11
    LASTNAME2, FIRSTNAME2:                               SECTION:

    DATE SUBMITTED     :

        Make sure that you do the following:

        1. COMPILE your C source code with -Wall directive.

               Example: CCPROG2> gcc -Wall 02-C3.c -o 02-C3.exe

           where 02 is an example group number and C3 is the Challenge number.

           You must replace 02 with your own group number!

        2. RUN the program's exe file in the command line with input and output
   (I/O) redirection.

                        Example: CCPROG2> 02-C3 < AMZN.txt > 02-C3-OUTPUT.txt

       The text file 02-C3-OUTPUT.txt will contain the actual output of your
   program.

    3. COMPARE your program's output your program with the accompanying
   C3-EXPECTED.txt file using bbtest.c.

            In case you do not have bbtest.exe, produce it first by compiling
   bbtest.c as shown below:

                        Example: CCPROG2> gcc -Wall bbtest.c -o bbtest.exe

                Thereafter, run bbtest.exe with I/O redirection as shown below:

                        Example: CCPROG2> bbtest C3-EXPECTED.txt
   02-C3-OUTPUT.TXT > 02-C3-BBTEST.txt

                The output file 02-C3-BBTEST.txt contains the results of the
   comparison.  If you see Differences = 0 towards the end of the file, then it
   means that your program's output matches the expected output. Otherwise, if
   you see a Differences value higher than 0, then there's a strong probability
   that you either have a logical error in your program, or you did NOT follow
   the MP specifications (including the directions in this file).

                Debug your C source file, and redo the steps above until you get
   Differences = 0.

                Take note, however, that Differences = 0 does NOT necessarily
   mean that your solution is 100% logically correct.  The bbtest.exe only tests
   if two files have the same contents.  It is not meant to test the logic of
   your C program.

        4. TEST your solution using the stock historical data for other
   companies other than AMZN.txt.  Note that there are no expected output files
   provided for other companies.  You'll have to figure out how to verify the
           correctness of your program's output on your own.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Do NOT include other files. */

/*
        HARD REQUIREMENTS: NON-COMPLIANCE WILL MAKE YOUR SOLUTION INCORRECT or
   CAUSE POINT DEDUCTIONS!

        1. Similar to Challenge #2, you must apply arrays and strings in solving
   Challenge #3.
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
#define MAX_RECORDS 1000
#define NUM_OHLC_VALUES 4

/*
    You may declare any typedef that you need below this comment.
*/
// StrDate alias is to be used with a string that represents a date
typedef char StrDate[11];
typedef StrDate StrDates[MAX_RECORDS];
typedef double OhlcValue[NUM_OHLC_VALUES];
typedef OhlcValue OhlcValues[MAX_RECORDS];
typedef double VolumeValues[MAX_RECORDS];
typedef char CompanySymbol[11];
/*
    TO DO: Define the functions that you need below this comment.  You are the
   one responsible in deciding what should be the function's a. return data type
        b. name
        c. formal parameters
        d. local variables and statements inside the body.

        You SHOULD write a SENSIBLE comment describing briefly what the function
   is supposed to accomplish BEFORE the function definition itself.
*/
void GetCompanySymbolAndTotalRecords(CompanySymbol companySymbol,
                                     int* totalRecords) {
  scanf("%s %d", companySymbol, totalRecords);
}

int GetMinIndex(const OhlcValues ohlcValues, const int totalRecords) {
  int minIndex = 0;
  double minValue = ohlcValues[0][NUM_OHLC_VALUES - 1];
  for (int i = 1; i < totalRecords; i++) {
    if (ohlcValues[i][NUM_OHLC_VALUES - 1] < minValue) {
      minValue = ohlcValues[i][NUM_OHLC_VALUES - 1];
      minIndex = i;
    }
  }
  return minIndex;
}

int GetMaxIndex(const OhlcValues ohlcValues, const int totalRecords) {
  int maxIndex = 0;
  double maxValue = ohlcValues[0][NUM_OHLC_VALUES - 1];
  for (int i = 1; i < totalRecords; i++) {
    if (ohlcValues[i][NUM_OHLC_VALUES - 1] > maxValue) {
      maxValue = ohlcValues[i][NUM_OHLC_VALUES - 1];
      maxIndex = i;
    }
  }
  return maxIndex;
}

void AddDate(StrDates strDates, const StrDate strDate, const int i) {
  strcpy(strDates[i], strDate);
}

void AddOhlc(OhlcValues ohlcValues, const OhlcValue ohlcValue, const int i) {
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
                 CompanySymbol companySymbol,
                 const int i) {
  StrDate strDate;
  OhlcValue ohlcValue;
  double volumeValue;

  scanf("%s %lf %lf %lf %lf %lf", strDate, &ohlcValue[0], &ohlcValue[1],
        &ohlcValue[2], &ohlcValue[3], &volumeValue);
  AddDate(strDates, strDate, i);
  AddOhlc(ohlcValues, ohlcValue, i);
  AddVolumeValue(volumeValues, volumeValue, i);
}

void ReadStockHistoricalData(StrDates strDates,
                             OhlcValues ohlcValues,
                             VolumeValues volumeValues,
                             CompanySymbol companySymbol,
                             int* totalRecords) {
  GetCompanySymbolAndTotalRecords(companySymbol, totalRecords);

  for (int i = 0; i < *totalRecords; i++) {
    ProcessLine(strDates, ohlcValues, volumeValues, companySymbol, i);
  }
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
  CompanySymbol companySymbol;
  int totalRecords;
  StrDates strDates;
  OhlcValues ohlcValues;
  VolumeValues volumeValues;

  /* Do NOT change the next two variable declarations.  Use min_index to store
     the index of the array with the lowest (minimum) closing stock price.
     Similarly, use max_index to store index of the the array with the highest
     (maximum) closing stock price. */
  int min_index;
  int max_index;

  /*
              TO DO: Fill in the blank by CALLing the function that you defined
     above for reading the stock historical data.
  */
  ReadStockHistoricalData(strDates, ohlcValues, volumeValues, companySymbol,
                          &totalRecords);

  /*
          TO DO: Fill in the blanks by CALLING the functions that will compute
     the min_index and max_index values.
  */
  min_index = GetMinIndex(ohlcValues, totalRecords);
  max_index = GetMaxIndex(ohlcValues, totalRecords);

  /* The next three printf() statements should produce the required output.
         Refer to the accompanying C3-EXPECTED.txt to see the expected results
     using AMZN.txt as input file. */

  /* TO DO: Fill in the blank to print the company symbol. */
  printf("%s\n", companySymbol);

  /* TO DO: Fill in the blanks to print array index corresponding to the
          (a) index of the most recent lowest closing price, (b) the date
     associated with that index and (c) the lowest closing price value. */
  printf("%d %s %.2f\n", min_index, strDates[min_index],
         ohlcValues[min_index][NUM_OHLC_VALUES - 1]);

  /* TO DO: Fill in the blanks to to print the array index corresponding to the
          (a) index of the most recent highest closing price, (b) the date
     associated with that index (c) and the highest closing price value. */
  printf("%d %s %.2f\n", max_index, strDates[max_index],
         ohlcValues[max_index][NUM_OHLC_VALUES - 1]);

  return 0;
}
