/* vi: set sw=4 ts=4: */
/*
 * lseek() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <unistd.h>
#include <cancel.h>

#ifdef __NR_lseek
# define __NR___lseek_nocancel __NR_lseek
_syscall3(off_t, __NC(lseek), int, fd, off_t, offset, int, whence)
#else
# include <errno.h>
off_t __NC(lseek)(int fd, off_t offset attribute_unused, int whence)
{
	if (fd < 0) {
		__set_errno(EBADF);
		return -1;
	}

	switch(whence) {
		case SEEK_SET:
		case SEEK_CUR:
		case SEEK_END:
			break;
		default:
			__set_errno(EINVAL);
			return -1;
	}

	__set_errno(ENOSYS);
	return -1;
}
#endif
CANCELLABLE_SYSCALL(off_t, lseek, (int fd, off_t offset, int whence), (fd, offset, whence))
lt_libc_hidden(lseek)
#if defined __UCLIBC_HAS_LFS__ && (__WORDSIZE == 64 || (!defined __NR__llseek && !defined __NR_llseek))
strong_alias_untyped(__NC(lseek),__NC(lseek64))
strong_alias_untyped(lseek,lseek64)
lt_strong_alias(lseek64)
lt_libc_hidden(lseek64)
#endif
