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

#include <test/test.h>

#define MAX_COUNT 20
#define PERIOD 1000000

int timer_test()
{
        int count = 0;

        for (count = 0; count < MAX_COUNT; ++count) {

                kprint("%d\r\n", count);
                usleep(PERIOD);

        }
        kprint("If numbers appeared every PERIOD,\r\n"
                "test passed succecfully\r\n");

        timeout_wait(0 == 0, 10 * PERIOD);
        kprint("first timeout_wait test\r\n");

        timeout_wait(1 == 0, 10 * PERIOD);
        kprint("second timeout_wait test\r\n");

        return 0;
}

#undef MAX_COUNT
#undef PERIOD
