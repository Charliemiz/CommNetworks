/*
 * Auth: Charlie Misbach
 * Date: 02-20-24 (Due: 02-26-24)
 * Course: CSCI-3550 (Sec: 001)
 * Desc:  PREPROJECT-02, Command-line Arguments
 */

#include<stdio.h>

/* Entry point of program */
int main( int argc, char *argv[] ) {
  /* Declare int i for iteration */ 
  int i;

  /* Print program name using argv[0] */
  printf( "Program Name: %s\n", argv[0] );

  /* Check if there is at least one argument given by user */
  if (argc >= 2) {
    /* Print the number of arguments */
    printf( "Arguments: %d\n", argc - 1);

    /* Iterate through each argument and print them (not including program name) */
    for (i = 1; i < argc; i++) {
      printf( "argv[%d]: \"%s\"\n", i, argv[i]);
    }
  } else {
    /* Print an error message if not enough arguments were supplied */
    printf("ERROR: Must supply one or more arguments. Try again.");
  }

  return 0;
} /* end main() */