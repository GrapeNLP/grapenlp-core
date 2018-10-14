/*
 * Unitex
 *
 * Copyright (C) 2001-2007 Université de Marne-la-Vallée <unitex@univ-mlv.fr>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
 *
 */

#include <grape/unicode.h>

/* This array is a bit array used to define characters that are letters */
char tab_is_letter[8192];


/**
 * We define here the unicode NULL character and the unicode
 * empty string.
 */
unichar U_ENDL = '\n';
unichar U_NULL = '\0';
unichar *U_EMPTY = &U_NULL;

/**
 * Here are defined the default encodings.
 */
Encoding STDIN_ENC = UTF8;
Encoding STDOUT_ENC = UTF8;
Encoding STDERR_ENC = UTF8;
Encoding FILE_ENC = UTF16_LE;


/* ------------------- Some aliases, mainly for default UTF16-LE use ------------------- */

FILE *u_fopen(const char *name, const char *MODE) {
    return u_fopen(FILE_ENC, name, MODE);
}

int u_fempty(const char *name) {
    return u_fempty(FILE_ENC, name);
}

int u_fgetc_raw(FILE *f) {
    return u_fgetc_raw(FILE_ENC, f);
}

int u_fgetc_UTF16LE(FILE *f) {
    return u_fgetc(UTF16_LE, f);
}

int u_fgetc_UTF16BE(FILE *f) {
    return u_fgetc(UTF16_BE, f);
}

int u_fgetc_UTF8(FILE *f) {
    return u_fgetc(UTF8, f);
}

int u_fgetc(FILE *f) {
    return u_fgetc(FILE_ENC, f);
}

int u_fgetc_CR(FILE *f) {
    return u_fgetc_CR(FILE_ENC, f);
}

int u_fread_raw(unichar *t, int N, FILE *f) {
    return u_fread_raw(FILE_ENC, t, N, f);
}

int u_fread(unichar *t, int N, FILE *f) {
    return u_fread(FILE_ENC, t, N, f);
}

int u_fputc_raw(unichar c, FILE *f) {
    return u_fputc_raw(FILE_ENC, c, f);
}

int u_fputc_UTF16LE(unichar c, FILE *f) {
    return u_fputc(UTF16_LE, c, f);
}

int u_fputc_UTF16BE(unichar c, FILE *f) {
    return u_fputc(UTF16_BE, c, f);
}

int u_fputc_UTF8(unichar c, FILE *f) {
    return u_fputc(UTF8, c, f);
}

int u_fputc(unichar c, FILE *f) {
    return u_fputc(FILE_ENC, c, f);
}

int u_ungetc(unichar c, FILE *f) {
    return u_ungetc(FILE_ENC, c, f);
}

int u_fwrite_raw(const unichar *t, int N, FILE *f) {
    return u_fwrite_raw(FILE_ENC, t, N, f);
}

int u_fwrite(const unichar *t, int N, FILE *f) {
    return u_fwrite(FILE_ENC, t, N, f);
}

int u_fgets(unichar *s, FILE *f) {
    return u_fgets(FILE_ENC, s, f);
}

int u_fgets(unichar *s, int size, FILE *f) {
    return u_fgets(FILE_ENC, s, size, f);
}

int u_fgets2(unichar *s, FILE *f) {
    return u_fgets2(FILE_ENC, s, f);
}

/**
 * By default, messages printed to the standard output are UTF8-encoded.
 */
int u_printf(const char *format, ...) {
    va_list list;
    va_start(list, format);
    int n = u_vfprintf(STDOUT_ENC, stdout, format, list);
    va_end(list);
    return n;
}

template<typename UCharIterator>
int u_printf(UCharIterator begin, UCharIterator end) {
    int count(0);
    for (; begin != end; ++begin, ++count)
        u_putc(*begin);
    return count;
}

int u_fprintf(FILE *f, const char *format, ...) {
    va_list list;
    va_start(list, format);
    int n = u_vfprintf(FILE_ENC, f, format, list);
    va_end(list);
    return n;
}

void u_fprints(Encoding, unichar *, FILE *);

void u_fprints(unichar *s, FILE *f) {
    u_fprints(FILE_ENC, s, f);
}

void u_fprints(Encoding, const char *, FILE *);

void u_fprints(const char *s, FILE *f) {
    u_fprints(FILE_ENC, s, f);
}

int u_scanf(const char *format, ...) {
    va_list list;
    va_start(list, format);
    int n = u_vfscanf(STDIN_ENC, stdin, format, list);
    va_end(list);
    return n;
}

int u_fscanf(FILE *f, const char *format, ...) {
    va_list list;
    va_start(list, format);
    int n = u_vfscanf(FILE_ENC, f, format, list);
    va_end(list);
    return n;
}

/* ------------------- File functions ------------------- */

/**
 * Opens a file in binary mode for unicode I/O and returns the
 * file in case of success; NULL otherwise. If you try to open a file
 * in READ mode, NULL will be returned if the file does not exist or
 * if it does not start with the byte order mark, in the case of a UTF16
 * file. In this last case, an error message will be printed to indicate
 * that the file is not a UTF16 one.
 *
 * 'MODE' should be U_READ, U_WRITE, U_APPEND or U_MODIFY
 */
FILE *u_fopen(Encoding encoding, const char *name, const char *MODE) {
    FILE *f;
    if (!strcmp(MODE, U_APPEND) || !strcmp(MODE, U_MODIFY)) {
        /* If we are in APPEND or MODIFY mode, we check first if the file already exists */
        f = fopen(name, U_READ);
        if (f != NULL) {
            /* If the file exists, we close it and reopen it in APPEND mode */
            fclose(f);
            f = fopen(name, MODE);
            if (!strcmp(MODE, U_MODIFY)) {
                /* If we are in MODIFY mode, we must set the cursor at the beginning of the
          * file, i.e. after the byte order mark, if any. */
                if (encoding == UTF16_LE || encoding == UTF16_BE) {
                    fseek(f, 2, 0);
                }
            }
            return f;
        }
        /* If the file does not exists, we are in WRITE mode */
        f = fopen(name, U_WRITE);
        if (f == NULL) return NULL;
        /* As the file is new, we must insert the byte order char if we are in
    * UTF16. */
        if (encoding == UTF16_LE) {
            u_fputc(U_BYTE_ORDER_MARK, f);
        } else if (encoding == UTF16_BE) {
            u_fputc_UTF16BE(U_BYTE_ORDER_MARK, f);
        }
        return f;
    }
    f = fopen(name, MODE);
    int c;
    if (f == NULL) return NULL;
/* If the file is opened in READ mode and if we are in UTF16,
 * we check the presence of the byte order mark. */
    if (!strcmp(MODE, U_READ)) {
        if (encoding == UTF16_LE) {
            c = u_fgetc_UTF16LE(f);
            if (c != U_BYTE_ORDER_MARK) {
                error("u_fopen error: %s is not a UTF16-LE text file\n", name);
                fclose(f);
                return NULL;
            }
            return f;
        }
        if (encoding == UTF16_BE) {
            c = u_fgetc_UTF16BE(f);
            if (c != U_BYTE_ORDER_MARK) {
                error("u_fopen error: %s is not a UTF16-BE text file\n", name);
                fclose(f);
                return NULL;
            }
            return f;
        }
        return f;
    }
/* If the file is opened in WRITE mode, we may insert the 0xFEFF unicode char */
    if (!strcmp(MODE, U_WRITE)) {
        if (encoding == UTF16_LE) u_fputc(U_BYTE_ORDER_MARK, f);
        else if (encoding == UTF16_BE) u_fputc_UTF16BE(U_BYTE_ORDER_MARK, f);
    }
    return f;
}


/**
 * Closes a UTF16 file.
 */
int u_fclose(FILE *f) {
    return fclose(f);
}


/**
 * This function creates an empty Unicode file that just contains the
 * byte order mark. It returns 0 if it fails; 1 otherwise.
 */
int u_fempty(Encoding encoding, const char *name) {
    FILE *f = u_fopen(encoding, name, U_WRITE);
    if (f == NULL) {
        return 0;
    }
    u_fclose(f);
    return 1;
}


/**
 * This function tests if the given file name correspond to a UTF16 file.
 */
bool u_is_UTF16(const char *name) {
    FILE *f = fopen(name, U_READ);
    if (f == NULL) {
        /* If the file does not exist */
        return FILE_DOES_NOT_EXIST;
    }
    int c = u_fgetc_UTF16LE(f);
    fclose(f);
    if (c == U_BYTE_ORDER_MARK) {
        return UTF16_LITTLE_ENDIAN_FILE;
    }
    if (c == U_NOT_A_CHAR) {
        return UTF16_BIG_ENDIAN_FILE;
    }
    return NOT_A_UTF16_FILE;
}


/**
 * UTF16-LE version of fgetc. It does not read a char after reading 0x0D.
 * It returns EOF if it cannot read a UTF16-LE character. Moreover, it
 * prints an error message if it can read just one byte.
 */
int u_fgetc_UTF16LE_raw(FILE *f) {
    int c;
    unsigned char a, b;
    if (!fread(&b, 1, 1, f)) return EOF;
    if (!fread(&a, 1, 1, f)) {
        error("Alignment error: odd number of characters in a UTF16 file\n");
        return EOF;
    }
    c = a * 256 + b;
    return c;
}


/**
 * UTF16-BE version of fgetc. It does not read a char after reading 0x0D.
 * It returns EOF if it cannot read a UTF16-BE character. Moreover, it
 * prints an error message if it can read just one byte.
 */
int u_fgetc_UTF16BE_raw(FILE *f) {
    int c;
    unsigned char a, b;
    if (!fread(&b, 1, 1, f)) return EOF;
    if (!fread(&a, 1, 1, f)) {
        error("Alignment error: odd number of characters in a UTF16 file\n");
        return EOF;
    }
    c = b * 256 + a;
    return c;
}


/**
 * Reads an UTF8 encoded character from the given file and returns its
 * unicode number. Returns EOF if the end of file has been reached.
 * Prints an error and returns '?' if the end of file is found while reading a
 * compound character, or if there is an encoding error.
 *
 * IMPORTANT: This function allows reading characters > 65536, so if
 *            it is used only for 16 bits unicode, the caller
 *            must check that the value is not greater than expected.
 */
int u_fgetc_UTF8_raw(FILE *f) {
    unsigned char c;
    if (!fread(&c, 1, 1, f)) return EOF;
    if (c <= 0x7F) {
        /* Case of a 1 byte character 0XXX XXXX */
        return c;
    }
/* Case of a character encoded on several bytes */
    int number_of_bytes;
    unsigned int value;
    if ((c & 0xE0) == 0xC0) {
        /* 2 bytes 110X XXXX*/
        value = c & 31;
        number_of_bytes = 2;
    } else if ((c & 0xF0) == 0xE0) {
        /* 3 bytes 1110X XXXX */
        value = c & 15;
        number_of_bytes = 3;
    } else if ((c & 0xF8) == 0xF0) {
        /* 4 bytes 1111 0XXX */
        value = c & 7;
        number_of_bytes = 4;
    } else if ((c & 0xFC) == 0xF8) {
        /* 5 bytes 1111 10XX */
        value = c & 3;
        number_of_bytes = 5;
    } else if ((c & 0xFE) == 0xFC) {
        /* 6 bytes 1111 110X */
        value = c & 1;
        number_of_bytes = 6;
    } else {
        error("Encoding error in first byte of a unicode sequence\n");
        return '?';
    }
/* If there are several bytes, we read them and compute the unicode
 * number of the character */
    for (int i = 0; i < number_of_bytes - 1; i++) {
        if (!fread(&c, 1, 1, f)) return EOF;
        /* Following bytes should be of the form 10XX XXXX */
        if ((c & 0xC0) != 0x80) {
            error("Encoding error in byte %d of a %d byte unicode sequence\n", i + 2, number_of_bytes);
            return '?';
        }
        value = (value << 6) | (c & 0x3F);
    }
    return value;
}


/**
 * Unicode version of fgetc. It does not read a char after reading 0x0D.
 * In UTF16:
 * - It returns EOF if it cannot read a well-formed character. Moreover, it
 *   prints an error message if it can read just one byte.
 *
 * In UTF8:
 * - It returns EOF at the end of file or '?' if it cannot read a well-formed
 *   character. In that case, it prints an error message.
 */
int u_fgetc_raw(Encoding encoding, FILE *f) {
    switch (encoding) {
        case UTF16_LE:
            return u_fgetc_UTF16LE_raw(f);
        case UTF16_BE:
            return u_fgetc_UTF16BE_raw(f);
        case UTF8:
            return u_fgetc_UTF8_raw(f);
    }
    return EOF;
}


/**
 * Unicode version of fgetc. This function reads Windows-style end-of-lines,
 * i.e. if it reads a '\r', it skips the '\n' that is supposed to come after.
 *
 * See u_fgetc_raw for returned values.
 */
int u_fgetc(Encoding encoding, FILE *f) {
    int c = u_fgetc_raw(encoding, f);
    if (c == 0x0D) {
        /* If we read a '\r', we try to skip the '\n' */
        if (EOF == u_fgetc_raw(encoding, f)) return EOF;
        return '\n';
    }
    return c;
}


/**
 * A version of u_fgetc that returns \n whatever it reads \n, \r or \r\n.
 */
int u_fgetc_CR(Encoding encoding, FILE *f) {
    int c = u_fgetc_raw(encoding, f);
    if (c == EOF) {
        return EOF;
    }
    if (c == 0x0A) {
        return '\n';
    }
    if (c == 0x0D) {
        if (encoding == UTF8) {
            /* In UTF8, we know that if we look for a \n, it will take 1 byte. This
       * is a trick in order to avoid reading a character made of several bytes
       * that we should put back to the file. */
            c = fgetc(f);
        } else {
            c = u_fgetc_raw(encoding, f);
        }
        if (c == EOF) {
            return '\n';
        }
        if (c != 0x0A) {
            /* If there is no 0x0A after 0x0D, we put back the character */
            switch (encoding) {
                case UTF16_LE:
                case UTF16_BE: {
                    u_ungetc_raw(encoding, c, f);
                    break;
                }
                case UTF8: {
                    ungetc((char) c, f);
                    break;
                }
            }
        }
        return '\n';
    }
    return c;
}


/**
 * Reads N characters and stores them in 't', that is supposed to be large enough.
 * Returns the number of characters read.
 * This function reads raw chars, since it does not convert \r\n into \n.
 *
 * WARNING: this function will be deprecated
 */
int u_fread_raw(Encoding encoding, unichar *t, int N, FILE *f) {
    int i, c;
    for (i = 0; i < N; i++) {
        c = u_fgetc_raw(encoding, f);
        if (c == EOF) return i;
        t[i] = (unichar) c;
    }
    return i;
}


/**
 * Reads N characters and stores them in 't', that is supposed to be large enough.
 * Returns the number of characters read. This function converts \r\n into \n.
 */
int u_fread(Encoding encoding, unichar *t, int N, FILE *f) {
    int i, c;
    for (i = 0; i < N; i++) {
        c = u_fgetc_CR(encoding, f);
        if (c == EOF) return i;
        t[i] = (unichar) c;
    }
    return i;
}


/**
 * UTF16-LE version of fputc. It does not put a 0xOA after a 0x0D.
 * Returns 1 in case of success; 0 otherwise.
 */
int u_fputc_UTF16LE_raw(unichar c, FILE *f) {
    unsigned char a, b;
    int ret;
    a = (unsigned char) (c / 256);
    b = (unsigned char) (c % 256);
    ret = fwrite(&b, 1, 1, f);
    ret = ret && fwrite(&a, 1, 1, f);
    return ret;
}


/**
 * UTF16-BE version of fputc. It does not put a 0xOA after a 0x0D.
 * Returns 1 in case of success; 0 otherwise.
 */
int u_fputc_UTF16BE_raw(unichar c, FILE *f) {
    unsigned char a, b;
    int ret;
    a = (unsigned char) (c / 256);
    b = (unsigned char) (c % 256);
    ret = fwrite(&a, 1, 1, f);
    ret = ret && fwrite(&b, 1, 1, f);
    return ret;
}


/**
 * A version of putc that does not prints \r\n when you want it to print a \n.
 * Returns 1 in case of success; 0 otherwise.
 */
int fputc_raw(unsigned char c, FILE *f) {
    return fwrite(&c, 1, 1, f);
}


/**
 * This function writes a 2-bytes unicode character in the given file
 * encoding it in UTF8. It does not put a 0xOA after a 0x0D.
 * Returns 0 if an error occurs; 1 otherwise.
 *
 * NOTE: as it takes a unichar, this function cannot be used for writing
 *       a unicode character > 0xFFFF
 */
int u_fputc_UTF8_raw(unichar c, FILE *f) {
    if (c <= 0x7F) {
        return (fputc_raw(c, f) == EOF) ? 0 : 1;
    }
    unsigned char a;
    unsigned char b;
    if (c <= 0x7FF) {
        a = (unsigned char) (0xC0 | (c >> 6));
        b = (unsigned char) (0x80 | (c & 0x3F));
        if (fputc_raw(a, f) == EOF) return 0;
        return (fputc_raw(b, f) == EOF) ? 0 : 1;
    }
    unsigned char C;
    a = (unsigned char) (0xE0 | (c >> 12));
//b=(unsigned char) (0x80 | ((c-(c&12))>>6));   //$CD:20021119 old
    b = (unsigned char) (0x80 | ((c >> 6) & 0x3F));       //$CD:20021119
    C = (unsigned char) (0x80 | (c & 0x3F));
    if (fputc_raw(a, f) == EOF) return 0;
    if (fputc_raw(b, f) == EOF) return 0;
    if (fputc_raw(C, f) == EOF) return 0;
    return 1;
}


/**
 * Unicode version of fputc. Returns 0 if an error occurs; 1 otherwise.
 */
int u_fputc_raw(Encoding encoding, unichar c, FILE *f) {
    switch (encoding) {
        case UTF16_LE:
            return u_fputc_UTF16LE_raw(c, f);
        case UTF16_BE:
            return u_fputc_UTF16BE_raw(c, f);
        case UTF8:
            return u_fputc_UTF8_raw(c, f);
    }
    return 0;
}


/**
 * Unicode version of fputc that saves '\n' as '\r\n'.
 * Returns 0 if an error occurs; 1 otherwise.
 */
int u_fputc(Encoding encoding, unichar c, FILE *f) {
    if (c == '\n') {
        if (!u_fputc_raw(encoding, 0x0D, f)) return 0;
    }
    return u_fputc_raw(encoding, c, f);
}


/**
 * UTF16 version of ungetc. In fact, we just rewind 2 bytes before in 'f'.
 * At the opposite of the real ungetc, it does not push back the given
 * character to the stream.
 *
 * Returns 1 in case of success; 0 otherwise.
 */
int u_ungetc_UTF16_raw(unichar c, FILE *f) {
    return (fseek(f, -2, SEEK_CUR) == 0) ? 1 : 0;
}


/**
 * UTF16-LE version of ungetc. In fact, we just rewind 2 bytes before in 'f'.
 * At the opposite of the real ungetc, it does not push back the given
 * character to the stream.
 *
 * Returns 1 in case of success; 0 otherwise.
 */
int u_ungetc_UTF16LE_raw(unichar c, FILE *f) {
    return u_ungetc_UTF16_raw(c, f);
}


/**
 * UTF16-BE version of ungetc. In fact, we just rewind 2 bytes before in 'f'.
 * At the opposite of the real ungetc, it does not push back the given
 * character to the stream.
 *
 * Returns 1 in case of success; 0 otherwise.
 */
int u_ungetc_UTF16BE_raw(unichar c, FILE *f) {
    return u_ungetc_UTF16_raw(c, f);
}


/**
 * UTF8 version of ungetc. In fact, we just rewind 'n' bytes before in 'f',
 * where 'n' is the length of the UTF8 represention of 'c'.
 * At the opposite of the real ungetc, it does not push back the given
 * character to the stream.
 *
 * Returns 1 in case of success; 0 otherwise.
 */
int u_ungetc_UTF8_raw(unichar c, FILE *f) {
    int number_of_bytes;
    if (c <= 0x7F) {
        /* Case of a 1 byte character 0XXX XXXX */
        number_of_bytes = -1;
    } else if (c <= 0x7FF) {
        /* 2 bytes 110X XXXX*/
        number_of_bytes = -2;
    } else/* if (c<=0xFFFF)*/ { //Always true due to limited range of data type
        /* 3 bytes 1110X XXXX */
        number_of_bytes = -3;
    }
    return (fseek(f, number_of_bytes, SEEK_CUR) == 0) ? 1 : 0;
}


/**
 * Unicode version of ungetc. In fact, we just rewind 'n' bytes before in 'f',
 * where 'n' is the length of the represention of 'c' in the given encoding.
 * At the opposite of the real ungetc, it does not push back the given
 * character to the stream.
 *
 * Returns 1 in case of success; 0 otherwise.
 */
int u_ungetc_raw(Encoding encoding, unichar c, FILE *f) {
    switch (encoding) {
        case UTF16_LE:
            return u_ungetc_UTF16LE_raw(c, f);
        case UTF16_BE:
            return u_ungetc_UTF16BE_raw(c, f);
        case UTF8:
            return u_ungetc_UTF8_raw(c, f);
    }
    return 0;
}


/**
 * Unicode version of ungetc. In fact, we just rewind 'n' bytes before in 'f',
 * where 'n' is the length of the represention of 'c' in the given encoding.
 * If 'c' is '\n', then we also ungetc a '\r'.
 * At the opposite of the real ungetc, it does not push back the given
 * character to the stream.
 *
 * Returns 1 in case of success; 0 otherwise.
 */
int u_ungetc(Encoding encoding, unichar c, FILE *f) {
    if (c == '\n') {
        if (!u_ungetc_raw(encoding, c, f)) return 0;
        if (!u_ungetc_raw(encoding, '\r', f)) return 0;
        return 1;
    }
    return u_ungetc_raw(encoding, c, f);
}


/**
 * Writes N characters from t. Returns the number of characters written.
 * It does not write '\r\n' for '\n'.
 */
int u_fwrite_raw(Encoding encoding, const unichar *t, int N, FILE *f) {
    for (int i = 0; i < N; i++) {
        if (!u_fputc_raw(encoding, t[i], f)) return i;
    }
    return N;
}


/**
 * Writes N characters from t. Returns the number of characters written.
 * It writes '\r\n' for '\n'.
 */
int u_fwrite(Encoding encoding, const unichar *t, int N, FILE *f) {
    for (int i = 0; i < N; i++) {
        if (!u_fputc(encoding, t[i], f)) return i;
    }
    return N;
}


/**
 * Prints a char string into a file. Characters are promoted to unicode
 * and encoded according to the given encoding.
 */
void u_fprints_char(Encoding encoding, const char *s, FILE *f) {
    int i = 0;
    while (s[i] != '\0')
        u_fputc(encoding, (unichar) ((unsigned char) s[i++]), f);
}


/**
 * Reads from the file 'f' until it finds the end of line '\n' or
 * the end of file. The characters read are written in 'line'. The
 * function returns EOF if the current position in the file is at the
 * end of file; otherwise, it returns the number of characters read, possibly
 * 0 if there is an empty line.
 *
 * NOTE: there is no overflow control!
 */
int u_fgets(Encoding encoding, unichar *line, FILE *f) {
    int c;
    int i = 0;
    while ((c = u_fgetc(encoding, f)) != EOF && c != '\n') {
        line[i++] = (unichar) c;
    }
    if (i == 0 && c == EOF) {
        /* If we are at the end of file */
        return EOF;
    }
    line[i] = '\0';
    return i;
}


/**
 * Reads a complete line or at most (size-1) unichars if the line is too long.
 * If the line is not too long, the '\n' is put before the final '\0'.
 * The function skips all '\r' and the resulting buffer is always '\0' ended.
 * It returns the length of the string:
 * - EOF : means that it was the end of file
 * - 0 : means that we have read an empty line ended by '\n'
 * - (len ==(size-1)) and (line[len-1] != '\n') : means that the line was too long for the buffer
 * - (0 < len < size-1) : means that we have read a complete line (str[len-1]=='\n', unless EOF)
 *
 * Author: Olivier Blanc
 * Modified by Sébastien Paumier
 */

int u_fgets(Encoding encoding, unichar *line, int size, FILE *f) {
    int i = 0;
    int c = 0; //Initialized in order to avoid warning
    while ((i < (size - 1)) && ((c = u_fgetc(encoding, f)) != EOF)) {
        line[i++] = (unichar) c;
        if (c == '\n') break;
    }
    if (i == 0 && c != '\n') return EOF;
    line[i] = 0;
    return i;
}


/**
 * This function acts exactly as 'u_fgets' does, except that
 * it stops at an end of line if and only if it is not protected by
 * a backslash. Backslashe that are not immediately before a '\n' are taken
 * as normal characters. The function returns the length of 'line'.
 * NOTE: this is an approximation, since we cannot represent a single line
 * ended by a backslash.
 *
 * Example:
 *
 * abc\de\
 * ef
 *
 * will lead to a string like: a b c \ d e \n e f
 */
int u_fgets2(Encoding encoding, unichar *line, FILE *f) {
    int pos, length;
    if (EOF == (pos = u_fgets(encoding, line, f))) {
        /* If we are at the end of file, then we return EOF */
        return EOF;
    }
    if (pos == 0) {
        /* If we have read an empty line, there is nothing more to do */
        return 0;
    }
    length = pos;
/* Otherwise, we check if the line we have just read is ended by a backslash.
 * In that case, we add a \n to it and we read another line. */
    while (line[length - 1] == '\\') {
        /* We try to read another line. We try to store it at &(line[length]),
    * because, if we can read such a line, we will have to replace the
    * backslash by a \n */
        pos = u_fgets(encoding, &(line[length]), f);
        if (pos == EOF) {
            /* If we cannot read another line, we return the current length */
            return length;
        }
        /* Otherwise, we put a \n before the line we have just read, and we update the length */
        line[length - 1] = '\n';
        length = length + pos;
    }
    return length;
}


/**
 * Unicode version of fprintf. It supports all the printf format options.
 * It also supports:
 * - %C for printing a unicode character
 * - %S for printing a unicode string
 * - %R for printing the reversed of a unicode string
 * - %H combined with one of the 3 previous can be used to display HTML
 *   things. For instance, if we do u_printf("%HC",c); it will print:
 *   &lt;   if c='<'
 *   &gt;   if c='>'
 *   &amp;  if c='&'
 *   c      otherwise
 *   See 'htmlize' for details.
 *
 * Author: Sébastien Paumier
 * Original version with format option restrictions: Olivier Blanc
 */
int u_vfprintf(Encoding encoding, FILE *f, const char *format, va_list list) {
    int n_printed = 0;
    int i;
    double d;
    char c;
    void *p;
    unichar uc;
    char *s;
    unichar *us;
    while (*format) {
        if (*format == '%') {
            /* If we have a special sequence introduced by '%' */
            format++;
            switch (*format) {
                /* If we have %% we must print a '%' */
                case '%':
                    u_fputc(encoding, '%', f);
                    n_printed++;
                    break;

                    /* If we have %c or %C we must print an unicode character */
                case 'c': /* We intercept %c here, because of the \n that always
                      must be encoded as \r\n */
                case 'C': {
                    uc = (unichar) va_arg(list, int);
                    u_fputc(encoding, uc, f);
                    n_printed++;
                    break;
                }

                case 'H': {
                    /* If we have a '%H', it means that we have to print HTML things */
                    format++;
                    if (*format == 'C' || *format == 'c') {
                        /* If we have to print a HTML character */
                        unichar tmp[2];
                        tmp[0] = (unichar) va_arg(list, int);
                        tmp[1] = '\0';
                        unichar html[32];
                        int l = htmlize(tmp, html);
                        u_fprints(encoding, html, f);
                        n_printed = n_printed + l;
                    } else if (*format == 'S') {
                        /* If we have to print a HTML string */
                        us = va_arg(list, unichar*);
                        if (us == NULL) {
                            u_fprints(encoding, "(null)", f);
                            n_printed = n_printed + 6;
                        } else {
                            unichar html[4096];
                            int l = htmlize(us, html);
                            u_fprints(encoding, html, f);
                            n_printed = n_printed + l;
                        }
                    } else if (*format == 'R') {
                        /* If we have to print a HTML reversed string */
                        us = va_arg(list, unichar*);
                        if (us == NULL) {
                            u_fprints(encoding, "(null)", f);
                            n_printed = n_printed + 6;
                        } else {
                            unichar reversed[4096];
                            mirror(us, reversed);
                            unichar html[4096];
                            int l = htmlize(reversed, html);
                            u_fprints(encoding, html, f);
                            n_printed = n_printed + l;
                        }
                    } else fatal_error("Invalid format option %%H%c\n", *format);
                    break;
                }

                    /* If we have %S we must print an unicode string */
                case 'S': {
                    us = va_arg(list, unichar*);
                    if (us == NULL) {
                        u_fprints(encoding, "(null)", f);
                        n_printed = n_printed + 6;
                    } else {
                        u_fprints(encoding, us, f);
                        n_printed = n_printed + u_strlen(us);
                    }
                    break;
                }

                    /* If we have %R we must print a reversed unicode string */
                case 'R': {
                    us = va_arg(list, unichar*);
                    if (us == NULL) {
                        /* We don't want to print ")llun(" when the string to reverse is NULL */
                        u_fprints(encoding, "(null)", f);
                        n_printed = n_printed + 6;
                        break;
                    }
                    unichar reversed[4096];
                    n_printed = n_printed + mirror(us, reversed);
                    u_fprints(encoding, reversed, f);
                    break;
                }

                    /* If we have %n, we must store the number of characters that have
          * already been printed into the given int*. */
                case 'n': {
                    int *res = va_arg(list, int*);
                    *res = n_printed;
                    break;
                }

                    /* If we have '%???', we let sprintf do the job */
                default: {
                    /* We get back on the '%' */
                    format--;
                    int z = 0;
                    char format2[64];
                    char result[4096];
                    do {
                        format2[z++] = *format;
                        format++;
                    } while (format2[z - 1] != '\0' && !strchr("diouxXeEfgcsp", format2[z - 1]));
                    /* We get back one character */
                    format--;
                    if (format2[z - 1] == '\0') {
                        fatal_error("Invalid format option in u_printf:\n%s\n", format2);
                    }
                    format2[z] = '\0';
                    switch (format2[z - 1]) {
                        case 'd':
                        case 'i':
                        case 'o':
                        case 'u':
                        case 'x':
                        case 'X': {
                            i = va_arg(list, int);
                            n_printed = n_printed + sprintf(result, format2, i);
                            break;
                        }
                        case 'e':
                        case 'E':
                        case 'f':
                        case 'g': {
                            d = va_arg(list, double);
                            n_printed = n_printed + sprintf(result, format2, d);
                            break;
                        }
                        case 'c': {
                            c = va_arg(list, int);
                            n_printed = n_printed + sprintf(result, format2, c);
                            break;
                        }
                        case 's': {
                            s = va_arg(list, char*);
                            n_printed = n_printed + sprintf(result, format2, s);
                            break;
                        }
                        case 'p': {
                            p = va_arg(list, void*);
                            n_printed = n_printed + sprintf(result, format2, p);
                            break;
                        }
                    }
                    u_fprints_char(encoding, result, f);
                    break;
                }
            }
        } else {
            /* If we have a normal character, we print it */
            u_fputc(encoding, (unsigned char) *format, f);
            n_printed++;
        }
        format++;
    }
    return n_printed;
}


/**
 * Unicode version of fprintf. See u_vfprintf for supported format options.
 *
 * Author: Olivier Blanc
 * Modified by Sébastien Paumier
 */
int u_fprintf(Encoding encoding, FILE *f, const char *format, ...) {
    va_list list;
    va_start(list, format);
    int n = u_vfprintf(encoding, f, format, list);
    va_end(list);
    return n;
}


/**
 * This function prints a message into a unicode string and returns the
 * size of the result. Note that if 'dest' is NULL, the function will
 * only count the size of the result without actually building it.
 * See u_fprintf for supported format options.
 *
 * Author: Olivier Blanc
 */
int u_sprintf(unichar *dest, const char *format, ...) {
    va_list list;
    va_start(list, format);
    int n = u_vsprintf(dest, format, list);
    va_end(list);
    return n;
}


/**
 * Unicode version of sprintf. It supports all the printf format options.
 * It also supports:
 * - %C for printing a unicode character
 * - %S for printing a unicode string
 * - %HS for printing a unicode string in HTML (see htmlize)
 * - %R for printing the reversed of a unicode string
 * - %HR for printing the reversed of a unicode string in HTML (see htmlize)
 *
 * Author: Sébastien Paumier
 * Original version with format option restrictions: Olivier Blanc
 */
int u_vsprintf(unichar *dest, const char *format, va_list list) {
    int n_printed = 0;
    int i;
    double d;
    char c;
    void *p;
    unichar uc;
    char *s;
    unichar *us;
    while (*format) {
        if (*format == '%') {
            /* If we have a special sequence introduced by '%' */
            format++;
            switch (*format) {
                /* If we have %% we must print a '%' */
                case '%':
                    if (dest) dest[n_printed] = '%';
                    n_printed++;
                    break;

                    /* If we have %C we must print an unicode character */
                case 'C': {
                    uc = (unichar) va_arg(list, int);
                    if (dest) dest[n_printed] = uc;
                    n_printed++;
                    break;
                }

                case 'H': {
                    /* If we have a '%H', it means that we have to print HTML things */
                    format++;
                    if (*format == 'S') {
                        /* If we have to print a HTML string */
                        us = va_arg(list, unichar*);
                        if (us == NULL) {
                            if (dest) u_strcpy(&(dest[n_printed]), "(null)");
                            n_printed = n_printed + 6;
                        } else {
                            unichar html[4096];
                            int l = htmlize(us, html);
                            if (dest) u_strcpy(&(dest[n_printed]), html);
                            n_printed = n_printed + l;
                        }
                    } else if (*format == 'R') {
                        /* If we have to print a HTML reversed string */
                        us = va_arg(list, unichar*);
                        if (us == NULL) {
                            if (dest) u_strcpy(&(dest[n_printed]), "(null)");
                            n_printed = n_printed + 6;
                        } else {
                            unichar reversed[4096];
                            mirror(us, reversed);
                            unichar html[4096];
                            int l = htmlize(reversed, html);
                            if (dest) u_strcpy(&(dest[n_printed]), html);
                            n_printed = n_printed + l;
                        }
                    } else fatal_error("Invalid format option %%H%c\n", *format);
                    break;
                }

                    /* If we have %S we must print an unicode string */
                case 'S': {
                    us = va_arg(list, unichar*);
                    if (us == NULL) {
                        if (dest) u_strcpy(&(dest[n_printed]), "(null)");
                        n_printed = n_printed + 6;
                    } else {
                        if (dest) u_strcpy(&(dest[n_printed]), us);
                        n_printed = n_printed + u_strlen(us);
                    }
                    break;
                }

                    /* If we have %R we must print a reversed unicode string */
                case 'R': {
                    us = va_arg(list, unichar*);
                    if (us == NULL) {
                        /* We don't want to print ")llun(" when the string to reverse is NULL */
                        if (dest) u_strcpy(&(dest[n_printed]), "(null)");
                        n_printed = n_printed + 6;
                        break;
                    }
                    unichar reversed[4096];
                    int old = n_printed;
                    n_printed = n_printed + mirror(us, reversed);
                    if (dest) u_strcpy(&(dest[old]), reversed);
                    break;
                }

                    /* If we have %n, we must store the number of characters that have
          * already been printed into the given int*. */
                case 'n': {
                    int *res = va_arg(list, int*);
                    *res = n_printed;
                    break;
                }

                    /* If we have '%???', we let sprintf do the job */
                default: {
                    /* We get back on the '%' */
                    format--;
                    int z = 0;
                    char format2[64];
                    char result[4096];
                    do {
                        format2[z++] = *format;
                        format++;
                    } while (format2[z - 1] != '\0' && !strchr("diouxXeEfgcsp", format2[z - 1]));
                    /* We get back one character */
                    format--;
                    if (format2[z - 1] == '\0') {
                        fatal_error("Invalid format option in u_printf:\n%s\n", format2);
                    }
                    format2[z] = '\0';
                    int n_printed_old = n_printed;
                    switch (format2[z - 1]) {
                        case 'd':
                        case 'i':
                        case 'o':
                        case 'u':
                        case 'x':
                        case 'X': {
                            i = va_arg(list, int);
                            n_printed = n_printed + sprintf(result, format2, i);
                            break;
                        }
                        case 'e':
                        case 'E':
                        case 'f':
                        case 'g': {
                            d = va_arg(list, double);
                            n_printed = n_printed + sprintf(result, format2, d);
                            break;
                        }
                        case 'c': {
                            c = va_arg(list, int);
                            n_printed = n_printed + sprintf(result, format2, c);
                            break;
                        }
                        case 's': {
                            s = va_arg(list, char*);
                            n_printed = n_printed + sprintf(result, format2, s);
                            break;
                        }
                        case 'p': {
                            p = va_arg(list, void*);
                            n_printed = n_printed + sprintf(result, format2, p);
                            break;
                        }
                    }
                    if (dest) u_strcpy(&(dest[n_printed_old]), result);
                    break;
                }
            }
        } else {
            /* If we have a normal character, we print it */
            if (dest) dest[n_printed] = (unsigned char) *format;
            n_printed++;
        }
        format++;
    }
    if (dest) dest[n_printed] = '\0';
    return n_printed;
}


/**
 * Returns a non-zero value if 'c' is an hexadecimal digit; 0 otherwise.
 */
bool u_is_hexa_digit(unichar c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}


/**
 * Returns a non-zero value if 'c' is a separator; 0 otherwise.
 */
int is_separator(unichar c) {
    return (c == ' ') || (c == '\t') || (c == '\r') || (c == '\n');
}


/**
 * Unicode version of fscanf. The supported format options are:
 * %c : normal character
 * %C : unicode character
 * %s : normal string
 * %S : unicode string
 * %d : decimal integer of the form 45 -45 or +45
 * %x : hexadecimal integer of the form a9 -B75 or +f8CE
 *
 * The separators are space, tabulation '\r' and '\n'. They are skipped in
 * input stream BUT NOT IN FORMAT STRING!!! So, if we do:
 *
 *    u_fscanf(f,"%d %s",&i,s);
 *
 * it will match only if there is a space after the integer. For instance, you can use this
 * feature to eat EOL. If we want to an integer and the EOL sequences that follows,
 * just use:
 *
 *    u_fscanf(f,"%d\r\n",&i);
 *
 * Note 1: if this function is applied on stdin, it may have read one character in advance.
 * Note 2: if yout type u_fscanf(f,"%d\n",&i); the function will skip any separator that is
 *         not '\n' after the integer, so that the line " 45   \t   \n" will be entirely read.
 *
 * Author: Sébastien Paumier
 */
int u_vfscanf(Encoding encoding, FILE *f, const char *format, va_list list) {
    int c;
    int *i;
    unichar *uc;
    char *ch;
    int n_variables = 0;
    static int stdin_ch = -1;
    while (*format) {
        /* First, we get the current character */
        if (f == stdin) {
            /* If we read from the input stream, we may have to use the 1-char buffer */
            if (stdin_ch != -1) {
                c = stdin_ch;
                stdin_ch = -1;
            } else {
                /* If we have no character in the 1-char buffer, we take one from the file */
                c = u_fgetc_raw(encoding, f);
            }
        } else {
            /* If we have to take one from the file */
            c = u_fgetc_raw(encoding, f);
        }
        if (c == EOF) {
            if (n_variables == 0) {
                /* If the EOF occurs before the first conversion, we return EOF */
                return EOF;
            }
            /* Otherwise, we return the number of variables that have already been read */
            return n_variables;
        }
        /* Then we deal with the separators. If the current format char is a separator,
    * we have two cases: */
        if (is_separator(*format)) {
            if (c == *format) {
                /* 1) the format char is the same than the input char => we go on */
                format++;
                continue;
            } else {
                /* 2) the format is for instance a '\t' and we have a current input
          *    separator that is not a '\t' => we skip all separators that are not '\t' */
                while ((c = u_fgetc_raw(encoding, f)) != EOF && is_separator(c) && c != *format);
                /* Subcase 1: EOF */
                if (c == EOF) return (n_variables == 0) ? EOF : n_variables;
                /* Subcase 2: we found the correct separator */
                if (c == *format) {
                    format++;
                    continue;
                }
                /* Subcase 3: we found a character that is not the expected separator => we fail */
                return n_variables;
            }
        }
        /* Now we must deal with an input separator when the current format character
    * is not a separator */
        while (c != EOF && is_separator(c)) {
            c = u_fgetc_raw(encoding, f);
        }
        /* Again, we may have reached the EOF */
        if (c == EOF) {
            if (n_variables == 0) {
                /* If the EOF occurs before the first conversion, we return EOF */
                return EOF;
            }
            /* Otherwise, we return the number of variables that have already been read */
            return n_variables;
        }
        if (*format == '%') {
            /* If we have a special sequence introduced by '%' */
            format++;
            switch (*format) {
                /* If we have %% we must read a '%' */
                case '%': {
                    if (c != '%') return n_variables;
                    break;
                }

                    /* If we have %c we must read a normal character */
                case 'c': {
                    ch = va_arg(list, char*);
                    *ch = (char) c;
                    n_variables++;
                    break;
                }

                    /* If we have %C we must read a unicode character */
                case 'C': {
                    uc = va_arg(list, unichar*);
                    *uc = c;
                    n_variables++;
                    break;
                }

                    /* If we have %s we must read a normal string */
                case 's': {
                    ch = va_arg(list, char*);
                    int pos = 0;
                    do {
                        ch[pos++] = (char) c;
                    } while ((c = u_fgetc_raw(encoding, f)) != EOF && !is_separator(c));
                    ch[pos] = '\0';
                    if (c != EOF) {
                        /* If we have read a separator, we put it back in the file, for
                * the case where the user would like to read it with another read function */
                        if (f == stdin) {
                            stdin_ch = c;
                        } else {
                            u_ungetc_raw(encoding, c, f);
                        }
                    }
                    n_variables++;
                    break;
                }

                    /* If we have %S we must read a unicode string */
                case 'S': {
                    uc = va_arg(list, unichar*);
                    int pos = 0;
                    do {
                        uc[pos++] = c;
                    } while ((c = u_fgetc_raw(encoding, f)) != EOF && !is_separator(c));
                    uc[pos] = '\0';
                    if (c != EOF) {
                        /* If we have read a separator, we put it back in the file, for
                * the case where the user would like to read it with another read function */
                        if (f == stdin) {
                            stdin_ch = c;
                        } else {
                            u_ungetc_raw(encoding, c, f);
                        }
                    }
                    n_variables++;
                    break;
                }

                    /* If we have %d we must read a decimal integer, eventually preceded by '+' or '-' */
                case 'd': {
                    i = va_arg(list, int*);
                    int multiplier = 1;
                    if (c == '+' || c == '-') {
                        /* If we have a sign, we must read the next character */
                        if (c == '-') multiplier = -1;
                        c = u_fgetc_raw(encoding, f);
                        if (c == EOF || c < '0' || c > '9') {
                            /* If we have reached the EOF or if we have a non digit character */
                            return n_variables;
                        }
                    } else if (c < '0' || c > '9') {
                        /* If we have a character that neither a sign nor a digit, we fail */
                        return n_variables;
                    }
                    *i = 0;
                    do {
                        *i = (*i) * 10 + (unichar) c - '0';
                    } while ((c = u_fgetc_raw(encoding, f)) != EOF && c >= '0' && c <= '9');
                    *i = (*i) * multiplier;
                    if (c != EOF) {
                        /* If we have read a non digit, we put it back in the file, for
                * the case where the user would like to read it with another read function */
                        if (f == stdin) {
                            stdin_ch = c;
                        } else {
                            u_ungetc_raw(encoding, c, f);
                        }
                    }
                    n_variables++;
                    break;
                }

                    /* If we have %x we must read an hexadecimal integer, eventually preceeded by '+' or '-' */
                case 'x': {
                    i = va_arg(list, int*);
                    int multiplier = 1;
                    if (c == '+' || c == '-') {
                        /* If we have a sign, we must read the next character */
                        if (c == '-') multiplier = -1;
                        c = u_fgetc_raw(encoding, f);
                        if (c == EOF || !u_is_hexa_digit(c)) {
                            /* If we have reached the EOF or if we have a non hexa digit character */
                            return n_variables;
                        }
                    } else if (!u_is_hexa_digit(c)) {
                        /* If we have a character that neither a sign nor a digit, we fail */
                        return n_variables;
                    }
                    *i = 0;
                    do {
                        if (c >= '0' && c <= '9') c = c - '0';
                        else if (c >= 'a' && c <= 'f') c = c - 'a' + 10;
                        else c = c - 'A' + 10;
                        *i = (*i) * 16 + c;
                    } while ((c = u_fgetc_raw(encoding, f)) != EOF && u_is_hexa_digit(c));
                    *i = (*i) * multiplier;
                    if (c != EOF) {
                        /* If we have read a non digit, we put it back in the file, for
                * the case where the user would like to read it with another read function */
                        if (f == stdin) {
                            stdin_ch = c;
                        } else {
                            u_ungetc_raw(encoding, c, f);
                        }
                    }
                    n_variables++;
                    break;
                }
            }
        } else {
            /* If we have a normal character, we must read it */
            if (c != *format) return n_variables;
        }
        format++;
    }
    return n_variables;
}


/**
 * Unicode version of fscanf. See u_vfscanf for supported format options.
 *
 * Author: Sébastien Paumier
 */
int u_fscanf(Encoding encoding, FILE *f, const char *format, ...) {
    va_list list;
    va_start(list, format);
    int n = u_vfscanf(encoding, f, format, list);
    va_end(list);
    return n;
}


/**
 * Unicode version of sscanf. See u_vfscanf for supported format options.
 *
 * Author: Sébastien Paumier
 */
int u_vsscanf(unichar *s, const char *format, va_list list) {
    int c;
    int *i;
    unichar *uc;
    char *ch;
    int n_variables = 0;
    int pos = 0;
    while (*format) {
        /* First, we skip the separators, but only if the current format character is
    * not a separator */
        if (!is_separator(*format)) {
            while (is_separator(s[pos])) pos++;
            if (s[pos] == '\0') {
                if (n_variables == 0) {
                    /* If the EOF occurs before the first conversion, we return EOF */
                    return EOF;
                }
                /* Otherwise, we return the number of variables that have already been read */
                return n_variables;
            }
        } else {
            /* If we have a separator in the format string, we must look exactly for it */
            while (s[pos] != '\0' && is_separator(s[pos]) && s[pos] != *format) pos++;
            if (s[pos] == '\0' || s[pos] != *format) {
                /* If we have not found the wanted separator, we fail */
                return (n_variables == 0) ? EOF : n_variables;
            }
            format++;
            continue;
        }
        if (*format == '%') {
            /* If we have a special sequence introduced by '%' */
            format++;
            switch (*format) {
                /* If we have %% we must read a '%' */
                case '%': {
                    if (s[pos] != '%') return n_variables;
                    break;
                }

                    /* If we have %c we must read a normal character */
                case 'c': {
                    ch = va_arg(list, char*);
                    *ch = (char) s[pos++];
                    n_variables++;
                    break;
                }

                    /* If we have %C we must read a unicode character */
                case 'C': {
                    uc = va_arg(list, unichar*);
                    *uc = s[pos++];
                    n_variables++;
                    break;
                }

                    /* If we have %s we must read a normal string */
                case 's': {
                    ch = va_arg(list, char*);
                    int pos2 = 0;
                    do {
                        ch[pos2++] = (char) s[pos++];
                    } while (s[pos] != '\0' && !is_separator(s[pos]));
                    ch[pos2] = '\0';
                    if (s[pos] != '\0') {
                        /* If we have read a separator, we have nothing to do */
                    }
                    n_variables++;
                    break;
                }

                    /* If we have %S we must read a unicode string */
                case 'S': {
                    uc = va_arg(list, unichar*);
                    int pos2 = 0;
                    do {
                        uc[pos2++] = s[pos++];
                    } while (s[pos] != '\0' && !is_separator(s[pos]));
                    uc[pos2] = '\0';
                    if (s[pos] != '\0') {
                        /* If we have read a separator, we have nothing to do */
                    }
                    n_variables++;
                    break;
                }

                    /* If we have %d we must read a decimal integer, eventually preceeded by '+' or '-' */
                case 'd': {
                    i = va_arg(list, int*);
                    int multiplier = 1;
                    if (s[pos] == '+' || s[pos] == '-') {
                        /* If we have a sign, we must read the next character */
                        if (s[pos] == '-') multiplier = -1;
                        pos++;
                        if (s[pos] == '\0' || s[pos] < '0' || s[pos] > '9') {
                            /* If we have reached the EOF or if we have a non digit character */
                            return n_variables;
                        }
                    } else if (s[pos] < '0' || s[pos] > '9') {
                        /* If we have a character that neither a sign nor a digit, we fail */
                        return n_variables;
                    }
                    *i = 0;
                    do {
                        *i = (*i) * 10 + (unichar) s[pos++] - '0';
                    } while (s[pos] != '\0' && s[pos] >= '0' && s[pos] <= '9');
                    *i = (*i) * multiplier;
                    if (s[pos] != '\0') {
                        /* If we have read a non digit, we have nothing to do */
                    }
                    n_variables++;
                    break;
                }

                    /* If we have %x we must read an hexadecimal integer, eventually preceeded by '+' or '-' */
                case 'x': {
                    i = va_arg(list, int*);
                    int multiplier = 1;
                    if (s[pos] == '+' || s[pos] == '-') {
                        /* If we have a sign, we must read the next character */
                        if (s[pos] == '-') multiplier = -1;
                        pos++;
                        if (s[pos] == '\0' || !u_is_hexa_digit(s[pos])) {
                            /* If we have reached the EOF or if we have a non hexa digit character */
                            return n_variables;
                        }
                    } else if (!u_is_hexa_digit(s[pos])) {
                        /* If we have a character that neither a sign nor a digit, we fail */
                        return n_variables;
                    }
                    *i = 0;
                    do {
                        c = s[pos++];
                        if (c >= '0' && c <= '9') c = c - '0';
                        else if (c >= 'a' && c <= 'f') c = c - 'a' + 10;
                        else c = c - 'A' + 10;
                        *i = (*i) * 16 + c;
                    } while (s[pos] != '\0' && u_is_hexa_digit(s[pos]));
                    *i = (*i) * multiplier;
                    if (s[pos] != '\0') {
                        /* If we have read a non digit, we have nothing to do */
                    }
                    n_variables++;
                    break;
                }
            }
        } else {
            /* If we have a normal character, we must read it */
            if (s[pos++] != *format) return n_variables;
        }
        format++;
    }
    return n_variables;
}


/**
 * Unicode version of sscanf. See u_vfscanf for supported format options.
 *
 * Author: Sébastien Paumier
 */
int u_sscanf(unichar *input, const char *format, ...) {
    va_list list;
    va_start(list, format);
    int n = u_vsscanf(input, format, list);
    va_end(list);
    return n;
}


/**
 * Prints an unicode string into a file.
 */
void u_fprints(Encoding encoding, unichar *s, FILE *f) {
    int i = 0;
    if (s == NULL) {
        return;
    }
    while (s[i] != '\0') {
        u_fputc(encoding, s[i++], f);
    }
}


/**
 * Prints a char string into a file.
 */
void u_fprints(Encoding encoding, const char *s, FILE *f) {
    int i = 0;
    if (s == NULL) {
        return;
    }
    while (s[i] != '\0') {
        u_fputc(encoding, (unichar) s[i++], f);
    }
}


/* ------------------- String functions ------------------- */

/**
 * Unicode version of strlen.
 */
int u_strlen(const unichar *s) {
    int i = 0;
    while (s[i++]);
    return (i - 1);
}


/**
 * Unicode version of strcpy.
 */
unichar *u_strcpy(unichar *dest, const unichar *src) {
    unichar *s = dest; // backup pointer to start of destination string
    unichar c;
    do {
        c = *src++;
        *dest++ = c;
    } while (c != '\0');
    return s;
}


/**
 * unicode version of strncpy
 */
unichar *u_strncpy(unichar *dest, const unichar *src, int n) {
    const unichar *src_end = src + n;
    for (; *src && src != src_end; ++src, ++dest)
        *dest = *src;
    for (; src != src_end; ++src, ++dest)
        *dest = 0;
}

/**
 * Unicode version of strcpy that takes a non unicode source string.
 */
unichar *u_strcpy(unichar *dest, const char *src) {
    unichar *s = dest; // backup pointer to start of destination string
    unichar c;
    do {
        c = *src++;
        *dest++ = c;
    } while (c != '\0');
    return s;
}


/**
 * Unicode version of strcat.
 */
unichar *u_strcat(unichar *dest, unichar *src) {
    unichar *s1 = dest;
    const unichar *s2 = src;
    unichar c;
/* First we go at the end of the destination string */
    do {
        c = *s1++;
    } while (c != (unichar) '\0');
    s1 -= 2;
/* And we concatenate the 'src' string */
    do {
        c = *s2++;
        *++s1 = c;
    } while (c != (unichar) '\0');
    return dest;
}


/**
 * Unicode version of strcat.
 */
unichar *u_strcat(unichar *dest, const char *src) {
    int i, j = 0;
    i = u_strlen(dest);
    while ((dest[i++] = (unichar) ((unsigned char) src[j++])) != 0);
    return dest;
}


/**
 * Unicode version of strcmp that tolerates NULL strings.
 */
int u_strcmp(const unichar *a, const unichar *b) {
    if (a == NULL) {
        if (b == NULL) return 0;
        return 1;
    }
    if (b == NULL) return -1;
    const unichar *a_p = a;
    const unichar *b_p = b;
    unichar a_c;
    unichar b_c;
    do {
        a_c = (unichar) *a_p++;
        b_c = (unichar) *b_p++;
        if (a_c == '\0') return a_c - b_c;
    } while (a_c == b_c);
    return a_c - b_c;
}


/**
 * Unicode version of strcmp that tolerates NULL strings.
 */
int u_strcmp(const unichar *a, const char *b) {
    if (a == NULL) {
        if (b == NULL) return 0;
        return 1;
    }
    if (b == NULL) return -1;
    const unichar *a_p = a;
    const unsigned char *b_p = (const unsigned char *) b;
    unichar a_c;
    unsigned char b_c;
    do {
        a_c = (unichar) *a_p++;
        b_c = (unsigned char) *b_p++;
        if (a_c == '\0') return a_c - b_c;
    } while (a_c == b_c);
    return a_c - b_c;
}


/**
 * Unicode version of strdup.
 * This function returns an allocated string that is a copy of the given one.
 *
 * Author: Olivier Blanc
 */
unichar *u_strdup(const unichar *str) {
    if (str == NULL) return NULL;
    unichar *res = (unichar *) malloc((u_strlen(str) + 1) * sizeof(unichar));
    if (res == NULL) fatal_error("Not enough memory in u_strdup\n");
    return u_strcpy(res, str);
}


/**
 * Unicode version of strndup.
 *   -- why this is then called u_strdup, and not u_strndup? (Sebastian, Munich)
 * This version returns an allocated string that is a copy of the
 * n first bytes of the given one.
 *
 * Author: Olivier Blanc
 */
unichar *u_strdup(const unichar *str, int n) {
    if (str == NULL) return NULL;
    if (n < 0)
        fatal_error("Invalid length in u_strdup\n");
    int length = u_strlen(str);
    if (length < n)
        n = length;
    unichar *res = (unichar *) malloc((n + 1) * sizeof(unichar));
    if (res == NULL)
        fatal_error("Not enough memory in u_strdup\n");
    u_strncpy(res, str, n);
    res[n] = '\0';
    return res;
}


/**
 * Unicode version of strdup.
 * This function returns an allocated string that is a copy of the given one.
 *
 * Author: Olivier Blanc
 */
unichar *u_strdup(const char *str) {
    if (str == NULL) return NULL;
    unichar *res = (unichar *) malloc((strlen(str) + 1) * sizeof(unichar));
    if (res == NULL) fatal_error("Not enough memory in u_strdup\n");
    return u_strcpy(res, str);
}


/**
 * Unicode version of strchr.
 * This function returns a pointer on the first occurrence of 'c' in 's', or
 * NULL if not found. If 'unprotected' is not null, the function looks for the
 * first unprotected occurrence of 'c'; otherwise, it looks for the first
 * occurrence, protected by a backslash or not.
 *
 * Author: Olivier Blanc
 * Modified by Sébastien Paumier
 */
unichar *u_strchr(const unichar *s, unichar c, int unprotected) {
    if (s == NULL) return NULL;
    while (*s) {
        if (*s == '\\' && unprotected) {
            /* If we are looking for an unprotected character, we skip any
       * protected character */
            s++;
            if (*s == '\0') return NULL;
        }
        if (*s == c) {
            return (unichar *) s;
        }
        s++;
    }
    return NULL;
}


/**
 * Unicode version of strchr.
 * This function returns a pointer on the first occurrence of 'c' in 's', or
 * NULL if not found.
 *
 * Author: Olivier Blanc
 */
unichar *u_strchr(const unichar *s, unichar c) {
    return u_strchr(s, c, 0);
}


/**
 * A version of strchr that looks for a unicode character in a normal string.
 * We do this instead of calling the original strchr with a cast of 'c' to 'char',
 * because such a cast would cause invalid matches.
 *
 * Author: Olivier Blanc
 * Modified by Sébastien Paumier
 */
char *u_strchr(char *s, unichar c) {
    if (s == NULL) return NULL;
    while (*s) {
        if (c == (unichar) *s) return s;
        s++;
    }
    return NULL;
}


/**
 * Unicode version of strpbrk.
 * This function returns a pointer on the first occurrence of any delimiter 's', or
 * NULL if not found.
 *
 * Author: Olivier Blanc
 */
unichar *u_strpbrk(const unichar *s, unichar *delimiters) {
    if (s == NULL) return NULL;
    while (*s) {
        if (u_strchr(delimiters, *s)) return (unichar *) s;
        s++;
    }
    return NULL;
}

unichar *u_strtrim(const unichar *s) {
    const unichar *begin(s);
    while (*begin && u_is_white(*begin))
        ++begin;
    const unichar *end(begin);
    while (*end)
        ++end;
    if (end != begin) {
        --end;
        while (end != begin && u_is_white(*end))
            --end;
        ++end;
    }
    std::size_t size(std::distance(begin, end));
    unichar *dest = new unichar[size + 1];
    std::copy(s, s + size, dest);
    dest[size] = 0;
    return dest;
}

unichar *u_non_white_begin(unichar *begin, unichar *end) {
    unichar *trim_begin(begin);
    while (trim_begin != end && u_is_white(*trim_begin))
        ++trim_begin;
    return trim_begin;
}

const unichar *u_non_white_begin(const unichar *begin, const unichar *end) {
    const unichar *trim_begin(begin);
    while (trim_begin != end && u_is_white(*trim_begin))
        ++trim_begin;
    return trim_begin;
}

unichar *u_non_white_end(unichar *begin, unichar *end) {
    unichar *trim_end(end);
    while (trim_end != begin && u_is_white(*(trim_end-1)))
        --trim_end;
    return trim_end;
}

const unichar *u_non_white_end(const unichar *begin, const unichar *end) {
    const unichar *trim_end(end);
    while (trim_end != begin && u_is_white(*(trim_end-1)))
        --trim_end;
    return trim_end;
}

unichar *u_non_white_begin(unichar *s, std::size_t start = 0) {
    return u_non_white_begin(s, s + start);
}

const unichar *u_non_white_begin(const unichar *s, std::size_t start = 0) {
    return u_non_white_begin(s, s + start);
}

unichar *u_non_white_end(unichar *s, std::size_t start = 0) {
    return u_non_white_end(s, s + start);
}

const unichar *u_non_white_end(const unichar *s, std::size_t start = 0) {
    return u_non_white_end(s, s + start);
}

/**
 * Unicode version of strpbrk.
 * This function returns a pointer on the first occurrence of any delimiter 's', or
 * NULL if not found.
 *
 * Author: Olivier Blanc
 */
unichar *u_strpbrk(const unichar *s, char *delimiters) {
    if (s == NULL) return NULL;
    while (*s) {
        if (u_strchr(delimiters, *s)) return (unichar *) s;
        s++;
    }
    return NULL;
}


/**
 * Converts the unichar* src into a char* dest.
 * dest is encoded in latin-1 (iso-8859-1) and non-convertible characters are skipped.
 *
 * Author: Sébastien Paumier
 * Modified by Sébastian Nagel
 */
void u_to_char(char *dest, unichar *src) {
    unichar c;
    do {
        c = *src++;
        if (c <= 0xFF) *dest++ = (char) c;
    } while (c != '\0');
}


/**
 * Puts a copy of 'src' into 'dst', replacing:
 * - multi-spaces by non-breakable spaces. Spaces at the beginning of the string
 *   are also converted, even if there is only one
 * - '< ' by "&lt;"
 * - '> ' by "&gt;"
 * - '& ' by "&amp;"
 *
 * Note that 'dst' is supposed to be large enough.
 * The function returns the length of 'dst'.
 */
int htmlize(unichar *src, unichar *dst) {
    if (src == NULL) {
        fatal_error("NULL error in ize\n");
    }
    int i = 0;
    int pos = 0;
    while (src[i] != '\0') {
        if (src[i] == ' ') {
            /* If we find a space, we look if we are at the beginning of the line,
       * or at the end, or on the first character of a space sequence. */
            if (i == 0 || src[i + 1] == '\0' || src[i + 1] == ' ') {
                /* Here, we have to print "&nbsp;" as many times as needed */
                while (src[i] == ' ') {
                    u_strcpy(&dst[pos], "&nbsp;");
                    pos = pos + 6;
                    i++;
                }
            } else {
                /* Otherwise, we put a single normal space */
                dst[pos++] = ' ';
                i++;
            }
        } else if (src[i] == '<') {
            u_strcpy(&dst[pos], "&lt;");
            pos = pos + 4;
            i++;
        } else if (src[i] == '>') {
            u_strcpy(&dst[pos], "&gt;");
            pos = pos + 4;
            i++;
        } else if (src[i] == '&') {
            u_strcpy(&dst[pos], "&amp;");
            pos = pos + 5;
            i++;
        } else {
            dst[pos++] = src[i++];
        }
    }
    dst[pos] = '\0';
    return pos;
}


/**
 * Copies the mirror of 'src' into 'dst'. Returns the length of the strings.
 */
int mirror(unichar *src, unichar *dst) {
    if (src == NULL) {
        fatal_error("NULL error in mirror\n");
    }
    int l = u_strlen(src) - 1;
    int pos = 0;
    while (l >= 0) {
        dst[pos++] = src[l--];
    }
    dst[pos] = '\0';
    return pos;
}


/**
 * Replaces 's' by its mirror and returns the length of the string,
 * or -1 if the string is NULL.
 */
int mirror(unichar *s) {
    if (s == NULL) return -1;
    int length = u_strlen(s);
    int a = 0;
    int b = length - 1;
    unichar tmp;
    while (a < b) {
        tmp = s[a];
        s[a] = s[b];
        s[b] = tmp;
        a++;
        b--;
    }
    return length;
}


/**
 * Returns the length of the longuest prefix common to the strings 'a' and 'b'.
 */
int get_longuest_prefix(unichar *a, unichar *b) {
    if (a == NULL || b == NULL) {
        return 0;
    }
    int i = 0;
    while (a[i] == b[i] && a[i] != '\0') i++;
    return i;
}


/**
 * This function returns a hash code for a unicode string.
 */
unsigned int hash_unichar(unichar *s) {
    if (s == NULL) {
        return 0;
    }
    unsigned int code = 0;
    int i = 0;
    while (s[i] != '\0') {
        code = code * 31 + s[i];
        i++;
    }
    return code;
}


//
// unicode version of is-end-of-line
//
bool u_is_eol(unichar c) { return (c == '\n'); }


//
// unicode version of isdigit
//
bool u_is_digit(unichar c) {
    return (c >= '0' && c <= '9');
}


//
// returns true if c is a basic latin letter
//
bool u_is_basic_latin_letter(unichar c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}


//
// returns true if c is a latin-1 supplement letter
//
bool u_is_latin1_supplement_letter(unichar c) {
    return (c >= 0xC0 && c <= 0xFF && c != 0xD7 && c != 0xF7);
}


//
// returns true if c is a latin extended-A letter
//
bool u_is_latin_extendedA_letter(unichar c) {
    return (c >= 0x0100 && c <= 0x017F);
}


//
// returns true if c is a latin extended-B letter
//
bool u_is_latin_extendedB_letter(unichar c) {
    return (c >= 0x0180 && c <= 0x0233 && c != 0x0220 && c != 0x221);
}


//
// returns true if c is in the IPA extensions letters
//
bool u_is_IPA_extensions_letter(unichar c) {
    return (c >= 0x0250 && c <= 0x02AD);
}


//
// returns true if c is a greek letter
//
bool u_is_greek_letter(unichar c) {
    return (c >= 0x0386 && c <= 0x03F5 && c != 0x0387 && c != 0x038B
            && c != 0x038D && c != 0x03A2 && c != 0x03CF && c != 0x03D8 && c != 0x03D9);
}

//------Beginning of Hyungue's inserts--------------

//
//	return true if c is a korean syllalbe
//
bool u_is_korea_syllabe_letter(unichar c) {
    return ((c >= 0xac00) && (c <= 0xd7af));
}
//
//	return true if c is a korean ideograme
//

bool u_is_CJK_Unified_Ideographs(unichar c) {
    return ((c >= 0x4e00) && (c <= 0x9fff));
}

bool u_is_cjk_compatibility_ideographs(unichar c) {
    return ((c >= 0xf900) && (c <= 0xfaff));
}

//
//	return true if c is a character of the alphabet coreen
//	when charcters of this zone exit in the korean text
//	these is symbols
//
bool u_is_Hangul_Compatility_Jamo(unichar c) {
    return ((c >= 0x3130) && (c <= 0x318f));
}

//
//	return true
//	these charcters of this zone can not existe in the korean text
//
bool u_is_Hangul_Jamo(unichar c) {
    return ((c >= 0x1100) && (c <= 0x11FF));
}
//------End of Hyungue's inserts--------------

//
// returns true if c is a cyrillic letter
//
bool u_is_cyrillic_letter(unichar c) {
    return (c >= 0x0400 && c <= 0x4F9 && (c < 0x0482 || c > 0x048B) && c != 0x04C5 && c != 0x04C6
            && c != 0x04C9 && c != 0x04CA && c != 0x04CD && c != 0x04CE && c != 0x04CF && c != 0x04F6
            && c != 0x04F7);
}


//
// returns true if c is an armenian letter
//
bool u_is_armenian_letter(unichar c) {
    return (c >= 0x0531 && c <= 0x587 && (c < 0x0557 || c > 0x0560));
}


//
// returns true if c is an hebrew letter
//
bool u_is_hebrew_letter(unichar c) {
    return (c >= 0x05D0 && c <= 0x05EA) || (c == 0x05F0 || c == 0x05F1 || c == 0x05F2);
}


//
// returns true if c is an arabic letter
//
bool u_is_arabic_letter(unichar c) {
    return ((c >= 0x0621 && c <= 0x063A) || (c >= 0x0641 && c <= 0x64A)
            || (c >= 0x0671 && c <= 0x06D3) || c == 0x06D5
            || (c >= 0x06FA && c <= 0x06FC));
}


//
// returns true if c is a syriac letter
//
bool u_is_syriac_letter(unichar c) {
    return (c >= 0x0710 && c <= 0x072C);
}


//
// returns true if c is a thaana letter
//
bool u_is_thaana_letter(unichar c) {
    return (c >= 0x0780 && c <= 0x07A5);
}


//
// returns true if c is a devanagari letter
//
bool u_is_devanagari_letter(unichar c) {
    return ((c >= 0x0905 && c <= 0x0939) || (c >= 0x093C && c <= 0x094D)
            || (c >= 0x0950 && c <= 0x0954) || (c >= 0x0958 && c <= 0x0970));
}


//
// returns true if c is a bengali letter
//
bool u_is_bengali_letter(unichar c) {
    return (c >= 0x0985 && c <= 0x09B9 && c != 0x098D && c != 0x098E
            && c != 0x0991 && c != 0x0992 && c != 0x09B1 && c != 0x09B3
            && c != 0x09B4 && c != 0x09B5) ||
           (c >= 0x09BE && c <= 0x09CC && c != 0x09C5 && c != 0x09C6
            && c != 0x09C9 && c != 0x09CA) ||
           (c >= 0x09DC && c <= 0x09E3 && c != 0x09DE) ||
           (c == 0x09F0 || c == 0x09F1);
}


//
// returns true if c is a gurmukhi letter
//
bool u_is_gurmukhi_letter(unichar c) {
    return (c >= 0x0A05 && c <= 0x0A0A) ||
           (c == 0x0A0F || c == 0x0A10) ||
           (c >= 0x0A13 && c <= 0x0A39 && c != 0x0A29 && c != 0x0A31
            && c != 0x0A34 && c != 0x0A37) ||
           (c >= 0x0A3E && c <= 0x0A42) ||
           (c == 0x0A47 || c == 0x0A48) ||
           (c >= 0x0A4B && c <= 0x0A4D) ||
           (c >= 0x0A59 && c <= 0x0A5E && c != 0x0A5D) ||
           (c >= 0x0A70 && c <= 0x0A74);
}


//
// returns true if c is a gujarati letter
//
bool u_is_gujarati_letter(unichar c) {
    return (c >= 0x0A85 && c <= 0x0ACC && c != 0x0A8C && c != 0x0A8E
            && c != 0x0A92 && c != 0x0AA9 && c != 0x0AB1 && c != 0x0AB4
            && c != 0x0ABA && c != 0x0ABB && c != 0x0AC6 && c != 0x0ACA);
}


//
// returns true if c is an oriya letter
//
bool u_is_oriya_letter(unichar c) {
    return (c >= 0x0B05 && c <= 0x0B39 && c != 0x0B0D && c != 0x0B0E
            && c != 0x0B11 && c != 0x0B12 && c != 0x0B29 && c != 0x0B31
            && c != 0x0B34 && c != 0x0B35) ||
           (c >= 0x0B3E && c <= 0x0B43) ||
           (c == 0x0B47 || c == 0x0B48 || c == 0x0B4B || c == 0x0B4C) ||
           (c >= 0x0B5C && c <= 0x0B61 && c != 0x0B5E);
}


//
// returns true if c is a tamil letter
//
bool u_is_tamil_letter(unichar c) {
    return (c >= 0x0B85 && c <= 0x0BCC && c != 0x0B8B && c != 0x0B8C
            && c != 0x0B8D && c != 0x0B91 && c != 0x0B96 && c != 0x0B97
            && c != 0x0B98 && c != 0x0B9B && c != 0x0B9D && c != 0x0BA0
            && c != 0x0BA1 && c != 0x0BA2 && c != 0x0BA5 && c != 0x0BA6
            && c != 0x0BA7 && c != 0x0BAB && c != 0x0BAC && c != 0x0BAD
            && c != 0x0BB6 && c != 0x0BBA && c != 0x0BBB && c != 0x0BBC
            && c != 0x0BBD && c != 0x0BC3 && c != 0x0BC4 && c != 0x0BC5
            && c != 0x0BC9);
}


//
// returns true if c is a telugu letter
//
bool u_is_telugu_letter(unichar c) {
    return (c >= 0x0C05 && c <= 0x0C4C && c != 0x0C0D && c != 0x0C11
            && c != 0x0C29 && c != 0x0C34 && c != 0x0C3A && c != 0x0C3B
            && c != 0x0C3C && c != 0x0C3D && c != 0x0C45 && c != 0x0C49);
}


//
// returns true if c is a kannada letter
//
bool u_is_kannada_letter(unichar c) {
    return (c >= 0x0C85 && c <= 0x0CCC && c != 0x0C8D && c != 0x0C91
            && c != 0x0CA9 && c != 0x0CB4 && c != 0x0CBA && c != 0x0CBB
            && c != 0x0CBC && c != 0x0CBD && c != 0x0CC5 && c != 0x0CC9) ||
           (c == 0x0CDE || c == 0x0CE0 || c == 0x0CE1);
}


//
// returns true if c is a malayalam letter
//
bool u_is_malayalam_letter(unichar c) {
    return (c >= 0x0D05 && c <= 0x0D4C && c != 0x0D0D && c != 0x0D11
            && c != 0x0D29 && c != 0x0D3A && c != 0x0D3B && c != 0x0D44
            && c != 0x0D3C && c != 0x0D3D && c != 0x0D45 && c != 0x0D49) ||
           (c == 0x0D60 || c == 0x0D61);
}


//
// returns true if c is a sinhala letter
//
bool u_is_sinhala_letter(unichar c) {
    return (c >= 0x0D85 && c <= 0x0DC6 && c != 0x0D97 && c != 0x0D98
            && c != 0x0D99 && c != 0x0DB2 && c != 0x0DBC && c != 0x0DBE
            && c != 0x0DBF && c != 0x0D) ||
           (c >= 0x0DCF && c <= 0x0DDF && c != 0x0DD5 && c != 0x0DD7) ||
           (c == 0x0DF2 || c == 0x0DF3);
}


// returns true if c is a thai letter
//
bool u_is_thai_letter(unichar c) {
    return (c >= 0x0E01 && c <= 0x0E39 && c != 0x0E3F) ||
           (c >= 0x0E40 && c <= 0x0E4B);
}

// returns true if c is a greek extended letter
//
bool u_is_greek_extended_letter(unichar c) {                            //$CD:20021115
    return (c >= 0x1F00 && c <= 0x1F15) || (c >= 0x1F18 && c <= 0x1F1D) ||        //$CD:20021115
           (c >= 0x1F20 && c <= 0x1F45) || (c >= 0x1F48 && c <= 0x1F4D) ||        //$CD:20021115
           (c >= 0x1F50 && c <= 0x1F57) ||                                    //$CD:20021115
           c == 0x1F59 || c == 0x1F5B || c == 0x1F5D ||                        //$CD:20021115
           (c >= 0x1F5F && c <= 0x1F7D) || (c >= 0x1F80 && c <= 0x1FB4) ||        //$CD:20021115
           (c >= 0x1FB6 && c <= 0x1FBC) || (c >= 0x1FC2 && c <= 0x1FC4) ||        //$CD:20021115
           (c >= 0x1FC6 && c <= 0x1FCC) || (c >= 0x1FD0 && c <= 0x1FD3) ||        //$CD:20021115
           (c >= 0x1FD6 && c <= 0x1FDB) || (c >= 0x1FE0 && c <= 0x1FEC) ||        //$CD:20021115
           (c >= 0x1FF2 && c <= 0x1FF4) || (c >= 0x1FF6 && c <= 0x1FFC);        //$CD:20021115
}                                                                    //$CD:20021115


//
// returns true if c is a letter in a naive way
//
bool u_is_letter_internal(unichar c) {
    return u_is_basic_latin_letter(c)
           || u_is_latin1_supplement_letter(c)
           || u_is_latin_extendedA_letter(c)
           || u_is_latin_extendedB_letter(c)
           || u_is_IPA_extensions_letter(c)
           || u_is_greek_letter(c)
           || u_is_cyrillic_letter(c)
           || u_is_armenian_letter(c)
           || u_is_hebrew_letter(c)
           || u_is_arabic_letter(c)
           || u_is_thaana_letter(c)
           || u_is_devanagari_letter(c)
           || u_is_bengali_letter(c)
           || u_is_gurmukhi_letter(c)
           || u_is_gujarati_letter(c)
           || u_is_oriya_letter(c)
           || u_is_tamil_letter(c)
           || u_is_telugu_letter(c)
           || u_is_kannada_letter(c)
           || u_is_malayalam_letter(c)
           || u_is_sinhala_letter(c)
           || u_is_thai_letter(c)
           || u_is_greek_extended_letter(c)    //$CD:20021115
           //---------Beginning of Hyungue's inserts--------
           || u_is_korea_syllabe_letter(c)
           || u_is_CJK_Unified_Ideographs(c)
           || u_is_cjk_compatibility_ideographs(c)
//---------End of Hyungue's inserts--------
            ;
}

bool u_is_white(unichar c) {
    return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}

/**
 * Initializes the array : bit i = 1 if i is a letter, 0 otherwise.
 */
char init_unicode_table() {
    int i;
    for (i = 0; i < 8192; i++) tab_is_letter[i] = 0;
    for (i = 0; i <= 0xFFFF; i++) {
        if (u_is_letter_internal((unichar) i)) {
            tab_is_letter[i / 8] = (char) (tab_is_letter[i / 8] | (1 << (i % 8)));
        }
    }
    return 1;
}


// this line is used to initialize automatically the unicode table
char foo = (char) (init_unicode_table()/*+make_CR()*/);


/**
 * Returns a non zero value if 'c' is a letter looking up at the unicode table;
 * 0 otherwise.
 */
bool u_is_letter(unichar c) {
    return (tab_is_letter[c / 8] & (1 << (c % 8)));
}


/**
 * This function returns 1 if the given string is only made of letters.
 */
bool u_is_word(unichar *s) {
    if (s == NULL) {
        fatal_error("NULL error in is_word\n");
    }
    for (int i = 0; s[i] != '\0'; i++) {
        if (!u_is_letter(s[i])) return 0;
    }
    return 1;
}


/**
 * Reads an integer from the string 'str'. If 'next' is not NULL,
 * it will contains a pointer to the first character that follows the
 * integer.
 *
 * Author: Olivier Blanc
 */
int u_parse_int(unichar *str, unichar **next) {
    int res = 0;
    while (u_is_digit(*str)) {
        res = res * 10 + (*str - '0');
        str++;
    }
    if (next) {
        *next = str;
    }
    return res;
}

void u_fskip_line(FILE *f) {
    unichar c(u_fgetc(f));
    while (!feof(f) && c != '\n')
        c = u_fgetc(f);
}

//Javier Sastre 14/10/2011
bool u_is_float_first(unichar c) { return u_is_digit(c) || c == 'N' || c == 'n' || c == 'I' || c == 'i'; }

//Javier Sastre 14/02/2010
std::size_t u_fsize(FILE *f) {
    std::size_t current, end;
    // Store current position
    current = ftell(f);
    // Move to the end and get position
    fseek(f, 0, 2);
    end = ftell(f);
    // Restore the file pointer
    fseek(f, current, 0);
    return end - 2;
}

//Javier Sastre 14/02/2010
std::pair<unichar *, std::size_t> u_fread(const char *file_path_name) {
    FILE *f(u_fopen(file_path_name, U_READ));
    if (f == NULL)
        fatal_error("Unable to open text file to read\n");
    std::size_t input_byte_count(u_fsize(f)); //file size minus 2 bytes of Byte-Order-Mark
    std::size_t input_unichar_count = input_byte_count / 2;
    unichar *s(new unichar[input_unichar_count]);
    u_fread(s, input_unichar_count, f);
    u_fclose(f);
    return std::make_pair(s, input_unichar_count);
}

