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

#ifndef _DEVS_
#define _DEVS_

#include <fs/block.h>
#include <bcm2836/defines.h>
#include <bcm2836/sd.h>

#define BLOCK_DEVS_NUM 1

extern block_dev block_dev_table[BLOCK_DEVS_NUM];

enum block_dev_list {
        SD_CARD = 0
};

int bdevs_init();

#endif
