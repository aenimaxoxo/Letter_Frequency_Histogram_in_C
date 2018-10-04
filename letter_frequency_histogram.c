# include <stdio.h>
# include <ctype.h>
# include <time.h>

# define MAXCHAR 1000

int get_max_array_element(int a[], int array_length){
  int max = 0;
  int index = 0;
  
  for (int i = 0; i < array_length; i++){
    if (a[i] > a[max]){
      max = index;
    }
    index++;
  }
  return max;
}

void print_vowels(int letters[], int max_length){

  // declare multidimensional array with width = 26 (for letters) and height = most common vowel

  int multi_letters[26][max_length];

  // fill with zeros
  
  for (int i = 0; i < 26; i++){
    for (int j = 0; j < max_length; j++){
      multi_letters[i][j] = 0; 
    }
  }

  // fill in histogram spots
  
  for (int i = 0, k = 'a'; i < 26, k <= 'z'; i++, k++){
    int location = max_length - letters[k];
    for (int j = location; j < max_length; j++){
      multi_letters[i][j] = 1;
    }
  }
  printf("\n");

  // print out just vowels

  for (int j = 0; j < max_length; j++){
    for (int i = 0; i < 26; i++){
      if (i == 0 || i == 4 || i == 8 || i == 14 || i == 20){
	if (multi_letters[i][j] == 0){
	  printf("  | ");
	} else {
	  printf("* | ");
	}
      } else {
	continue;
      }
    }
    printf("\n");
  }
  printf("\n");
  
  // print out vowels for reference
  
  printf("a | e | i | o | u |");
}

void print_letters(int letters[], int max_length){

  // declare multidimensional array with width = 26 (for letters) and height = most common vowel

  int multi_letters[26][max_length];

  // fill with zeros
  
  for (int i = 0; i < 26; i++){
    for (int j = 0; j < max_length; j++){
      multi_letters[i][j] = 0; 
    }
  }

  // fill in histogram spots
  
  for (int i = 0, k = 'a'; i < 26, k <= 'z'; i++, k++){
    int location = max_length - letters[k];
    for (int j = location; j < max_length; j++){
      multi_letters[i][j] = 1;
    }
  }
  printf("\n");

  // print out multidimensional array
  
  for (int j = 0; j < max_length; j++){
    for (int i = 0; i < 26; i++){
      if (multi_letters[i][j] == 0){
	printf("  | ");
      } else {
	printf("* | ");
      }
      // printf("%d | ", multi_letters[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  // print out letters for reference
  for (int k = 'a'; k <= 'z'; k++){
    printf("%c | ", k);
  }
}

int main(void){

  FILE *fp;
  char str[MAXCHAR], c;
  int letters[128];
  int state = 2;
  char *filename;
  int count = 0;
  
  // constructs for time module
  
  time_t our_time;
  struct tm * timeblock;
  time(&our_time);
  timeblock = localtime(&our_time);

  // file entry
  
  printf("Please enter the location of a text file without quotes. \n");
  scanf("%s", filename);
  
  fp = fopen(filename, "r");

  // catch null file
  
  if (fp == NULL){
    printf("\nCan not open file: %s. Check file path and permissions.", filename);
    return 1; 
  }

  printf("\nEnter 0 to return all letters or 1 to return just vowels: \n");
  scanf("%d", &state);
  
  // fill array with zeros before use
  
  for (int i = 0; i < 128; i++){
    letters[i] = 0;
  }

  // for aesthetics
  
  printf("\n\n");

  // parse file
  
  while ((c = getc(fp)) != EOF){
    if (c >= 'A' && c <= 'z'){
      ++letters[tolower(c)];
    }
    if isdigit(c){
	count++;
      }
  }

  // get  max element statistics
  
  int max_index = get_max_array_element(letters, 128);
  int max_length = letters[max_index];

  printf("The highest frequency letter is %c, with a count of %d\n\n", max_index, max_length);


  if (state == 0){
    // print out histogram of all letters
    print_letters(letters, max_length);
  }
  else if (state == 1){
    // print out histogram of all vowels
    print_vowels(letters, max_length);
  } else {
    printf("Choice Undefined.\n");
    return 1;
  }
  // print out program statistics
  
  printf("\n\nThis file has %d numerical digits.\n\n", count);
  printf("The current year is %d, and this file is being created at %d:%d, on %d/%d/%d.\n\n", timeblock -> tm_year + 1900, timeblock -> tm_hour, timeblock -> tm_min, timeblock -> tm_mon + 1, timeblock -> tm_mday, timeblock -> tm_year - 100);

  // close file stream
  
  fclose(fp);
  
  return 0;
}
