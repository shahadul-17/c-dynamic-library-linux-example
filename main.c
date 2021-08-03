#include <stdio.h>
#include <dlfcn.h>

#include "common/StringUtilities.h"

// function pointer...
int (*count)(const char *filePath);

int main(int argc, char *argv[], char *envp[])
{
    if (argc < 3)
    {
        printf("Must provide necessary command line arguments.\n");

        return -1;
    }

    char *countingMode = argv[1];
    char *sharedLibraryName = NULL;

    if (startsWith(countingMode, "reading"))
    {
        sharedLibraryName = "./bin/Reading.so";
    }
    else if (startsWith(countingMode, "mapping"))
    {
        sharedLibraryName = "./bin/Mapping.so";
    }
    else
    {
        printf("Invalid command line argument '%s' provided.", countingMode);

        return -1;
    }

    printf("Executing library '%s'.\n", sharedLibraryName);

    void *sharedLibraryHandle = dlopen(sharedLibraryName, RTLD_LAZY);

    if (sharedLibraryHandle == NULL)
    {
        printf("An error occurred while opening shared library '%s'.\n", sharedLibraryName);

        return -1;
    }

    count = dlsym(sharedLibraryHandle, "openFileAndCountCharacters");

    if (count == NULL)
    {
        printf("An error occurred finding symbol in shared library '%s'.\n", sharedLibraryName);

        return -1;
    }

    char *filePath = argv[2];
    int characterCount = count(filePath);

    if (characterCount < 0)
    {
        printf("An error occurred while counting characters.\n");
    }
    else
    {
        printf("Character count excluding new-line(s) = %d\n", characterCount);
    }
    
    dlclose(sharedLibraryHandle);

    return 0;
}
