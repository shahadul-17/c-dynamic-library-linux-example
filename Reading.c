#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "common/Types.h"
#include "common/StringUtilities.h"

int getPageSize()
{
    // return getpagesize();
    return sysconf(_SC_PAGESIZE);
}

int openFileAndCountCharacters(const char *filePath)
{
    FILE *file = fopen(filePath, "rb");

    if (file == NULL)
    {
        printf("An error occurred while opening file.\n");

        return -1;
    }

    int pageSize = getPageSize();
    char *buffer = malloc(pageSize);

    if (buffer == NULL)
    {
        // releasing resource...
        fclose(file);

        printf("An error occurred while allocating memory.\n");

        return -2;
    }

    size_t bytesRead = 0;
    int count = 0;

    while ((bytesRead = fread(buffer, 1, pageSize, file)) > 0)
    {
        count += countCharacters(buffer, bytesRead, TRUE);
    }

    // releasing resources...
    fclose(file);
    free(buffer);

    return count;
}
