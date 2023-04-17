#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include "passwgen.h"

/*Генератор пароля.*/
char* passwgen(int* len_passw)
{
  int length = *len_passw;

  struct timeval  tv;
  gettimeofday(&tv, NULL);
  
  char *password = (char*)calloc(length + 1, sizeof(char));

  char *digits = "0123456789";
  int digits_length = strlen(digits);
  
  char *lowers = "abcdefghijklmnopqrstuwxyz";
  int lowers_length = strlen(lowers);
  
  char *uppers = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int uppers_length = strlen(uppers);
  
  char *symbols = "!@#$%^&*()";
  int symbols_length = strlen(symbols);

  srand(tv.tv_usec);
  
  for (int i = 0; i < length; i++)
  {
    int char_type = rand() % 4;
    
    if (char_type == 0)
      password[i] = digits[rand() % digits_length];
    else if (char_type == 1)
      password[i] = lowers[rand() % lowers_length];
    else if (char_type == 2)
      password[i] = uppers[rand() % uppers_length];
    else
      password[i] = symbols[rand() % symbols_length];
    
  }
  return password;
}