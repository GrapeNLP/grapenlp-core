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

#ifndef UnicodeH
#define UnicodeH

#include <cstdarg>
#include <cstdlib>
#include <cstring>

#include <boost/lexical_cast.hpp>

#include <grapenlp/unichar.h>
#include <grapenlp/file.h>
#include <grapenlp/error.h>
#include <grapenlp/functional.h>
#include <grapenlp/u_uppercase_table.h>
#include <grapenlp/u_lowercase_table.h>
#include <grapenlp/u_touppercase_table.h>
#include <grapenlp/u_tolowercase_table.h>

/* This line is used to prevent people from using printf and scanf. We do
 * that because we want to parametrize I/O operations with encodings. */
#define printf DONT_USE_PRINTF_BUT_U_PRINTF
#define scanf DONT_USE_SCANF_BUT_U_SCANF


/**
 * This library provides basic I/O unicode operations. For internal data
 * representations, UTF16-LE is used. It is also the default encoding for
 * reading and writing text files. UTF8 is the default encoding for writing
 * to the standard and error outputs.
 */


/**
 * These are the binary open modes for unicode text files.
 */
#define U_READ "rb"
#define U_WRITE "wb"
#define U_APPEND "ab"
#define U_MODIFY "r+b"


/* This caracter is used as the first one of a unicode text file... */
#define U_BYTE_ORDER_MARK 0xFEFF

/* ...and this one is used by contrast with 0xFEFF to determine the byte order */
#define U_NOT_A_CHAR 0xFFFE

/* Markers to indicate if a text file is a UTF16 one or not. */
#define FILE_DOES_NOT_EXIST 0
#define NOT_A_UTF16_FILE 1
#define UTF16_LITTLE_ENDIAN_FILE 2
#define UTF16_BIG_ENDIAN_FILE 3


/**
 * This is the type of a unicode character. Note that it is a 16-bits type,
 * so that it cannot handle characters >= 0xFFFF. Such characters, theoretically
 * represented with low and high surrowgate characters are not handled by Unitex.
 */
//typedef unsigned short unichar;

/**
 * We define here the unicode NULL character and the unicode
 * empty string.
 */
extern unichar U_ENDL;
extern unichar U_NULL;
extern unichar* U_EMPTY;


/* This constant must be used instead of 65536 (0x10000) in order
 * to avoid problems if one day the type unichar becomes larger
 * than 2 bytes */
#define MAX_NUMBER_OF_UNICODE_CHARS (1<<sizeof(unichar)*8)


/**
 * We define here the I/O encodings that are supported by the Unicode library.
 */
typedef enum {
   UTF16_LE,
   UTF16_BE,
   UTF8
} Encoding;

/**
 * Here are defined the default encodings.
 */
extern Encoding STDIN_ENC8;
extern Encoding STDOUT_ENC;
extern Encoding STDERR_ENC;
extern Encoding FILE_ENC;


/* ------------------- Some aliases, mainly for default UTF16-LE use ------------------- */
FILE* u_fopen(const char*,const char*);
int u_fempty(const char*);

int u_fgetc_raw(FILE*);
int u_fgetc_UTF16LE(FILE*);
int u_fgetc_UTF16BE(FILE*);
int u_fgetc_UTF8(FILE*);
int u_fgetc(FILE*);
int u_fgetc_CR(FILE*);
int u_fread_raw(unichar*,int,FILE*);
int u_fread(unichar*,int,FILE*);

int u_fputc_raw(unichar,FILE*);
int u_fputc_UTF16LE(unichar,FILE*);
int u_fputc_UTF16BE(unichar,FILE*);
int u_fputc_UTF8(unichar,FILE*);
int u_fputc(unichar,FILE*);
int u_ungetc(unichar,FILE*);

int u_fwrite_raw(const unichar*,int,FILE*);
int u_fwrite(const unichar*,int,FILE*);

int u_fgets(unichar*,FILE*);
int u_fgets(unichar*,int,FILE*);
int u_fgets2(unichar*,FILE*);

int u_printf(const char*,...);
template<typename UCharIterator>
int u_printf(UCharIterator begin, UCharIterator end);
int u_fprintf(FILE*,const char*,...);

int u_scanf(const char*,...);
int u_fscanf(FILE*,const char*,...);

/* The u_prints and u_fprints functions should not be visible from the
 * outside of this library. People should use u_printf and u_fprintf */
//void u_prints(unichar*);
//void u_fprints(unichar*,FILE*);
//void u_fprints(const char*,FILE*);
//void u_fprints(Encoding,unichar*,FILE*);
//void u_fprints(Encoding,const char*,FILE*);

/* ------------------- File functions ------------------- */
FILE* u_fopen(Encoding,const char*,const char*);
int u_fclose(FILE*);
int u_fempty(Encoding,const char*);
bool u_is_UTF16(const char*);

int u_fgetc_UTF16LE_raw(FILE*);
int u_fgetc_UTF16BE_raw(FILE*);
int u_fgetc_UTF8_raw(FILE*);
int u_fgetc_raw(Encoding,FILE*);
int u_fgetc(Encoding,FILE*);
int u_fgetc_CR(Encoding,FILE*);

int u_fread_raw(Encoding,unichar*,int,FILE*);
int u_fread(Encoding,unichar*,int,FILE*);

int u_fputc_UTF16LE_raw(unichar,FILE*);
int u_fputc_UTF16BE_raw(unichar,FILE*);
int u_fputc_UTF8_raw(unichar,FILE*);
int u_fputc_raw(Encoding,unichar,FILE*);
int u_fputc(Encoding,unichar,FILE*);

int u_ungetc_UTF16LE_raw(unichar,FILE*);
int u_ungetc_UTF16BE_raw(unichar,FILE*);
int u_ungetc_UTF8_raw(unichar,FILE*);
int u_ungetc_raw(Encoding,unichar,FILE*);
int u_ungetc(Encoding,unichar,FILE*);

int u_fwrite_raw(Encoding, const unichar*,int,FILE*);
int u_fwrite(Encoding, const unichar*,int,FILE*);

int u_fgets(Encoding,unichar*,FILE*);
int u_fgets(Encoding,unichar*,int,FILE*);
int u_fgets2(Encoding encoding,unichar* line,FILE* f);

int u_fprintf(Encoding,FILE*,const char*,...);
int u_vfprintf(Encoding,FILE*,const char*,va_list);
int u_sprintf(unichar*,const char*,...);
int u_vsprintf(unichar*,const char*,va_list);

int u_fscanf(Encoding,FILE*,const char*,...);
int u_vfscanf(Encoding,FILE*,const char*,va_list);
int u_sscanf(unichar*,const char*,...);
int u_vsscanf(unichar*,const char*,va_list);

/* ------------------- String functions ------------------- */
int u_strlen(const unichar*);
unichar* u_strcpy(unichar*,const unichar*);
unichar* u_strcpy(unichar*,const char*);
unichar* u_strcat(unichar*,unichar*);
unichar* u_strcat(unichar*,char*);
int u_strcmp(const unichar*, const unichar*);
int u_strcmp(const unichar*,const char*);
unichar* u_strdup(const unichar*);
unichar* u_strdup(const unichar*,int);
unichar* u_strdup(const char*);
unichar* u_strchr(const unichar*,unichar,int);
unichar* u_strchr(const unichar*,unichar);
char* u_strchr(char*,unichar);
unichar* u_strpbrk(const unichar*,unichar*);
unichar* u_strpbrk(const unichar*,char*);
unichar* u_strtrim(const unichar*);
unichar *u_non_white_begin(unichar *s, std::size_t start);
const unichar *u_non_white_begin(const unichar *s, std::size_t start);
unichar *u_non_white_begin(unichar *begin, unichar *end);
const unichar *u_non_white_begin(const unichar *begin, const unichar *end);
unichar *u_non_white_end(unichar *s, std::size_t start);
const unichar *u_non_white_end(const unichar *s, std::size_t start);
unichar *u_non_white_end(unichar *begin, unichar *end);
const unichar *u_non_white_end(const unichar *begin, const unichar *end);


void u_to_char(char*,unichar*);
int htmlize(unichar*,unichar*);
int mirror(unichar*,unichar*);
int mirror(unichar*);
int get_longuest_prefix(unichar*,unichar*);
unsigned int hash_unichar(unichar*);


/* ------------------- Character functions ------------------- */
bool u_is_eol(unichar c);
bool u_is_digit(unichar);
bool u_is_basic_latin_letter(unichar);
bool u_is_latin1_supplement_letter(unichar);
bool u_is_latin_extendedA_letter(unichar);
bool u_is_latin_extendedB_letter(unichar);
bool u_is_IPA_extensions_letter(unichar);
bool u_is_greek_letter(unichar);
bool u_is_cyrillic_letter(unichar);
bool u_is_armenian_letter(unichar);
bool u_is_hebrew_letter(unichar);
bool u_is_arabic_letter(unichar);
bool u_is_thaana_letter(unichar);
bool u_is_devanagari_letter(unichar);
bool u_is_bengali_letter(unichar);
bool u_is_gurmukhi_letter(unichar);
bool u_is_gujarati_letter(unichar);
bool u_is_oriya_letter(unichar);
bool u_is_tamil_letter(unichar);
bool u_is_telugu_letter(unichar);
bool u_is_kannada_letter(unichar);
bool u_is_malayalam_letter(unichar);
bool u_is_sinhala_letter(unichar);
bool u_is_thai_letter(unichar);
bool u_is_greek_extended_letter(unichar);	//$CD:20021115
//--------Beginning of Hyungue's inserts------------------
bool u_is_korea_syllabe_letter(unichar c);
bool u_is_CJK_Unified_Ideographs(unichar c);
bool u_is_cjk_compatibility_ideographs(unichar c);
bool u_is_Hangul_Compatility_Jamo(unichar c);
bool u_is_Hangul_Jamo(unichar c);
//--------End of Hyungue's inserts----------------
bool u_is_letter(unichar);
bool u_is_white(unichar);
bool u_is_word(unichar*);

int u_parse_int(unichar * str, unichar ** next = NULL);

// Sebastian Nagel's function objects
struct u_toupper: public std::unary_function<unichar, unichar>
{
	unichar operator() (const unichar c) const
	{ return grapenlp::u_touppercase_table[c]; }
};

struct u_tolower: public std::unary_function<unichar, unichar>
{
	unichar operator() (const unichar c) const
	{ return grapenlp::u_tolowercase_table[c]; }
};
// end of Sebastian Nagel's function objects

// Javier Sastre's funtions, last change at 14/10/2011
bool u_is_float_first(unichar c);

struct u_identity: public grapenlp::identity<unichar>
{
	unichar operator() (const unichar c) const
	{ return c; }
};

//File size - 2 bytes of Bit-Order-Mark
std::size_t u_fsize(FILE *f);

std::pair<unichar*, std::size_t> u_fread(const char *file_path_name);

//std::size_t to unichar iterator
//The correspondent container must have space enough to hold all the size_t digits
//starting from the passed unichar iterator
template<typename UnicharIterator>
inline UnicharIterator itoui(std::size_t ui, UnicharIterator uit)
{
	if (ui >= 10)
		uit = itoui(ui/10, uit);
	*uit = ui%10 + '0';
	++uit;
	return uit;
}

template<typename IntType>
unichar u_fread_optional_int(FILE *f, IntType &n, IntType default_value = 0)
{
	unichar c(u_fgetc(f));
	if (feof(f))
	{
		n = default_value;
		return c;
	}
	IntType sign(1);
	if (c == '-')
	{
		sign = -1;
		c = fgetc(f);
	}
	else if (c == '+')
		c = fgetc(f);
	else if (!u_is_digit(c))
	{
		n = default_value;
		return c;
	}
	n = 0;
	do
	{
		n = n * ((IntType)10) + ((IntType)c) - ((IntType)'0');
		c = u_fgetc(f);
	}while (!feof(f) && u_is_digit(c));
	n *= sign;
	return c;
}

template<typename IntType>
unichar u_fread_int(FILE *f, IntType &n)
{
	unichar c(u_fgetc(f));
	if (feof(f))
		fatal_error("Unexpected EOF while reading integer\n");
	n = 0;
	IntType sign(1);
	if (c == '-')
	{
		sign = -1;
		c = u_fgetc(f);
	}
	else if (c == '+')
		c = u_fgetc(f);
	else if (!u_is_digit(c))
		fatal_error("Unexpected char while reading integer: %c\n", c);
	do
	{
		n = n * ((IntType)10) + ((IntType)c) - ((IntType)'0');
		c = u_fgetc(f);
	}while (!feof(f) && u_is_digit(c));
	n *= sign;
	return c;
}

template<typename IntType>
unichar u_fread_optional_unsigned_int(FILE *f, IntType &n, IntType default_value = 0)
{
	unichar c(u_fgetc(f));
	if (feof(f) || !u_is_digit(c))
	{
		n = default_value;
		return c;
	}
	n = 0;
	do
	{
		n = n * ((IntType)10) + ((IntType)c) - ((IntType)'0');
		c = u_fgetc(f);
	}while (!feof(f) && u_is_digit(c));
	return c;
}

template<typename IntType>
unichar u_fread_unsigned_int(FILE *f, IntType &n)
{
	unichar c(u_fgetc(f));
	if (feof(f))
		fatal_error("Unexpected EOF while reading unsigned integer\n");
	n = 0;
	if (!u_is_digit(c))
		fatal_error("Unexpected char while reading unsigned integer: %c\n", c);
	do
	{
		n = n * ((IntType)10) + ((IntType)c) - ((IntType)'0');
		c = u_fgetc(f);
	}while (!feof(f) && u_is_digit(c));
	return c;
}

template<typename FloatType>
unichar u_fread_float(FILE *f, FloatType &n, unichar c)
{
	std::string s;
	//Read sign
	if (c == '-' || c == '+')
	{
		s += static_cast<char>(c);
		c = u_fgetc(f);
	}
	//Catch special case "Not a Number"
	if ((c == 'n' || c == 'N'))
	{
		c = u_fgetc(f);
		if (c != 'a' && c != 'A')
			fatal_error("Expected 'a' or 'A' while reading \"Not a Number\" but got %c", c);
		c = u_fgetc(f);
		if (c != 'n' && c != 'N')
			fatal_error("Expected 'n' or 'N' while reading \"Not a Number\" but got %c", c);
		if (s == "-")
			n = -std::numeric_limits<FloatType>::quiet_NaN();
		else n = std::numeric_limits<FloatType>::quiet_NaN();
		return u_fgetc(f);
	}
	//Catch special case "Infinity"
	if ((c == 'i' || c == 'I'))
	{
		c = u_fgetc(f);
		if (c != 'n' && c != 'N')
			fatal_error("Expected 'n' or 'N' while reading \"Infinity\" but got %c", c);
		c = u_fgetc(f);
		if (c != 'f' && c != 'F')
			fatal_error("Expected 'f' or 'F' while reading \"Infinity\" but got %c", c);
		if (s == "-")
			n = -std::numeric_limits<FloatType>::infinity();
		else n = std::numeric_limits<FloatType>::infinity();
		return u_fgetc(f);
	}
	//Read mantissa's integer part
	while (!feof(f) && u_is_digit(c))
	{
		s += static_cast<char>(c);
		c = u_fgetc(f);
	}
	//Read mantissa's decimal part
	if (!feof(f) && c == '.')
	{
		//Add dot
		s += static_cast<char>(c);
		c = u_fgetc(f);
		//Read decimal digits
		while (!feof(f) && u_is_digit(c))
		{
			s += static_cast<char>(c);
			c = u_fgetc(f);
		}
	}
	//Read exponent
	if (!feof(f) && (c == 'E' || c == 'e'))
	{
		s += static_cast<char>(c);
		c = u_fgetc(f);
		//Read sign
		if (c == '-' || c == '+')
		{
			s += static_cast<char>(c);
			c = u_fgetc(f);
		}
		//Read digits
		while (!feof(f) && u_is_digit(c))
		{
			s += static_cast<char>(c);
			c = u_fgetc(f);
		}
	}
	n = boost::lexical_cast<FloatType>(s);
	return c;
}

template<typename FloatType>
unichar u_fread_float(FILE *f, FloatType &n)
{ return u_fread_float(f, n, u_fgetc(f)); }

//Reads chars from file f until reaching End-Of-Line or End-Of-File
//Function feof(f) can be used to check if EOF was reached (otherwise it EOL was reached)
void u_fskip_line(FILE *f);

//Write a range of unichars
template<typename UCharIterator>
inline void u_write(FILE *f, UCharIterator begin, UCharIterator end)
{
	for (; begin != end; ++begin)
		u_fputc(*begin, f);
}

//Write a range of ranges of unichars (e.g.: an array of unicode strings)
template<typename UStringIterator>
inline void u_write(FILE *f, UStringIterator begin, UStringIterator end, const unichar separator)
{
	if (begin == end)
		return;
	u_write(f, begin->begin(), begin->end());
	++begin;
	for (; begin != end; ++begin)
	{
		u_fputc(separator, f);
		u_write(f, begin->begin(), begin->end());
	}
}

//Write a range of pointers to a ranges of unichars (e.g.: a set of pointers to unicode strings)
template<typename UPtrStringIterator>
inline void u_ptr_write(FILE *f, UPtrStringIterator begin, UPtrStringIterator end, const unichar separator)
{
	if (begin == end)
		return;
	u_write(f, (*begin)->begin(), (*end)->end());
	++begin;
	for (; begin != end; ++begin)
	{
		u_fputc(separator, f);
		u_write(f, (*begin)->begin(), (*end)->end());
	}
}

inline bool u_is_upper(unichar c)
{ return grapenlp::uppercase_table[c]; }

inline bool u_is_lower(unichar c)
{ return grapenlp::lowercase_table[c]; }

// End of Javier Sastre's functions
#endif /*GRAPENLP_UNICODE_H*/
