/*
 * TWAIN Plug-in
 * Copyright (C) 1999 Craig Setera
 * Craig Setera <setera@home.com>
 * 03/31/1999
 *
 * Updated for Mac OS X support
 * Brion Vibber <brion@pobox.com>
 * 07/22/2004
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef _TW_PLATFORM_H
#define _TW_PLATFORM_H

#ifdef __APPLE__

/* Mac OS X */

#include <Carbon/Carbon.h>
#include <TWAIN/TWAIN.h>

#define DEBUG_LOGFILE "/tmp/twain.log"
#define DUMP_FILE "/tmp/twaincap.bin"
#define DUMP_NAME "dtwain"
#define READDUMP_NAME "rtwain"

#define _stricmp strcasecmp

#else

/* Win32 */

#include <windows.h>
#include "twain.h"

/* The DLL to be loaded for TWAIN support */
#define TWAIN_DLL_NAME "TWAIN_32.DLL"
#define DEBUG_LOGFILE "c:\\twain.log"
#define DUMP_FILE "C:\\TWAINCAP.BIN"
#define DUMP_NAME "DTWAIN.EXE"
#define READDUMP_NAME "RTWAIN.EXE"

/* Windows uses separate entry point */
#define TWAIN_ALTERNATE_MAIN

#endif

#endif
