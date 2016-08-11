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

#include "test/test.h"

void data_dump (void* data) {
	kprint ("%d\r\n", *((int*)data));
}

int rbuffer_test() {

	rbuffer* test_buf = create_rbuffer (0, RING_BUFFER_SIZE); 	
	dump_rbuffer (test_buf, data_dump);			
	int i = 0;						
	int arr[50] = {};
	for (i = 0; i < 50; i++) {
		arr[i] = i;
	}					
	for (i = 0; i < 35; i++) {
		write_data (test_buf, &arr[i], sizeof (int));
	}

	void* data = kcalloc (1, sizeof (int));

	dump_rbuffer (test_buf, data_dump);

	for (i = 0; i < 5; i++) {
		if (i % 2 == 0)
			write_data (test_buf, &arr[i], sizeof (int));
		read_data (test_buf, data);
		kprint ("Data = %d\r\n", *((int*)data));
	}

	dump_rbuffer (test_buf, data_dump);

	for (i = 0; i < 5; i++) {
		if (i % 2 == 0)
			write_data (test_buf, &arr[i], sizeof (int));
		read_data (test_buf, data);
		kprint ("Data = %d\r\n", *((int*)data));
	}

	dump_rbuffer (test_buf, data_dump);

	for (i = 0; i < 45; i++) {
		read_data (test_buf, data);
		kprint ("Data = %d\r\n", *((int*)data));
	}

	dump_rbuffer (test_buf, data_dump);

	free_rbuffer (test_buf);
	kfree (data);
	return 0;
}	
