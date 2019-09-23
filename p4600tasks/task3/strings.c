#include <stdio.h>
#include <stdlib.h>

int main()
{
  char* words = "Hello world";
  char* cursor = words;

  char input[64];
  float inputx;
  int correct;
  do
  {
    fflush(stdin);  
    printf("input a number please\n");
    //fflush(stdout);
   
    correct = scanf("%f", &inputx);
 
  }while (correct !=  1);

  
  /*
  do
  {
    int correct = scanf("%f", &inputx);
  }
  while(correct == 0)
  {
    printf("wrong human");
  }
  */
  
  while(*cursor != '\0')
  {
    printf("%c",*cursor);
    cursor++;
  }

  char* wordsarray = "Hello world";
  printf("\n%s",wordsarray);

  int x = 5;
  float y = 3.1415;
  char c = 'a';
  //format specifiers
  printf("\nInput was %f", inputx);
  printf("this is an int = %d float = %0.2f char = %c\n ", x,y,c);
  printf("\n copy of string %s",wordsarray);
}
