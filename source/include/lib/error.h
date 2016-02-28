/* Copyright (C) 2013 by Klim Kireev <edvmartell@gmail.com> <https://github.com/proffK>

*   This file is part of kedos.

*   kedos is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.

*   kedos is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.

*   You should have received a copy of the GNU General Public License
*   along with kedos.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef __ERROR_
#define __ERROR_

#ifdef errno
#undef errno
#endif

extern int errno;

enum errors {

	E2BIG = 1,
	   //Argument list too long.
	EACCES,
	   //Permission denied.
	EADDRINUSE,
	   //Address in use.
	EADDRNOTAVAIL,
	   //Address not available.
	EAFNOSUPPORT,
	   //Address family not supported.
	EAGAIN,
	   //Resource unavailable, try again (may be the same value as [EWOULDBLOCK,).
	EALREADY,
	   //Connection already in progress.
	EBADF,
	   //Bad file descriptor.
	EBADMSG,
	   //Bad message.
	EBUSY,
	   //Device or resource busy.
	ECANCELED,
	   //Operation canceled.
	ECHILD,
	   //No child processes.
	ECONNABORTED,
	   //Connection aborted.
	ECONNREFUSED,
	   //Connection refused.
	ECONNRESET,
	   //Connection reset.
	EDEADLK,
	   //Resource deadlock would occur.
	EDESTADDRREQ,
	   //Destination address required.
	EDOM,
	   //Mathematics argument out of domain of function.
	EDQUOT,
	   //Reserved.
	EEXIST,
	   //File exists.
	EFAULT,
	   //Bad address.
	EFBIG,
	   //File too large.
	EHOSTUNREACH,
	   //Host is unreachable.
	EIDRM,
	   //Identifier removed.
	EILSEQ,
	   //Illegal byte sequence.
	EINPROGRESS,
	   //Operation in progress.
	EINTR,
	   //Interrupted function.
	EINVAL,
	   //Invalid argument.
	EIO,
	   //I/O error.
	EISCONN,
	   //Socket is connected.
	EISDIR,
	   //Is a directory.
	ELOOP,
	   //Too many levels of symbolic links.
	EMFILE,
	   //File descriptor value too large.
	EMLINK,
	   //Too many links.
	EMSGSIZE,
	   //Message too large.
	EMULTIHOP,
	   //Reserved.
	ENAMETOOLONG,
	   //Filename too long.
	ENETDOWN,
	   //Network is down.
	ENETRESET,
	   //Connection aborted by network.
	ENETUNREACH,
	   //Network unreachable.
	ENFILE,
	   //Too many files open in system.
	ENOBUFS,
	   //No buffer space available.
	ENODATA,
	   //No message is available on the STREAM head read queue.
	ENODEV,
	   //No such device.
	ENOENT,
	   //No such file or directory.
	ENOEXEC,
	   //Executable file format error.
	ENOLCK,
	   //No locks available.
	ENOLINK,
	   //Reserved.
	ENOMEM,
	   //Not enough space.
	ENOMSG,
	   //No message of the desired type.
	ENOPROTOOPT,
	   //Protocol not available.
	ENOSPC,
	   //No space left on device.
	ENOSR,
	   //[OB XSR, [Option Start, No STREAM resources. [Option End,
	ENOSTR,
	   //[OB XSR, [Option Start, Not a STREAM. [Option End,
	ENOSYS,
	   //Function not supported.
	ENOTCONN,
	   //The socket is not connected.
	ENOTDIR,
	   //Not a directory or a symbolic link to a directory.
	ENOTEMPTY,
	   //Directory not empty.
	ENOTRECOVERABLE,
	   //State not recoverable.
	ENOTSOCK,
	   //Not a socket.
	ENOTSUP,
	   //Not supported (may be the same value as [EOPNOTSUPP,).
	ENOTTY,
	   //Inappropriate I/O control operation.
	ENXIO,
	   //No such device or address.
	EOPNOTSUPP,
	   //Operation not supported on socket (may be the same value as [ENOTSUP,).
	EOVERFLOW,
	   //Value too large to be stored in data type.
	EOWNERDEAD,
	   //Previous owner died.
	EPERM,
	   //Operation not permitted.
	EPIPE,
	   //Broken pipe.
	EPROTO,
	   //Protocol error.
	EPROTONOSUPPORT,
	   //Protocol not supported.
	EPROTOTYPE,
	   //Protocol wrong type for socket.
	ERANGE,
	   //Result too large.
	EROFS,
	   //Read-only file system.
	ESPIPE,
	   //Invalid seek.
	ESRCH,
	   //No such process.
	ESTALE,
	   //Reserved.
	ETIME,
	   // Stream ioctl() timeout.
	ETIMEDOUT,
	   // Connection timed out.
	ETXTBSY,
	   //Text file busy.
	EWOULDBLOCK,
	   //Operation would block (may be the same value as [EAGAIN,).
	EXDEV
	    //Cross-device link. 
};
#endif
