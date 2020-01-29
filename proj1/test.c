#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#define MEMORY_SIZE 100000
#define linux_survey_TT(ptr)	syscall(548, ptr)

int main() {

	char result_1[ MEMORY_SIZE ];
	char result_2[ MEMORY_SIZE ];
	char result_3[ MEMORY_SIZE ];
	FILE *file;

	if(fork()) {
		linux_survey_TT(result_1);

		wait(NULL);
		file = fopen("result1.txt", "w");
		if(!file) {
			printf("error\n");
			exit(1);
		} else {
			fwrite(result_1, 1, strlen(result_1), file);
		}
		fclose(file);
	} else {
		linux_survey_TT(result_2);
		result_1[0] = 123;
		linux_survey_TT(result_3);

		file = fopen("result2.txt", "w");
		if(!file) {                                             	
		printf("error\n");
			exit(1);
		} else {
			fwrite(result_2, 1, strlen(result_2), file);
		}
		fclose(file);

		file = fopen("result3.txt", "w");
		if(!file) {
			printf("error\n");
			exit(1);
		} else {
			fwrite(result_3, 1, strlen(result_3), file);
		}
		fclose(file);
	}

	return 0;
}	
