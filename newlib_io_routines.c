#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <samc21.h>

/*
    quick and dirty code to provide console I/O for newlib's printf(), etc.

    Copyright (C) 2017 Peter Lawrence

    Permission is hereby granted, free of charge, to any person obtaining a 
    copy of this software and associated documentation files (the "Software"), 
    to deal in the Software without restriction, including without limitation 
    the rights to use, copy, modify, merge, publish, distribute, sublicense, 
    and/or sell copies of the Software, and to permit persons to whom the 
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in 
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
    DEALINGS IN THE SOFTWARE.
*/

void *_sbrk (int nbytes)
{
	(void)nbytes;

	errno = ENOMEM;
	return (void *)-1;
}

int _close (int file)
{
	(void)file;
	errno = EBADF;
  
	return -1; /* Always fails */
}

extern int __putchar(int c);

int _write (int file, char *buf, int nbytes)
{
	int count = nbytes;
	(void)file;

	while (count--)
		__putchar(*buf++);
        
	return nbytes;
}

int _fstat (int file, struct stat *st)
{
	(void)file;
	st->st_mode = S_IFCHR;
	return 0;
}

int _isatty (int file)
{
	(void)file;
	return 1;
}

int _lseek (int file, int offset, int whence)
{
	(void)file;
	(void)offset;
	(void)whence;
	return 0;
}

int _read (int file, char *ptr, int len)
{
	(void)file;
	(void)ptr;
	(void)len;
	return 0; /* EOF */
}

int _kill(pid_t pid, int sig)
{
	(void)pid;
	(void)sig;
	return 0;
}

pid_t _getpid(void)
{
	return 0;
}
