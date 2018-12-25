/*
 *****************************************************************************
 * MODULE: ECHOSTAR OS-Shell
 *
 * FILE  : poortool.c
 *
 * AUTHOR: Richard Onyett 
 * EMAIL :
 *
 * PURPOSE:  Poor Version of Testtool :)
 *
 * $Revision: $
 * $History:  $
 *****************************************************************************
 */

/*
******************************************************************************
Includes
******************************************************************************
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "list.h"

/*
******************************************************************************
Private Constants
******************************************************************************
*/
#ifndef TESTTOOL
#define parse_t char
#endif
#ifndef BOOL
#define BOOL int
#endif
 
#define SEPARATORS       " \t\n\r,;"
#define HEAP_DEBUG       // Define to see the heap parition
#define TRUE             1
#define FALSE            0
#define INT_MEMSTART     0x80000140
#define INT_MEMEND       0x80002000

#define KEY_BACKSP       0x8   /* backspace */
#define KEY_UP           0x9   /* ctrl-i */
#define KEY_DOWN         0xF   /* ctrl-o */
#define KEY_RIGHT        0x10  /* ctrl-p */
#define KEY_LEFT         0x15  /* ctrl-u */
#define UNIX_KEY_DOWN    0xA   /* ctrl-o on Unix */
#define UNIX_KEY_BACKSP  0x7F  /* backspace on Unix */

#define NUMBER_OF_HANDLES 3

/*
******************************************************************************
Private Types
*****************************************************************************
*/

/*
******************************************************************************
Private variables (static)
******************************************************************************
*/
static int base;                /* Radix for numbers         */
list_t *list_base[NUMBER_OF_HANDLES];          /* bucket of list storage    */
int list_handles[NUMBER_OF_HANDLES];           /* Handle storage            */

/*
******************************************************************************
Private Macros
******************************************************************************
*/

/*
******************************************************************************
Global variables
******************************************************************************
*/

/*
******************************************************************************
Exported Global variables
******************************************************************************
*/

/*
******************************************************************************
Prototypes of all functions contained in this file (in order of occurance)
******************************************************************************
*/
static int pollkey(void);
static int io_read(unsigned char* prompt, char* buffer,long buflen);
static BOOL match(char *str1,const char *str2);
static void GetCommandLine(char *Buffer, int *cargc,char *cargv[]);
static BOOL Eval(char string[], long int *result);
static void tt_help (int argc, char *argv[]);
static BOOL GetCLI(void);
void poortool_Init(void);

/*
------------------------------------------------------------------------------
 Name   : static int GetFreeHandle(void) {
 Purpose: Look for a free handle
 In     : None
 Out    : int
 Errors :
 Note   : 
------------------------------------------------------------------------------
*/
static int GetFreeHandle(void) {
  int i;

  for (i=0; i < NUMBER_OF_HANDLES; i++) {
    if (list_handles[i] != 1 ) {
      return i;
    }
  }

  return -1;
}  

/*
------------------------------------------------------------------------------
 Name   : static int pollkey(void)
 Purpose: Look for a Keypress.
 In     : None
 Out    : int Key
 Errors :
 Note   : 
------------------------------------------------------------------------------
*/
static int pollkey(void)
{
  char key;

  key = fgetc(stdin);

  return (int)key;
}

/*
------------------------------------------------------------------------------
 Name   : static int io_read(unsigned char* prompt, char* buffer,long buflen)
 Purpose: Perform read of input
 In     : char *prompt -
          char *buffer
          int buflen
 Out    : 
 Errors :
 Note   : 
------------------------------------------------------------------------------
*/
static int io_read(unsigned char* prompt, char* buffer,long buflen)
{
  int cnt = 0;

  printf((char *)prompt);
  fflush(stdout);
  
  fgets(buffer, (size_t)buflen, stdin);
  //  printf ("buffer %c %d\n", buffer[0], buffer[0]);
  return(cnt);
}

/*
------------------------------------------------------------------------------
 Name   : static int match(char *str1,char *str2) 
 Purpose: String matches ??  
 In     : char *str1
          char *str2
 Out    :
 Errors :
 Note   : 
------------------------------------------------------------------------------
*/
static BOOL match(char *str1,const char *str2)
{
  int i;

  for (i=0; i < (int)strlen(str2); i++)
  {
    if (str1[i] != str2[i] )
      return FALSE;
  }

  return(!(strncmp(str1,str2, strlen(str1))));
}

/*
------------------------------------------------------------------------------
 Name   : static void GetCommandLine(char *Buffer, int *cargc,char *cargv[])
 Purpose: Get the command line inside of Buffer
 In     : char *Buffer - All of the commands
          int  *cargc  - Number of Args
          char *cargv  - The Args List
 Out    :
 Errors :
 Note   : Attempt to tokenize the Buffer and return as a set of Args,
------------------------------------------------------------------------------
*/
static void GetCommandLine(char *Buffer, int *cargc,char *cargv[])
{
  char *Token;
  char *bPtr;

  *cargc = 0;

  bPtr = Buffer;

  Token = strtok ( (char *)bPtr, SEPARATORS );   // Convert to arguments
  while ( Token != NULL )
  {
    cargv[*cargc] = (char *)(Token);    // Copy Tokenised data into Array
    (*cargc)++;
    Token = strtok ( NULL, SEPARATORS );
  }
}

/*
------------------------------------------------------------------------------
 Name   : static int Eval(char string[], int *result) 
 Purpose: Convert the text string into dec, bin or hex.
 In     : char *string - Convert string
 Out    : int *result  - String as integer
 Errors :
 Note   : Assumes base 16. Change to 10,2 for Dec/Bin
        
          Surely Quicker:  *result = atoi(string[Ptr]);
------------------------------------------------------------------------------
*/
static BOOL Eval(char string[], long int *result) {
  int i = 0;
  int Ptr;
  int offset = 0;

  *result = 0L;
  base = 10;  /* Assumes HEX Mode */

  /* Skip any white space */
  for (Ptr=0; isspace(string[Ptr]); Ptr++);

  /*
  -- Validate input
  */
  switch ( string[Ptr] ) {
    case '$':        /* HEX Mode */
    {
      i = Ptr+1;
      for (Ptr=0; isspace(string[Ptr]); Ptr++);
      Ptr++;
      while ( string[Ptr] != '\0' )
      {
        if ( isxdigit(string[Ptr]) == 0 )
          return FALSE;
        Ptr++;
      }
      break;
    }
  }

  /*
  -- Convert String
  */
  while ( string[i] != '\0' ) {
    int temp;
    temp = string[i]-'0';
    if (string[i] >= 'A') temp -= ('A'-'9'-1);
    if (string[i] >= 'a') temp -= ('a' - 'A');
    if ((temp < base) && (temp >=0))
      *result = (*result * base) + temp;
    i++;
  }

  *result = *result + offset;

  return TRUE;
}

static void tt_list_create (int argc, char *argv[]) {
  long int freeHandle = 0;

  freeHandle = GetFreeHandle();
  if ( freeHandle == -1 ) {
    printf("poortool: Ran out of list handle space\n");
    return;
  }

  list_base[freeHandle] = list_create();

  if (list_base[freeHandle] != NULL ) {
    printf("list_create %ld\n", freeHandle);
  }

  list_handles[freeHandle] = 1;   /* Mark handle as being in use */
}

static void tt_list_destroy (int argc, char *argv[]) {
  long int Handle = 0;

  if ( argc == 1) {
    Eval(argv[0], &Handle);

    if ( list_base[Handle] != NULL) {
      list_clear (list_base[Handle]);
      list_handles[Handle] = 0;   /* Mark handle as being free */      
    } else {
      printf("No list found\n");      
    }
  } else {
    printf("No handle supplied\n");
  }
}

static void tt_list_show (int argc, char *argv[]) {
  long int Handle = 0;

  if ( argc == 1) {
    Eval(argv[0], &Handle);

    if ( list_base[Handle] != NULL) {
      list_show (list_base[Handle]);
    } else {
      printf("No list found\n");      
    }
  } else {
    printf("No handle supplied\n");
  }
}

static void tt_list_add (int argc, char *argv[]) {
  long int Handle = 0;
  long int value = 0;
  
  if ( argc == 2) {
    Eval(argv[0], &Handle);
    Eval(argv[1], &value);

    if ( list_base[Handle] != NULL) {
      list_add_element(list_base[Handle], value);      
    } else {
      printf("No list found\n");      
    }
  } else {
    printf("No handle supplied\n");
  }
}

static void tt_list_add_front (int argc, char *argv[]) {
  long int Handle = 0;
  long int value = 0;
  
  if ( argc == 2) {
    Eval(argv[0], &Handle);
    Eval(argv[1], &value);

    if ( list_base[Handle] != NULL) {
      list_add_front(list_base[Handle], value);      
    } else {
      printf("No list found\n");      
    }
  } else {
    printf("No handle supplied\n");
  }
}

/*
------------------------------------------------------------------------------
 Name   : static void fHelp(int argc, char *argv[])
 Purpose: Show all commands
 In     : int  argc
          char *argv[]
 Out    :
 Errors :
 Note   :
------------------------------------------------------------------------------
*/
static void tt_help(int argc, char *argv[])
{
  printf("**** PoorTool ****\n");
  printf("clist                      Create a dynamic list returns handle\n");
  printf("dlist  <handle>            Delete dynamic list                 \n");  
  printf("alist  <handle> <value>    Add value to list                   \n");
  printf("aflist <handle> <value>    Add value to list at the front      \n");  
  printf("dump  <handle>             Show list                           \n");
  printf("exit                       Quit from OS Monitor                \n");
}

/*
------------------------------------------------------------------------------
 Name   : static BOOL GetCLI(void)
 Purpose: Command Line Processor 
 In     : None.
 Out    : None.
 Errors :
 Note   : This routine runs until the EXIT command is entered and it will go
          back into looking for the next keypress 
------------------------------------------------------------------------------
*/
static BOOL GetCLI(void) {
  static char *Cargv[6];                /* Argument buffer for Commands */
  static int  Cargc = 0;                /* Argument count for Commands  */
  static char Buffer[30];               /* Buffer for parsing CLI       */
  BOOL Going = TRUE;                    /* Continue until EXIT          */

  while ( Going ) {
    io_read((unsigned char *)"poortool>", Buffer, sizeof(Buffer));
    GetCommandLine(Buffer, &Cargc, Cargv);
    
    /*
     * Match up the commands
     */
    if      (match(Cargv[0],"help"       )) tt_help  ( Cargc-1, &Cargv[1]);
    else if (match(Cargv[0],"clist"      )) tt_list_create    ( Cargc-1, &Cargv[1]);
    else if (match(Cargv[0],"dlist"      )) tt_list_destroy   ( Cargc-1, &Cargv[1]);    
    else if (match(Cargv[0],"alist"      )) tt_list_add       ( Cargc-1, &Cargv[1]);
    else if (match(Cargv[0],"aflist"     )) tt_list_add_front ( Cargc-1, &Cargv[1]);        
    else if (match(Cargv[0],"dump"       )) tt_list_show      ( Cargc-1, &Cargv[1]);
    else if (match(Cargv[0],"exit"       )) Going = FALSE;
    else printf ("??\n");
  }

  return FALSE;
}

/*
------------------------------------------------------------------------------
 Name   : void Poortool_Init(void)
 Purpose: Visible entry point for PoorTool.
 In     : 
 Out    : 
 Errors :
 Note   : Waits for keypress and enters into PoorTool world.
------------------------------------------------------------------------------
*/
void poortool_init(void) {
  BOOL Going = true;
  int i;

  /*
   * initialise the handles storage
   */
  for (i=0; i< NUMBER_OF_HANDLES; i++) {
    list_handles[i] = 0;
  }
  
  printf("Press ANY key for Poortool\n");
  
  while (Going) {
    int ip_char = 0;

   /*
    * Test for any keypress to enter the mode
    */
    while (ip_char == 0) {
      for (int i; i < 10000; i++);
      ip_char = pollkey();
    }
    Going = GetCLI();                         /* Execute the Command Line */
  }
}

/*
 * Fin
 */
