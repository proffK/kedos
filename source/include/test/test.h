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

#ifndef _TEST_
#define _TEST_

#include <lib/nostdio.h>
#include <lib/nostdlib.h>
#include <bcm2836/defines.h>
#include <bcm2836/timer.h>
#include <mm/heap.h>
#include <sys/kthread.h>

int mem_test();

int heap_test();

int timer_test();

int lib_test();

int rbuffer_test();

int thread_test();

void data_message_dump(void* data);

#endif
