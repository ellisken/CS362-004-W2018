#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

/*********************************************************
 * Name: inputChar()
 * Description: Generates a random char by ASCII and checks
 *   against valid inputs ('[', '(', '{', ' ', 'a', 'x', '}',
 *   ')', and ']'), then returns the char if valid.
 * Inputs: None, srand() must be seeded prior to usage.
 * Outputs: A char
 * Author: Kendra Ellis, ellisken@oregonstate.edu
 * ******************************************************/
char inputChar()
{
    //Create variable to store the "random" number generated
    int num = 0;

    //Generate new value for num within valid ASCII range
    //32-125, i.e., '[space]' through '}'
    //until it matches a valid char
    while(num != 91 && num != 40 && num != 123 && num != 32
        && num != 97 && num != 120 && num != 125
        && num != 41 && num != 93)
        num = rand() % (125 + 1 - 32) + 32;

    //Return result
    return num;
}



/*********************************************************
 * Name: inputString()
 * Description: Generates and returns a pointer to a 
 *  randomly generated C-string terminated by a null char.
 *  Total C-string length (including null) is 5.
 * Inputs: None, srand() must be seeded prior to usage.
 * Outputs: A pointer
 * Author: Kendra Ellis, ellisken@oregonstate.edu
 * ******************************************************/
char *inputString()
{
    //Create pointer to char string of length 5
    //since we're looking for the word "reset"
    char *random_string = malloc(5 * sizeof(char));

    //Generate random string of ASCII letters 
    //by generated a num in the ASCII range 101-116
    //and checking for valid letters 'e'
    //'r', 's', and 't' (101, 114, 115, 116) as the 
    //goal is to generate the word "reset"
    int i = 0;
    int j = 0;

    while(i < 5){
        j = rand() % (116 + 1 - 101) + 101;
        if(j == 101 || j == 114 || j == 115 || j == 116){
            random_string[i] = j;
            i++;
        }
    }

    //Return pointer to result
    return random_string;
}

void testme()
{
  //Initialize test iteration count variable, a pointer to a char array "s",
  //a char "c", and a test state.
  int tcCount = 0;
  char *s = NULL;
  char c;
  int state = 0;

  //While true, instantiate a new value for "s" and "c" and print
  //the iteration, values of "s" and "c" and the test state
  //to the console.
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    //Go through until each of the 9 search values
    //for "c" have been found in sequential order, 
    //update state each time a value is found
    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;

    //If "s" is equal to the value "reset"
    //and all the values of "c" have been found in sequence,
    //print "error" and exit the loop
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }

    //Release allocated string memory
    free(s);
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
