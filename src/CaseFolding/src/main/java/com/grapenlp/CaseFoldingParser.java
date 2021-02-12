/*
 * GRAPENLP
 *
 * Copyright (C) 2004-2021 Javier Miguel Sastre Martínez <javier.sastre@univ-mlv.fr>
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
 */

package com.grapenlp;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.TreeSet;

public class CaseFoldingParser {
    private int lineCount;

    static boolean isHexaChar(char c) {
        return (c >= '0' && c <= '9') || (c >= 'a') && (c <= 'f') || (c >= 'A') && (c <= 'F');
    }

    private String getNextLine(BufferedReader input) throws IOException {
        String line;
        do {
            line = input.readLine();
            ++lineCount;
        }
        while (line != null && ((line = line.trim()).length() == 0 || line.charAt(0) == '#'));
        return line;
    }

    private CaseFoldingEntry parseEntry(String line) throws UnknownCharacterTypeException {
        CaseFoldingEntry entry = new CaseFoldingEntry();

        int begin = 0;
        int end = 0;
        while (isHexaChar(line.charAt(end))) ++end;
        entry.setUpperCaseCode(Integer.parseInt(line.substring(begin, end), 16));
        begin = end + 2;
        entry.setCaseFoldingType(line.charAt(begin));
        if (entry.getCaseFoldingType() == 'F' || entry.getCaseFoldingType() == 'T')
            return entry;
        begin += 3;
        end = begin;
        while (isHexaChar(line.charAt(end))) ++end;
        entry.setLowerCaseCode(Integer.parseInt(line.substring(begin, end), 16));
        begin = line.indexOf('#', end) + 2;

        if ((end = line.indexOf("LETTER", begin)) >= 0) {
            entry.setCharType(CharacterType.LETTER);
            int langEnd = line.indexOf(' ', begin);
            while (langEnd < line.length() && !(
                    line.startsWith("LETTER", langEnd + 1) ||
                            line.startsWith("CAPITAL", langEnd + 1) ||
                            line.startsWith("SMALL", langEnd + 1)))
                langEnd = line.indexOf(' ', langEnd + 1);
            entry.setLanguage(line.substring(begin, langEnd));
            begin = end + 7;
        } else if ((end = line.indexOf("SYMBOL", begin)) >= 0) {
            int last = end - 1;
            entry.setCharType(CharacterType.SYMBOL);
            end = line.indexOf(' ', begin);
            entry.setLanguage(line.substring(begin, end));
            begin = end + 1;
            entry.setGraphema(line.substring(begin, last));
            return entry;
        } else if ((end = line.indexOf("LIGATURE", begin)) >= 0) {
            entry.setCharType(CharacterType.LIGATURE);
            entry.setLanguage(line.substring(begin, line.indexOf(' ', begin)));
            begin = end + 9;
        } else if ((end = line.indexOf("NUMERAL", begin)) >= 0) {
            entry.setCharType(CharacterType.NUMERAL);
            entry.setLanguage(line.substring(begin, end));
            begin = end + 8;
        } else if ((end = line.indexOf("SIGN", begin)) >= 0) {
            entry.setCharType(CharacterType.SIGN);
            entry.setGraphema(line.substring(begin, end - 1));
            return entry;
        } else if ((end = line.indexOf("COMBINING", begin)) >= 0) {
            entry.setCharType(CharacterType.COMBINING);
            begin = end + 10;
            end = line.indexOf(' ', begin);
            entry.setLanguage(line.substring(begin, end));
            begin = end + 1;
            entry.setGraphema(line.substring(begin));
        } else throw new UnknownCharacterTypeException(lineCount);

        end = line.indexOf(" WITH", begin);
        if (end >= 0) {
            entry.setGraphema(line.substring(begin, end));
            entry.setWith(line.substring(end + 6));
        } else entry.setGraphema(line.substring(begin));

        return entry;
    }

    private boolean caseFoldingEntryIsCanonical(CaseFoldingEntry entry) {
        String with = entry.getWith();
        return !(with.equals("GRAVE") ||
                with.equals("ACUTE") ||
                with.equals("CIRCUMFLEX") ||
                with.equals("TILDE") ||
                with.equals("DIAERESIS") ||
                with.equals("RING ABOVE") ||
                with.equals("CEDILLA"));
    }

    public void setCanonicalForms(TreeSet<CaseFoldingEntry> entries) throws CharacterCanonicalEntryNotFoundException, NotACorrespondingCanonicalEntryException, NotACanonicalEntryException {
        CaseFoldingEntry canonizedEntry, canonicalEntry;
        for (CaseFoldingEntry entry : entries) {
            if (caseFoldingEntryIsCanonical(entry))
                entry.setCanonicalForm(entry);
            else {
                canonizedEntry = new CaseFoldingEntry(entry);
                canonizedEntry.setWith("");
                canonicalEntry = entries.floor(canonizedEntry);
                if (canonicalEntry == null)
                    throw new CharacterCanonicalEntryNotFoundException(entry);
                if (!canonizedEntry.getGraphema().equals(canonicalEntry.getGraphema()) || !canonizedEntry.getLanguage().equals(canonicalEntry.getLanguage()) || canonizedEntry.getCharType() != canonicalEntry.getCharType())
                    throw new NotACorrespondingCanonicalEntryException(entry, canonicalEntry);
                if (!canonicalEntry.getWith().isEmpty())
                    throw new NotACanonicalEntryException(entry, canonicalEntry);
                entry.setCanonicalForm(canonicalEntry);
            }
        }
    }

    public TreeSet<CaseFoldingEntry> parse(File caseFoldingFile) throws IOException, UnknownCharacterTypeException, DuplicatedEntryException, NotACanonicalEntryException, CharacterCanonicalEntryNotFoundException, NotACorrespondingCanonicalEntryException {
        lineCount = 0;
        TreeSet<CaseFoldingEntry> entries = new TreeSet<CaseFoldingEntry>();
        try (BufferedReader input = new BufferedReader(new InputStreamReader(new FileInputStream(caseFoldingFile), StandardCharsets.UTF_8))) {
            String line;
            while ((line = getNextLine(input)) != null) {
                CaseFoldingEntry entry = parseEntry(line);
                if (entry.getCaseFoldingType() == 'F' || entry.getCaseFoldingType() == 'T' || entry.getLowerCaseCode() > 0xFFFF || entry.getUpperCaseCode() > 0xFFFF)
                    continue;
                if (!entries.add(entry))
                    throw new DuplicatedEntryException(lineCount, line, entry);
            }
        }
        setCanonicalForms(entries);
        return entries;
    }
}
