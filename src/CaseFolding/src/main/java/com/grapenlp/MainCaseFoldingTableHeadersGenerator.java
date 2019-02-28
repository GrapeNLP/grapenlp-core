/*
 * GRAPENLP
 *
 * Copyright (C) 2004-2008 Université de Marne-la-Vallée <javier.sastre@univ-mlv.fr>
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

/*
 *  @author Javier Sastre
 *
 * This program generates C++ header files containing look-up tables for case evaluation and conversion of UTF-16LE
 * characters inside the basic multilingual map (BMP), that is, the Unicode characters with code points ranging from 0
 * to 65536. Thus, each table contains 65536 entries, one per code point in the BMP, where the value stored at position
 * i is the mapped value of codepoint i. The generated tables are:
 * - u_lowercase_table.h: maps code points to bits indicating whether the code point is a lowercase letter or not
 * - u_lowercase_table.h: maps code points to bits indicating whether the code point is an uppercase letter or not
 * - u_tolowercase_table.h: maps code points to the corresponding lowercase code point without diacritics
 * - u_touppercase_table.h: maps code points to the corresponding uppercase code point without diacritics
 * Note the code point to code point maps are not only to be used for case folding but for removing diacritics in a
 * single look-up. Since users do not usually type diacritics when typewriting, not care about uppercase use, we use
 * these tables to normalize letters prior to comparing them (analogous to Java function equalsIgnoreCase but also
 * ignoring diacritics).
 */

package com.grapenlp;

import java.io.File;
import java.io.IOException;

public class MainCaseFoldingTableHeadersGenerator
{
    public static void main(String[] args) throws NotACanonicalEntryException, UnknownCharacterTypeException, DuplicatedEntryException, IOException, NotACorrespondingCanonicalEntryException, CharacterCanonicalEntryNotFoundException {
        if (args.length > 2)
        {
            System.out.println("Expected arguments:");
            System.out.println("1) Folder where to write the C++ case conversion headers (defaults to current directory");
            System.out.println("2) Verbose (true or false, defaults to false)");
            System.exit(1);
        }
        String folder = ".";
        if (args.length > 0)
            folder = args[0];

        boolean verbose = false;
        if (args.length > 1)
            verbose = args[1].equalsIgnoreCase("true");

        CaseFoldingTableHeadersGenerator generator = new CaseFoldingTableHeadersGenerator();
        generator.generate(new File(folder), verbose);
    }
}
