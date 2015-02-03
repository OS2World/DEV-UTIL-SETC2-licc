// licc.c - load icc
// Written by Matt Osborn 75230,1346
// Suggested by Ian Ameline  70400,2356

// This program will load the major elements (maybe even all) of the
// IBM C Set/2 compiler into memory for faster access times.

// This program has been generalized to accept a list of command line
// arguments that specify which programs to load. If such a list is not
// provided, a default list will be used.

// Not much out of the base
#define INCL_DOSPROCESS
#include <os2.h>

// Minimal C runtime also
#include <stdio.h>

// A few magic cookies
#define LICC_COUNT     4                // Default count of programs
#define LICC_MAIN      "icc.exe"        // Programs to load
#define LICC_DDE4BE    "dde4be.exe"
#define LICC_DDE4BE0   "dde4be0.exe"
#define LICC_DDE4FE    "dde4fe.exe"
#define LICC_DEFAULT   "default"
#define LICC_USER      "user"

// And a few error codes
#define LICCERR_OK      0     // Everything is fine
#define LICCERR_NOLOAD  1     // No programs loaded

// Function prototypes
APIRET exec (PSZ pszName);
int main (int argc, char *argv[]);

// The guy that runs the show
int main (int argc, char *argv[])
{
int count = 0;              // Count of successfully loaded programs
int total = argc -1;        // Total count of programs to load
int args = argc;            // Copy of argument count
char **argp;                // Copy of argument pointer
char *pszList;              // Program list

char *argd [5] = {          // Default arguments
  NULL,
  LICC_MAIN,
  LICC_DDE4BE,
  LICC_DDE4BE0,
  LICC_DDE4FE
};

  // Any arguments?
  if (argc > 1) {

    // Yes, use user supplied list
    argp    = argv;
    args    = argc;
    pszList = LICC_USER;

  } else {

    // Use defaults
    total   = LICC_COUNT;
    args    = LICC_COUNT + 1;
    pszList = LICC_DEFAULT;
    argd[0] = argv[0];
    argp    = argd;
  }


  // Sign on, just to be obnoxious
  printf ("\n%s: loading %s program list\n", argp[0], pszList);

  // Loop for all arguments
  while (args-- > 1) {

    // Try to load program (the guy that does the work)
    if (!exec (argp[args])) {

       // Successful, bump count of loaded programs
       count++;
    }
  }

  // Were any programs loaded?
  if (count) {

    // We were successful (to some degree)
    printf ("\n\n%d out of %d program(s) were successfully loaded.", count, total);

    // Notify user that we're sleeping
    printf ("\n\nNow sleeping, type CTRL-C to end program\n\n");

    // Sleep for however long
    DosSleep (-1);

  } else {

     // No programs loaded
     printf ("\nNo programs successfully loaded\n");
  }

  // This is for you batch file guys
  return ((count) ? LICCERR_OK : LICCERR_NOLOAD);
}


// The guy that does the work
APIRET exec (PSZ pszName)
{
RESULTCODES rcs;
CHAR   achName [CCHMAXPATH];
APIRET rc;

  // Inform user of program load (I like being obnoxious)
  printf ("\nLoading program: %-32s - ", pszName);

  // Initialize failed module name buffer
  *achName = '\0';

  // Now attempt the actual load
  rc = DosExecPgm (achName, sizeof(achName), EXEC_LOAD, 0, 0, &rcs, pszName);

  // Any problem?
  if (rc) {
    // Problem of some sort, notify user
    printf ("failed, error: %lx,", rc);

    // Any module name returned?
    if (*achName) {
      // Yes, print module name also
      printf (" module: %s", achName);
    }

  } else {

    // No problem loading program, let's brag about it
    printf (" process id: %ld", rcs.codeTerminate);
  }

  // Return results
  return (rc);
}
