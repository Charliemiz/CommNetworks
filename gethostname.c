/*
 * Auth: Charlie Misbach
 * Date: 02-28-24 (Due: 03-03-24)
 * Course: CSCI-3550 (Sec: 001)
 * Desc:  PREPROJECT-03, gethostname
 */

#include<stdio.h>
#include<stdlib.h>   /* For 'gethostname()' */
#include<unistd.h>   /* For exit(), EXIT_SUCCESS and FAILURE*/ 
    
#define ARRAY_SIZE 80   /* Control the array size from one place */

int main( void ) {
    /* Array to store the hostname */
    char hostname[ ARRAY_SIZE ];

    /* Attempt to get hostname */
    if ( gethostname(hostname, ARRAY_SIZE) == 0 ) {
        /* If gethostname() returns 0, call was successful*/
        printf("Local hostname: %s\n", hostname);
    } else {
        /* If gethostname() returns -1, there was an error */
        printf( "ERROR: gethostname()\n" );
        /* Exit the program with a failure status */
        exit(EXIT_FAILURE);

    }
    /* Made it to the end, exit the program successfully*/
    exit(EXIT_SUCCESS);
}