#include <stdio.h>
#include "pin.H"
#include "aext-common.h"

#define EXTRACTOR_NAME "aext-dump-ins"
#define EXTRACTOR_LOG EXTRACTOR_NAME##".out"

#define SKIP_BRACES 1

FILE * output_fd;
PIN_LOCK lock;

struct entry_point_tracker tracker;

void log_instruction(void *ip, USIZE size) {

    PIN_GetLock(&lock, 0);
	unsigned char instruction[64] = { 0 };
	PIN_SafeCopy(&instruction, ip, size);

    if (size == 0) {
        return;
    }

    fprintf(output_fd, "%p:", ip);
	
	int i=0;
	for (i=0;i<size;i++) {
		fprintf(output_fd, "%02x", instruction[i]);
	}

    fprintf(output_fd, ":EOL\n");
    fflush(output_fd);
    PIN_ReleaseLock(&lock);
}

void each_instruction(INS ins, VOID *v)
{
    IF_IN_MODULE(INS_Address(ins), tracker) 
    {
        INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)log_instruction, 
            IARG_INST_PTR, IARG_UINT32, INS_Size(ins), IARG_END);
    }
}

void finish(INT32 code, VOID *v)
{
    fprintf(output_fd, "#eof\n");
    fclose(output_fd);
}

void check_loaded_image(IMG img, void *v)
{
    if (IMG_IsMainExecutable(img)) {
        tracker.entry_point = IMG_Entry(img);
        tracker.exit_point = tracker.entry_point + IMG_SizeMapped(img);
        fprintf(stderr, "entry point @ %p\n", (void *)tracker.entry_point);
        fprintf(stderr, "size: %llu\n", IMG_SizeMapped(img));
    }
}

void pin_init() {
    PIN_InitLock(&lock);

    output_fd = fopen(EXTRACTOR_LOG, "w");

    INS_AddInstrumentFunction(each_instruction, 0);
    IMG_AddInstrumentFunction(check_loaded_image, 0);
    PIN_AddFiniFunction(finish, 0);
}

int main(int argc, char *argv[])
{
    if (PIN_Init(argc, argv)) {
        fprintf(stderr, "Unable to init pintool, check usage\n");
        exit(1);
    }

    pin_init();
    PIN_StartProgram();    
    return 0;
}
