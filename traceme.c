#include <stdio.h>
#include <string.h>
#include <process.h>
#include <sys/types.h>
#include <windows.h>

int main(int argc, char **argv) { 
	int i;
	for (i=0;i<10;i++) {
		printf("traceme - %d\n", _getpid());	
		
		if (argc > 1) {
			Sleep(10*1000);
		}

	}
	printf("traceme - done\n");
	return 0;
}
