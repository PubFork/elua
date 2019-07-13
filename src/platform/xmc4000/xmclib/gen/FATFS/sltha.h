/**
 * @file sltha.h
 * @date 2016-07-20
 *
 * NOTE:
 * This file is generated by DAVE. Any manual modification done to this file will be lost when the code is
 * regenerated.
 */
/**
 * @cond
 ***********************************************************************************************************************
 * FATFS v4.0.16 Provides the support for standard FATFS library
 *
 * Copyright (c) 2015-2017, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this list of conditions and the  following
 *   disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *   following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *   Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 *   products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT  OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes
 * with Infineon Technologies AG (dave@infineon.com).
 ***********************************************************************************************************************
 *
 * Change History
 * --------------
 *
 * 2015-12-01:
 *     - Initial version<br>
 *
 * @endcond
 *
 */

#ifndef SLTHA_H
#define SLTHA_H

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#include "fatfs_conf.h"

#if (FATFS_STANDARDLIBRARY == 1U)
#include "ff_Src/integer.h"
#include "ff_Src/ff.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>

#if defined (__GNUC__) || defined (__TASKING__)
  #include <fcntl.h>
  #include <unistd.h>
#endif

#ifdef __GNUC__
#if _FS_REENTRANT
  #include <reent.h>
#endif
#elif __CC_ARM
#if _FS_REENTRANT
  #include <rt_sys.h>
  #include <RTL.h>
#endif
#elif __ICCARM__
 #include <yfuns.h>
#elif __TASKING__
 #include <io.h>
#endif

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* File creation Flags */
#if defined(__GNUC__) || defined(__TASKING__)
  #define       SLTHA_RDONLY       (O_RDONLY)
  #define       SLTHA_WRONLY       (O_WRONLY)
  #define       SLTHA_RDWR         (O_RDWR)
  #define       SLTHA_APPEND       (O_APPEND)
  #define       SLTHA_CREAT        (O_CREAT)
  #define       SLTHA_TRUNC        (O_TRUNC)
  #define       SLTHA_EXCL         (O_EXCL)
  #define       SLTHA_SYNC         (O_SYNC)
  #define       SLTHA_NONBLOCK     (O_NONBLOCK)
  #define       SLTHA_NOCTTY       (O_NOCTTY)
  #define       SLTHA_RDWRMASK     (O_ACCMODE)

#elif defined __CC_ARM
  #define       SLTHA_RDONLY       OPEN_R
  #define       SLTHA_WRONLY       OPEN_W
  #define       SLTHA_RDWR         OPEN_PLUS
  #define       SLTHA_APPEND       OPEN_A

#elif defined __ICCARM__
  #define       SLTHA_RDONLY       _LLIO_RDONLY
  #define       SLTHA_WRONLY       _LLIO_WRONLY
  #define       SLTHA_RDWR         _LLIO_RDWR
  #define       SLTHA_APPEND       _LLIO_APPEND
  #define       SLTHA_CREAT        _LLIO_CREAT
  #define       SLTHA_TRUNC        _LLIO_TRUNC
  #define       SLTHA_EXCL         _LLIO_EXCL
  #define       SLTHA_RDWRMASK     _LLIO_RDWRMASK
#endif


/** Standard Input File Descriptor */
#define STDIN_HANDLE         (0U)
/** Standard Output File Descriptor */
#define STDOUT_HANDLE         (1U)
/** Standard Error File Descriptor */
#define STDERR_HANDLE          (2U)

#ifdef __GNUC__
/** Maximum Number of Files that can be opened.*/
  #define MAX_OPEN_FILES      (FOPEN_MAX)
#elif __CC_ARM
  #define MAX_OPEN_FILES                                   (_SYS_OPEN)
#elif __ICCARM__
  #define MAX_OPEN_FILES                                    (FOPEN_MAX)
#elif __TASKING__
  #define MAX_OPEN_FILES                                    (FOPEN_MAX)
#endif


/** Empty Slot Value */
#define SLTHA_EMPTY_SLOT                                        (-1U)
/** Slot is allocated but it is not in use yet.  */
#define SLTHA_ALLOCATED_NOT_IN_USE                              (-2U)
/** Fat Fs Handle  Value adjusted to stay away from Internal Handles. */
#define MONITOR_FATFS                                           (3U)

#define SLTHA_SUCCESS                                           (0U)

#if defined (__CC_ARM) || (__ICCARM__)
typedef short  mode_t   ;
#elif defined (__TASKING__)
typedef unsigned char  mode_t;
#endif

#ifdef __CC_ARM
#pragma import(__use_no_semihosting_swi)
/* The following macro definitions may be used to translate this file:
   STDIO - use standard Input/Output device default is NOT used) */
/** Standard IO device handles. */
#define STDIN   (0x8001)
#define STDOUT  (0x8002)
#define STDERR  (0x8003)

#endif

#if defined __GNUC__
/* In Non-RTOS mode */
#if !_FS_REENTRANT
/**
 * This opens the file specified by the Path in the mode
 * specified by the Flags and returns the file descriptor if file is successfully
 * opened or created.
 */
#define SLTHA_Open()     int _open(const TCHAR *Path, int Flags, ...)
/**
 * This closes the file specified by the file descriptor.
 */
#define SLTHA_Close()    int _close(int Fd)
/**
 * This reads Length bytes of data from the file specified
 * by the file descriptor into the buffer pointer.
 *
 */
#define SLTHA_Read()    _ssize_t _read(int Fd, void *BufferPtr, size_t Length)
/**
 * This writes Length bytes of data into the file specified
 * by the File descriptor. The data to write is pointed by buffer pointer
 */
#define SLTHA_Write()   _ssize_t _write(int Fd, const void *BufferPtr, size_t Length)
/**
 * This moves the file pointer of a file object specified by the
 * file descriptor to a particular offset. The value of offset determines the new position,
 * in one of three ways selected by the value of DirMode.<BR>
 * SEEK_SET: Offset from the beginning of the file desired. <BR>
 * SEEK_CUR: Offset is relative to the current file position.<BR>
 * SEEK_END: Offset is relative to the current end of file.<BR>
 */
#define SLTHA_Lseek()   off_t _lseek(int Fd, off_t Offset, int DirMode)
/**
 * This deletes an existing file or directory specified by the directory path.
 */
#define SLTHA_Remove()  int _unlink(const char  *Path)
/**
 * This gets file status on basis of file descriptor passed.
 * The file status information is copied in the stat structure.
 */
#define SLTHA_FileStatus()  int _fstat(int Fd, struct stat *FileStatusPtr)
/**
 * This gets file status on basis of file path passed.
 * The file status information is copied in the stat structure.
 */
#define SLTHA_Status()      int _stat(const char *Path, struct stat *FileStatusPtr)
/**
 * This renames/moves a file or directory
 */
#define SLTHA_Rename()      int rename(const char *Oldpath, const char *Newpath)
/**
 * This queries whether output stream is a terminal.
 */
#define SLTHA_IsAtty()      int _isatty(int Fd)
/* In RTOS mode */
#elif _FS_REENTRANT
/**
 * This opens the file specified by the Path in the mode
 * specified by the Flags and returns the file descriptor if file is successfully opened or created.
 */
#define SLTHA_Open()     int _open_r(struct _reent *ReentPtr, const TCHAR *Path, int Flags, int Mode)

/**
 * This closes the file specified by the file descriptor.
 */
#define SLTHA_Close()    int _close_r(struct _reent *ReentPtr, int Fd)

/**
 * This reads Length bytes of data from the file specified
 * by the file descriptor into the buffer pointer.
 *
 */
#define SLTHA_Read()     _ssize_t _read_r(struct _reent *ReentPtr, int Fd, void *BufferPtr, size_t Length)

/**
 * This writes Length bytes of data into the file specified
 * by the File descriptor. The data to write is pointed by buffer pointer
 */
#define SLTHA_Write()    _ssize_t _write_r(struct _reent *ReentPtr, int Fd, const void *BufferPtr, size_t Length)
/**
 * This moves the file pointer of a file object specified by the
 * file descriptor to a particular offset. The value of offset determines the new position,
 * in one of three ways selected by the value of DirMode.<BR>
 * SEEK_SET: Offset from the beginning of the file desired. <BR>
 * SEEK_CUR: Offset is relative to the current file position.<BR>
 * SEEK_END: Offset is relative to the current end of file.<BR>
 */
#define SLTHA_Lseek()    off_t _lseek_r(struct _reent *ReentPtr, int Fd, off_t Offset, int DirMode)
/**
 * This deletes an existing file or directory specified by the directory path.
 */
#define SLTHA_Remove()   int _unlink_r(struct _reent *ReentPtr, const char *Path)
/**
 * This gets file status on basis of file descriptor passed.
 * The file status information is copied in the stat structure.
 */
#define SLTHA_FileStatus()   int _fstat_r(struct _reent *ReentPtr, int Fd, struct stat *FileStatusPtr)
/**
 * This gets file status on basis of file path passed.
 * The file status information is copied in the stat structure.
 */
#define SLTHA_Status()     int _stat_r(struct _reent *ReentPtr, const char *Path, struct stat *FileStatusPtr)
/**
 * This renames/moves a file or directory
 */
#define SLTHA_Rename()     int _rename_r(struct _reent *ReentPtr, const char *Oldpath, const char *Newpath)
/**
 * This queries whether output stream is a terminal.
 */
#define SLTHA_IsAtty()     int _isatty_r(struct _reent *ReentPtr, int Fd)
#endif

#elif defined __CC_ARM
#define SLTHA_open()       FILEHANDLE _sys_open(const char  *path, int flags)
#define SLTHA_close()      int _sys_close(FILEHANDLE fd)
#define SLTHA_read()       int _sys_read(FILEHANDLE fd, U8 *bufferptr, U32 length, int mode)
#define SLTHA_write()      int _sys_write(FILEHANDLE fd, const U8 *bufferptr, U32 length, int mode)
#define SLTHA_lseek()      int _sys_seek(FILEHANDLE fd, long offset)
#define SLTHA_remove()     int remove(const char *path)
#define SLTHA_rename()     int rename(const char *oldpath, const char *newpath)
#define SLTHA_IsAtty()     int _sys_istty(FILEHANDLE fd)

#elif  defined __ICCARM__

#define SLTHA_open()       int __open(const char * path, int flags)
#define SLTHA_close()      int __close(int fd)
#define SLTHA_read()       size_t __read(int fd, unsigned char *bufferptr, size_t length)
#define SLTHA_write()      size_t __write(int fd, const unsigned char * bufferptr, size_t length)
#define SLTHA_lseek()      long __lseek(int fd, long offset, int dirmode)
#define SLTHA_remove()     int remove(const char * path)
#define SLTHA_rename()     int rename(const char *oldpath, const char *newpath)

#elif  defined __TASKING__

#define SLTHA_open()       _err_t _open(const char *path, _open_flags_t flags)
#define SLTHA_close()      _err_t  _close(_fd_t fd)
#define SLTHA_read()       int _read(_fd_t fd, void *bufferptr, size_t length)
#define SLTHA_write()      int _write(_fd_t fd, const void *bufferptr, size_t length)
#define SLTHA_lseek()      long _lseek(_fd_t fd, long offset, _whence_t dirmode)
#define SLTHA_remove()     int remove(const char *path)
#define SLTHA_filestatus() int fstat(int fd, struct stat *filestatusptr)
#define SLTHA_status()     int stat(const char *path, struct stat *filestatusptr)
#define SLTHA_rename()     int _rename(const char *oldpath, const char *newpath)

#endif

/*******************************************************************************
**                       ENUMERATIONS                                         **
*******************************************************************************/
/**
 * This enumerates the error codes of this APP
 */
typedef enum SLTHA_ERRORCODES
{
  SLTHA_ERROR = -1,             /** Too many files already opened. Slot not available.  */
  SLTHA_SLOT_NOT_AVAILABLE = 1, /** Invalid file access mode. */
  SLTHA_INVALID_MODE,           /** Memory allocation failed. */
  SLTHA_ALLOCATION_FAIL,        /** Error in FAT file system APP. */
  SLTHA_FATFS_ERROR,
} SLTHA_ERRORCODES_t;
/*******************************************************************************
**                      Structures                                            **
*******************************************************************************/
/**
 * Structure containing all the file details.
 */
typedef struct SLTHA_FILEHANDLE
{
  int Fd;                   /** Stores the allocated File descriptor value */
  int CurrentPos;           /** Current position of the file pointer in the file. */
  int Flags;                /** File access mode.*/
  FIL *FatFsPtr;            /** File pointer */
  char *FilePath;           /** File name or path */
} SLTHA_FILEHANDLE_t;

/*******************************************************************************
 ** FUNCTION PROTOTYPES                                                       **
*******************************************************************************/
/**
 * @brief  This function initializes all the local variables of Standard Library Adaptation layer.
 * It should be called first in order to use SLTHA Adaptation layer
 */
void SLTHA_Init(void);

#if defined ( __ICCARM__)
size_t __dwrite(int fd,const unsigned char *bufferptr, size_t length);
#endif



/*********************************************************************************************************************
 * MACROS
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * ENUMS
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * DATA STRUCTURES
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * API PROTOTYPES
 *********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif
#endif
#endif