#include "../include/global.h" 

int isUppercase(char s) {                   // Function to check if a character is uppercase.
    if (s >= 65 && s <= 90) {
        return 1;
    }
    return 0;
}

int isLowercase(char s) {                   // Function to check if a character is lowercase.
    if (s >= 97 && s <= 122) {
        return 1;
    }
    return 0;
}

int isDigit(char s) {                       // Function to check if a character is a digit.
    if (s >= 48 && s <= 57) {
        return 1;
    }
    return 0;
}

int constAlphanumericStrgLen(const char *s) {    // Function to get the alphanumeric length of a string (takes a const char pointer).
    const char *ptr = s;

    if (ptr == NULL) {
        return -1;
    }

    int length = 0;
    while (*ptr != '\0') {
        if ((isUppercase(*ptr)) || (isLowercase(*ptr)) || (isDigit(*ptr))) {
            length++;
        }
        ptr++;
    }
    return length;
}

int alphanumericStrgLen(char *s) {    // Function to get the alphanumeric length of a string (takes a char pointer).
    char *ptr = s;

    if (ptr == NULL) {
        return -1;
    }

    int length = 0;
    while (*ptr != '\0') {
        if ((isUppercase(*ptr)) || (isLowercase(*ptr)) || (isDigit(*ptr))) {
            length++;
        }
        ptr++;
    }
    return length;
}

int constStrgLen(const char *s) {           // Function to get the total length of a string (takes a constant char pointer).

    const char *ptr = s;

    if (ptr == NULL) {
        return -1;
    }

    int length = 0;
    while (*ptr != '\0') {
        length++;
        ptr++;
    }
    return length;
}

int findEOM(const char *ciphertext, const char *EOM) {  // Function to get the position of the EOM in a ciphertext input. 
    if (!ciphertext || !EOM) {
        return -1;
    }
    int ciphertextLen = 0;
    int EOMLen = 0;

    while (ciphertext[ciphertextLen] != '\0') {
        ciphertextLen++;
    }
    while (EOM[EOMLen] != '\0') {
        EOMLen++;
    }
    for (int i = 0; i <= ciphertextLen - EOMLen; i++) {
        int j;
        for (j = 0; j < EOMLen; j++) {
            if (ciphertext[i + j] != EOM[j]) {
                break;
            }
        }
        if (j == EOMLen) {
            return i;
        }
    }
    return -1;
}

int encrypt(const char *plaintext, char *ciphertext, int key) {

    const char *plaintextAlphanumLenPtr = plaintext;
    int plaintextAlphanumLen = constAlphanumericStrgLen(plaintextAlphanumLenPtr);    // Get the alphanumeric length of plaintext.

    const char *plaintextLenPtr = plaintext;
    int plaintextLen = constStrgLen(plaintextLenPtr);                           // Get the length of plaintext.

    char *ciphertextLenPtr = ciphertext;
    int ciphertextLen = strgLen(ciphertextLenPtr);                              // Get the length of ciphertext.

    if (plaintextAlphanumLen == -1) {    // Check if the plaintext string is null.
        return -2;
    }
    else if (plaintextAlphanumLen == 0) {   // Check if there are no characters in plaintext to be encoded.
        if (ciphertextLen == -1) {          // Check if the ciphertext string is null.
            return -2;
        }
        else if (ciphertextLen < 7) {       // Check if there are not enough characters in ciphertext to encode "__EOM__".
            return -1;
        }
        if (ciphertextLen < 16) {           // Check if there are not enough characters in ciphertext to encode "undefined__EOM__".
            return -2;
        }
        else {                              // Encode the ciphertext as "undefined__EOM__".
            char *ciphertextPtr = ciphertext;
            char undefinedEOM[] = "undefined__EOM__";
            for (int i = 0; i < 17; i++, ciphertextPtr++) {
                *ciphertextPtr = undefinedEOM[i];
            }
            *ciphertextPtr = '\0';
            return 0;
        }
    }

    if (ciphertextLen == -1) {          // Check if the ciphertext string is null.
            return -2;
        }
    else if (ciphertextLen < 7) {       // Check if there are not enough characters in ciphertext to encode "__EOM__".
        return -1;
    }
    else if (ciphertextLen - 7 < plaintextLen) {    // Check if there are not enough characters in ciphertext to encode the plaintext.
        return -2;
    }

    // Begin encoding the ciphertext using the characters in plaintext.

    const char* plaintextPtr = plaintext;               // Initialize pointers to the plaintext and ciphertext strings.
    char *ciphertextPtr = ciphertext;

    while (*plaintextPtr != '\0') {
        if (isUppercase(*plaintextPtr)) {               // Check if the current plaintext character is uppercase.
            char shifted = *plaintextPtr + key;         // Shift the current plaintext character according to the key.
            if (shifted > 'Z') {
                shifted = 'A' + (shifted - 'Z' - 1);    // Wrap the shifted character if necessary.
            }
            *ciphertextPtr = shifted;                   // Encode the shifted character in ciphertext.
        }
        else if (isLowercase(*plaintextPtr)) {          // Check if the current plaintext character is lowercase.
            char shifted = *plaintextPtr + key;         // Shift the current plaintext character according to the key.
            if (shifted > 'z') {
                shifted = 'a' + (shifted - 'z' - 1);    // Wrap the shifted character if necessary.
            }
            *ciphertextPtr = shifted;                   // Encode the shifted character in ciphertext.
        }
        else if (isDigit(*plaintextPtr)) {              // Check if the current plaintext character is a digit.
            char shifted = *plaintextPtr + key;         // Shift the current plaintext character according to the key.
            if (shifted > '9') {
                shifted = '0' + (shifted - '9' - 1);    // Wrap the shifted character if necessary.
            }
            *ciphertextPtr = shifted;                   // Encode the shifted character in ciphertext.
        }
        else {
            *ciphertextPtr = *plaintextPtr;             // Encode non-alphumeric characters as is in ciphertext.
        }
        ciphertextPtr++;
        plaintextPtr++;
    }
    char EOM[] = "__EOM__";                             // Encode the EOM after the plaintext encoding.
    for (int i = 0; i < 8; i++) {
        *ciphertextPtr = EOM[i];
        ciphertextPtr++;
    }
    *ciphertextPtr = '\0';                              // Null terminate the encoded string.

    return plaintextAlphanumLen;                        // Return the number of plaintext characters successfully encoded.
}

int decrypt(const char *ciphertext, char *plaintext, int key) {
    
    const char *ciphertextLenPtr = ciphertext;                  // Get the length of the ciphertext string.
    int ciphertextLen = constStrgLen(ciphertextLenPtr);

    char *plaintextLenPtr = plaintext;                          // Get the length of the plaintext string.
    int plaintextLen = strgLen(plaintextLenPtr);

    const char *ciphertextEOMPtr = ciphertext;                  // Find the position of the first __EOM__ instance.
    const char EOM[] = "__EOM__";
    int EOMPos = findEOM(ciphertextEOMPtr, EOM);

    const char *ciphertextWithoutEOMPtr = ciphertext;           // Get ciphertext without the __EOM__.            
    char ciphertextWithoutEOM[EOMPos];
    int index;
    for (index = 0; index < EOMPos; index++) {
        ciphertextWithoutEOM[index] = *ciphertextWithoutEOMPtr;
    }
    ciphertextWithoutEOM[index] = '\0';
    int ciphertextAlphanumLenWithoutEOM = alphanumericStrgLen(ciphertextWithoutEOM); // Get the length of ciphertext without the __EOM__.

    if (plaintextLen == 0) {                    // Plaintext is empty, there is nothing to decrypt into.
        return 0;
    }
    if (plaintextLen == -1) {                   // Plaintext is null, there is nothing to decrypt into.
        return -2;
    }
    else if (ciphertextLen == -1) {             // Ciphertext is null, there is nothing to decypt from.
        return -2;
    }
    else if (ciphertextLen < 7) {               // Ciphertext does not contain enough characters to hold an __EOM__ marker.
        return -1;
    }
    else if (EOMPos == -1) {                    // An __EOM__ instance cannot be located in ciphertext.
        return -1;
    }
    else if (ciphertextAlphanumLenWithoutEOM == 0) {    // No characters in ciphertext are encoded (either empty/entirely non-alphanumeric).
        char undefined[] = "undefined";
        char *plaintextPtr = plaintext;
        for (int i = 0; i < 10; i++, plaintextPtr++) {
            *plaintextPtr = undefined[i];               // Return plaintext as "undefined".
        }
        *plaintextPtr = '\0';
        return 0;                                       // 0 characters were successfully decrypted.
    }

    const char *ciphertextPtr = ciphertext;             // Initialize pointers to the plaintext and ciphertext inputs.
    char *plaintextPtr = plaintext;
    
    int ciphertextAlphanumLen = 0;                      // Track the number of alphanumeric characters encrypted (initially 0).
    
    int upperbound;                                     // Create an upper bound for the decryption range.
    if (plaintextLen < EOMPos) {                        // If the length of plaintext is smaller than the position of the EOM, 
        upperbound = plaintextLen;                      // the length of plaintext will serve as the upper bound.
    }
    else {
        upperbound = EOMPos;                            // Otherwise the position of the EOM will serve as the upper bound.
    }
    for (int i = 0; i < upperbound; i++) {
        if (isUppercase(*ciphertextPtr)) {              // Check if the current ciphertext character is uppercase.
            char shifted = *ciphertextPtr - key;        // Shift the current ciphertext character according to the key.
            if (shifted < 'A') {
                shifted = 'Z' - ('A' - shifted - 1);    // Wrap the shifted character if necessary.
            }
            *plaintextPtr = shifted;                    // Decrypt the shifted character in plaintext.
            ciphertextAlphanumLen++;
        }
        else if (isLowercase(*ciphertextPtr)) {         // Check if the current ciphertext character is lowercase.
            char shifted = *ciphertextPtr - key;        // Shift the current ciphertext character according to the key.
            if (shifted < 'a') {
                shifted = 'z' - ('a' - shifted - 1);    // Wrap the shifted character if necessary.
            }
            *plaintextPtr = shifted;                    // Decrypt the shifted character in plaintext.
            ciphertextAlphanumLen++;
        }
        else if (isDigit(*ciphertextPtr)) {             // Check if the current ciphertext character is a digit.
            char shifted = *ciphertextPtr - key;        // Shift the current ciphertext character according to the key.
            if (shifted < '0') {
                shifted = '9' - ('0' - shifted - 1);    // Wrap the shifted character if necessary.
            }
            *plaintextPtr = shifted;                    // Decrypt the shifted character in plaintext.
            ciphertextAlphanumLen++;
        }
        else {
            *plaintextPtr = *ciphertextPtr;             // Decrypt non-alphumeric characters as is in plaintext.
        }
        ciphertextPtr++;
        plaintextPtr++;
    }
    *plaintextPtr = '\0';                               // Null terminate the decrypted plaintext.
    if (plaintextLen < EOMPos) {                        // If there were not enough characters to decrypt all of ciphertext, return -2.
        return -2;
    }
    return ciphertextAlphanumLen;                       // Otherwise, return the number of successfully decrypted characters.
}