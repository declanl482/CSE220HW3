#include "../include/global.h"

int strgLen(char *s) {

    char *ptr = s;              // Initialize a pointer to the input string.

    if (ptr == NULL) {          // Check if the pointer is null.
        return -1;
    }

    int length = 0;
    while (*ptr != '\0') {      // Traverse the string and capture the length of all characters.
        length++;
        ptr++;
    }
    return length;              // Return the length of the string.
}

void strgCopy(char *s, char *d) {

    char *srcPtr = s, *destPtr = d;             // Initialize pointers to the source and destination strings.
    int i = 0;

    if (srcPtr == NULL || destPtr == NULL) {    // Check if either of the pointers are null.
        return;
    }

    while (*srcPtr != '\0' && i < 49) {         // Copy the string up until the limit of the buffer.
        *destPtr = *srcPtr;                     // This is provided in the test cases as 50.
        destPtr++;                              // We iterate until index 48 because 49 is reserved for the null terminator.
        srcPtr++;
        i++;
    }

    *destPtr = '\0';                            // Null terminate the copied string.
}

void strgChangeCase(char *s) {

    char* ptr = s;                              // Initialize a pointer to the input string.

    if (ptr == NULL) {                          // Check if the pointer is null.
        return;
    }

    while (*ptr != '\0') {
        if (*ptr >= 97 && *ptr <= 122) {        // Check if the character is lowercase.
            *ptr = *ptr - 32;                   // Make the lowercase character uppercase.
            ptr++;
        }
        else if (*ptr >= 65 && *ptr <= 90) {    // Check if the character is uppercase.
            *ptr = *ptr + 32;                   // Make the uppercase character lowercase.
            ptr++;
        }
        else {
            ptr++;                              // If the character is non-alphabetic, continue iterating.
        }
    }
}

int strgDiff(char *s1, char *s2) {
    char *ptr1 = s1, *ptr2 = s2;                // Initialize pointers to the input strings.
    int i = 0;
    
    if (ptr1 == NULL || ptr2 == NULL) {         // Check if either of the pointers are null. 
        return -2;
    }

    while (*ptr1 != '\0' && *ptr2 != '\0') {
        if (*ptr1 != *ptr2) {                   // If the strings differ at any point, break out of the loop.
            break;
        }
        i++;
        ptr1++;
        ptr2++;
    }
    if (*ptr1 == '\0' && *ptr2 == '\0') {       // Check if the input strings are equal.
        return -1;                              // If so, return -1.
    }
    else {
        return i;                               // Otherwise, return the index of the first difference.
    }
}

void strgInterleave(char *s1, char *s2, char *d) {
    
    char *ptr1 = s1, *ptr2 = s2, *destPtr = d;              // Initialize pointers to the input strings.
    int i = 0;

    if (ptr1 == NULL || ptr2 == NULL || destPtr == NULL) {  // Check if any of the pointers are null.
        return;
    }

    while ((*ptr1 != '\0' || *ptr2 != '\0') && i < 49) {    // Interleave the strings up until the limit of the buffer.
        if (*ptr1 != '\0') {
            *destPtr = *ptr1;                               // Interleave using s1.
            ptr1++;
            destPtr++;                                      // Advance the destination pointer on each iteration.
            i++;
        }
        if (*ptr2 != '\0') {                                // Interleave using s2.
            *destPtr = *ptr2;
            ptr2++;
            destPtr++;                                      // Advance the destination pointer on each iteration.
            i++;
        }
    }
    *destPtr = '\0';                                        // Null terminate the interleaved string.
}