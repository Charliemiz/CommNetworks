/*
 * Auth: Charlie Misbach
 * Date: 03-27-24 (Due: 04-07-24)
 * Course: CSCI-3550 (Sec: 001)
 * Desc:  PREPROJECT-04, Read/Write Files
 */

#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<signal.h>  /* Needed for 'signal()' function. */
#define BUF_SIZE  (10*1024*1024) /* Create a buffer large enough to hold 10MB of data. */

/* Function prototypes */
void SIGINT_handler( int sig );
void cleanup(void);

char *buf = NULL;
int fd_in = -1; /* File descriptor for input file */
int fd_out = -1; /* File descriptor for output file */

int bytes_read;
int bytes_written;


int main(int argc, char *argv[]) {
    
    /* Initialize file counter */
    int file_counter = 1;

    /* This array will hold dynamic filenames that we can
        construct using the "snprintf()" function. */
    char fname[80];

    int i;

    /* Allocate memory for the buffer */ 
    buf = (char *)malloc(BUF_SIZE);

    if (buf == NULL) {
        fprintf(stderr, "ERROR: Could not allocate memory.\n");
        exit(EXIT_FAILURE);
    }

    /* Install our function to catch 'CTRL+C' */ 
    signal(SIGINT, SIGINT_handler);

    /* Enter this if statement if not enough arguments were provided (no file names) */
    if (argc < 2) {
        /* Print error */
        fprintf(stderr, "ERROR: Need to supply one or more files as input. Try again.\n");

        /* clean up*/
        cleanup();

        /* exit*/
        exit(EXIT_FAILURE);
    }

    
    for(i = 1; i < argc; i++) {
        fd_in = open(argv[i], O_RDONLY);
        if (fd_in < 0) {
            fprintf(stderr, "ERROR: Could not open file '%s'.\n", argv[i]);
        
            /* Skip to the next file if we cannot open this one */
            continue; 
        }
        
        /* Print statement that we are reading the file */
        printf("Reading: %s...\n", argv[i]);
        
        bytes_read = read(fd_in, buf, BUF_SIZE);
        if (bytes_read < 0) {
            /* Issue error */
            fprintf( stderr, "ERROR: Unable to read file: %s\n", argv[i] );

            /* Clean up */
            cleanup();

            /* Terminate the program. */
            exit( EXIT_FAILURE );
        }

        
        /* Close file if we successfully read from it */
        close(fd_in);
        fd_in = -1;

        /* Construct a name dynamically. (Will result in "file-01.dat") */
        sprintf( fname, "file-%02d.dat", file_counter );

        fd_out = open(fname, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);

        if( fd_out < 0 ) {
            /* Issue the error */
            fprintf( stderr, "ERROR: Could not create: %s\n", fname );

            /* Clean up. */
            cleanup();

            /* Exit. */
            exit( EXIT_FAILURE );

        } 
        
        /* Write the data in the buffer... */
        bytes_written = write( fd_out, buf, (size_t) bytes_read );

        /* Check if we wrote the correct number of bytes (the same # we read) */
        if (bytes_written != bytes_read ) {
            /* Issue a proper error. */
            fprintf( stderr, "ERROR: Error writing ALL bytes.\n" );

            /* Clean up. */
            cleanup();

            /* Terminate. */
            exit( EXIT_FAILURE );

        } 

        /* Print that we are writing to the file */
        printf("Writing: %s\n", fname);

        /* Successfully written to the file, now increment the file counter */
        file_counter++; 

        close(fd_out);
        fd_out = -1;

    }

    return 0; /* return main() */
} /* end main() */ 


/* global signal handler function */
void SIGINT_handler( int sig ) {

   /* Issue a message */
   fprintf( stderr, "Whoops!  Program interrupted!\n" );
   
   /* Cleanup */
   cleanup();

   /* Terminate the program HERE */
   exit( EXIT_FAILURE );

} /* end SIGINT_handler() */

void cleanup(void) {
    /* Deallocate the memory from the buffer */
    if(buf != NULL) {
        free( buf );
        buf = NULL;
    }
    /* Close the input file, if open */
    if (fd_in >= 0) {
        close(fd_in);
        fd_in = -1; /* Mark as closed */ 
    }
    /* Close the output file, if open */
    if (fd_out >= 0) {
        close(fd_out);
        fd_out = -1; /* Mark as closed */ 
    }
} /* end cleanup() */



