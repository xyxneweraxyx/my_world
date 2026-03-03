/*
** EPITECH PROJECT, 2025
** str
** File description:
** A simple library with string functions.
*/

#ifndef STRING_LIB
    #define STRING_LIB

// Functions
int str_len(const char *restrict len);
void str_cpy(const char *restrict src, char *restrict dest);
int str_cmp(const char *restrict str1, const char *restrict str2);
int str_ncmp(const char *restrict str1,
    const char *restrict str2, const int n);
void str_cat(char *restrict dest, int n, ...);
void str_ncpy(const char *restrict src, char *restrict dest, const int n);

#endif
