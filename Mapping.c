#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "common/Types.h"
#include "common/StringUtilities.h"

void closeFileDescriptor(int fileDescriptor)
{
    int result = close(fileDescriptor);

    if (result != 0)
    {
        printf("An error occurred while closing file descriptor.\n");
    }
}

void releaseMappedMemory(void *mappedMemory, size_t length)
{
    int result = munmap(mappedMemory, length);

    if (result != 0)
    {
        printf("An error occurred while releasing mapped memory.\n");
    }
}

int openFileAndCountCharacters(const char *filePath)
{
    int fileDescriptor = open(filePath, O_RDONLY);

    if (fileDescriptor < 0)
    {
        printf("An error occurred while opening file '%s'.\n", filePath);

        return -1;
    }

    struct stat *fileInformation = malloc(sizeof(struct stat));

    if (fileInformation == NULL)
    {
        // releasing resource...
        closeFileDescriptor(fileDescriptor);

        printf("An error occurred while allocating memory.\n");

        return -2;
    }

    int result = fstat(fileDescriptor, fileInformation);

    if (result < 0)
    {
        // releasing resources...
        free(fileInformation);
        closeFileDescriptor(fileDescriptor);
        
        printf("An error occurred while retrieving file '%s' information.\n", filePath);

        return -3;
    }

    // maps file to memory...
    char *mappedMemory = mmap(NULL, fileInformation->st_size, PROT_READ,
        MAP_FILE | MAP_PRIVATE, fileDescriptor, 0);
    
    if (mappedMemory == MAP_FAILED)
    {
        // releasing resources...
        free(fileInformation);
        closeFileDescriptor(fileDescriptor);

        printf("An error occurred while mapping file '%s' to memory.\n", filePath);

        return -4;
    }

    int count = countCharacters(mappedMemory, fileInformation->st_size, TRUE);

    // releasing resources...
    releaseMappedMemory(mappedMemory, fileInformation->st_size);
    free(fileInformation);
    closeFileDescriptor(fileDescriptor);

    return count;
}
