#include <stdio.h>
#include <sys/time.h>
#include <termios.h>

#ifndef STDIN_FILENO
# define STDIN_FILENO 0
#endif

/* Use of raw mode requires that you understand how to manage signals
   and all that.  */
#ifdef USE_RAW_MODE
# define RAW_MODE(x) tty_raw((x))
#else
# define RAW_MODE(x) tty_cbreak((x))
#endif

static struct termios save_termios;

static int
tty_cbreak (int fd)
{
  struct termios ios;

  if (tcgetattr (fd, &save_termios) < 0)
    return -1;

  ios = save_termios;
  ios.c_lflag &= ~(ICANON | ECHO);
  ios.c_cc[VMIN] = 1;
  ios.c_cc[VTIME] = 0;

  return tcsetattr (fd, TCSAFLUSH, &ios);
}

static int
tty_raw (int fd)
{
  struct termios ios;

  if (tcgetattr (fd, &save_termios) < 0)
    return -1;

  ios = save_termios;
  ios.c_lflag &= ~(ICANON | ECHO | IEXTEN | ISIG);
  ios.c_lflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  ios.c_lflag &= ~(CSIZE | PARENB);
  ios.c_lflag |= CS8;
  ios.c_lflag &= ~(OPOST);

  ios.c_cc[VMIN] = 1;
  ios.c_cc[VTIME] = 0;

  return tcsetattr (fd, TCSAFLUSH, &ios);
}

static int
tty_reset (int fd)
{
  return tcsetattr (fd, TCSAFLUSH, &save_termios);
}

int
kbdhit (void)
{
  fd_set rfds;
  struct timeval tv;

  /* Watch stdin (fd 0) to see when it has input. */
  FD_ZERO (&rfds);
  FD_SET (STDIN_FILENO, &rfds);

  /* Return immediately. */
  tv.tv_sec = 0;
  tv.tv_usec = 0;

  /* Must be in raw or cbreak mode for this to work correctly. */
  return select (STDIN_FILENO + 1, &rfds, NULL, NULL, &tv) &&
    FD_ISSET (STDIN_FILENO, &rfds);
}

int
getch (void)
{
  int c;

  /* Must be in raw or cbreak mode for this to work correctly. */
  if (read (STDIN_FILENO, &c, 1) != 1)
    c = EOF;

  return c & 0xff;
}

int
main ()
{
  int i;
  char c;

  puts ("Press Q to quit ... ");
  fflush (stdout);

  RAW_MODE (STDIN_FILENO);
  while (1)
    {
      fputs ("going to sleep for 2 seconds ... ", stdout);
      fflush (stdout);
      sleep (2);
      fputs ("awake. Checking for key\n", stdout);
      fflush (stdout);
      if (kbdhit ())
	{
	  int c;
	  fputs ("yes ... ", stdout);
	  fflush (stdout);
	  c = getch ();
	  fprintf (stdout, "%c\n", c);
	  fflush (stdout);
	  if (c == 'q' || c == 'Q' || c == EOF)
	    break;
	}
      fputs ("Nope. back to sleep\n", stdout);
    }
  tty_reset (STDIN_FILENO);

  puts ("\nDone.");
  return 0;
}
