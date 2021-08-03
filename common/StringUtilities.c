#include <string.h>

#include "StringUtilities.h"

BOOLEAN startsWith(const char *substring, const char *string)
{
    size_t substringLength = strlen(substring);
    size_t stringLength = strlen(string);

    if (stringLength < substringLength) { return FALSE; }

    return memcmp(substring, string, substringLength) == 0 ? TRUE : FALSE;
}

int countCharacters(const char *string, size_t stringLength, BOOLEAN ignoreNewLines)
{
    if (stringLength == -1)
    {
        stringLength = strlen(string);
    }

    int count = 0;

    for (int i = 0; i < stringLength; i++)
    {
        if (ignoreNewLines && string[i] == '\n') { continue; }

        count++;
    }

    return count;
}
