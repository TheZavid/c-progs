#include <stdio.h>

int
min(int temperatures[], int no_value, int n_of_temp)
{
  int padding = 0;

  // iterate through an array and find the min element in an array which is
  // to be used as cur_padding
  for (int i = 0; i < n_of_temp; i++){
    if ((temperatures[i] < padding) && (temperatures[i] != no_value))
      padding = temperatures[i];
  }

  padding *= -1;

  return padding;
}


void
printout(int padding, int temp)
{
  // print the correct padding for each value of termometre
  for(int i = 0; i < padding; i++) printf(" ");

  // stars '*' depict the correct temperature
  for(int i = 0; i <= temp; i++) printf("*");

  printf("\n");
}


void
visualise(int temperatures[], int no_value, int n_of_temp)
{
  int lastseen = 0;
  int padding = min(temperatures, no_value, n_of_temp);

  for (int i = 0; i < n_of_temp; i++){
    int cur_padding = padding;
    int cur_temp = temperatures[i];

    // if there is no data for the temperature we use the last seen temp or 0 if
    // there is no last seen
    if (cur_temp == no_value) cur_temp = lastseen;
    lastseen = cur_temp;

    // make the padding less for negative numbers and transform negative number
    // into positive
    if (cur_temp < 0){
      cur_padding += cur_temp;
      cur_temp *= -1;
    }

    // print out value with the correct padding
    printout(cur_padding, cur_temp);
  }
}

int
main(void)
{
  // simplified input
  constexpr int no_value = -999;
  int temperatures[] = { 10, 12, no_value, no_value, 20, 14, 6, -1, -5, 0, no_value, 1, -3 };
  int n_of_temp = (sizeof(temperatures)/sizeof(temperatures[0]));

  // visualise the data from the termometre
  visualise(temperatures, no_value, n_of_temp);

  return 0;
}
