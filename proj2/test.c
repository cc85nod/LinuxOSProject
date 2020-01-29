#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#define SIZE 100
#define get_process_zero_session_group(results, size)	syscall(547, results, size)
#define get_process_session_group(results, size) syscall(548, results, size)
int main() {

	unsigned int results1[ SIZE ], results2[ SIZE ];
	int j, k, l, n;

	k = get_process_zero_session_group(results1, SIZE);
	n = get_process_session_group(results2, SIZE);

	printf("--------get_process_zero_session_group--------\n");

	if(k) {
		printf("What follows are the PIDs of the processes that are in the same login sesson of process 0\n");
		for(j = 0; j < k && j < SIZE; j++) {
			printf("[%d] %u\n", j, results1[j]);
		}
	} else {
		printf("There is an error when executing this system call.\n");
	}

	printf("--------get_process_session_group--------\n");

	if(n) {
		printf("What follows are the PIDs of the processes that are in the same login sesson of process 0\n");
		for(l = 0; l < n && l < SIZE; l++) {
			printf("[%d] %u\n", l, results2[l]);
		}
	} else {
		printf("There is an error when executing this system call.\n");
	}
	
	return 0;
}