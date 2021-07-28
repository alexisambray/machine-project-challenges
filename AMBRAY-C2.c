/*
    Do not forget to encode your name, section and date of submission.

    LASTNAME1, FIRSTNAME1: AMBRAY, ALEXIS                SECTION: S11
    LASTNAME2, FIRSTNAME2:                               SECTION:

    DATE SUBMITTED     :

        CCPROG2 MP Solution for: Challenge #2

        Make sure to compile your C source code with a -Wall directive.
           Example: CCPROG2> gcc -Wall 02-C2.c -o 02-C2.exe

        Run the program's exe file in the command line with input and output
   (I/O) redirection. Example: CCPROG2> 02-C2 < AMZNorig.txt > AMZN.txt
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATE_FORMAT_LENGTH 10
#define NUM_OHLC_VALUES 4
#define MAX_RECORDS 1000

/* Do NOT include other header files. */

/*
        HARD REQUIREMENTS: NON-COMPLIANCE WILL MAKE YOUR SOLUTION INCORRECT or
   CAUSE POINT DEDUCTIONS!

        1. You must apply arrays and strings in solving Challenge #2.
        2. Do NOT use struct data type yet for this particular challenge.
        3. Segregate your program's logic into functions.  Non-compliance will
   result to a 5 point deduction for this Challenge.
        4. Document your codes with SENSIBLE comments.
        5. You are NOT allowed to use library functions that were NOT discussed
   in our subject.
*/

/*
    You may declare any typedef that you need below this comment.
*/
typedef char Date[DATE_FORMAT_LENGTH + 1];
typedef Date Dates[MAX_RECORDS];
typedef double OhlcValue[NUM_OHLC_VALUES];
typedef OhlcValue OhlcValues[MAX_RECORDS];
typedef double VolumeValues[MAX_RECORDS];

/*
    Define any function that you need below this comment.
*/

int GetNumRecords() {
  char companyCode[11];
  int numRecords;

  scanf("%s %d", companyCode, &numRecords);

  return numRecords;
}

void AddVolumeValue(VolumeValues volumeValues,
                    const double volume,
                    const int i) {
  volumeValues[i] = volume;
}

void AddOhlc(OhlcValues ohlcValues, const double ohlc[], const int i) {
  for (int j = 0; j < NUM_OHLC_VALUES; j++) {
    ohlcValues[i][j] = ohlc[j];
  }
}

void AddDate(Dates dates,
             const int month,
             const int day,
             const int year,
             const int i) {
  Date date;

  sprintf(date, "%02d/%02d/20%d", month, day, year);
  strcpy(dates[i], date);
}

void ProcessLine(Dates dates,
                 OhlcValues ohlcValues,
                 VolumeValues volumeValues,
                 const int i) {
  int month, day, year;
  OhlcValue ohlc;
  double volume;

  scanf("%d/%d/%d %lf %lf %lf %lf %lf", &month, &day, &year, &ohlc[0], &ohlc[1],
        &ohlc[2], &ohlc[3], &volume);
  year %= 100;  //  Strip out 20 part of the year
  AddDate(dates, month, day, year, i);
  AddOhlc(ohlcValues, ohlc, i);
  AddVolumeValue(volumeValues, volume, i);
}

void PopulateData(Dates dates,
                  OhlcValues ohlcValues,
                  VolumeValues volumeValues,
                  const int numRecords) {
  for (int i = 0; i < numRecords; i++) {
    ProcessLine(dates, ohlcValues, volumeValues, i);
  }
}

void OutputData(const Dates dates,
                const OhlcValues ohlcValues,
                const VolumeValues volumeValues,
                const int numRecords) {
  for (int i = 0; i < numRecords; i++) {
    printf("%s%15.2lf%15.2lf%15.2lf%15.2lf%15.2lf\n", dates[i],
           ohlcValues[i][0], ohlcValues[i][1], ohlcValues[i][2],
           ohlcValues[i][3], volumeValues[i]);
  }
}

int main() {
  /* Declare your own local variables. */
  Dates dates;
  OhlcValues ohlcValues;
  VolumeValues volumeValues;
  int numRecords;

  /* Call the functions that you defined. */

  numRecords = GetNumRecords();
  PopulateData(dates, ohlcValues, volumeValues, numRecords);
  OutputData(dates, ohlcValues, volumeValues, numRecords);

  return 0;
}
