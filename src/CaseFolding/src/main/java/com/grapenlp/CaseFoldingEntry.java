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

public class CaseFoldingEntry implements Comparable<CaseFoldingEntry>
{
    private String language = "";
    private int lowerCaseCode;
    private int upperCaseCode;
    private char caseFoldingType;
    private String graphema;
    private CharacterType charType;
    private String with = "";
    private CaseFoldingEntry canonicalForm = null;

    public CaseFoldingEntry()
    {}

    CaseFoldingEntry(CaseFoldingEntry entry)
    {
        language = entry.language;
        lowerCaseCode = entry.lowerCaseCode;
        upperCaseCode = entry.upperCaseCode;
        caseFoldingType = entry.caseFoldingType;
        graphema = entry.graphema;
        charType = entry.charType;
        with = entry.with;
        canonicalForm = entry.canonicalForm;
    }

    public String getLanguage() {
        return language;
    }

    public void setLanguage(String language) {
        this.language = language;
    }

    public int getLowerCaseCode() {
        return lowerCaseCode;
    }

    public void setLowerCaseCode(int lowerCaseCode) {
        this.lowerCaseCode = lowerCaseCode;
    }

    public int getUpperCaseCode() {
        return upperCaseCode;
    }

    public void setUpperCaseCode(int upperCaseCode) {
        this.upperCaseCode = upperCaseCode;
    }

    public char getCaseFoldingType() {
        return caseFoldingType;
    }

    public void setCaseFoldingType(char caseFoldingType) {
        this.caseFoldingType = caseFoldingType;
    }

    public String getGraphema() {
        return graphema;
    }

    public void setGraphema(String graphema) {
        this.graphema = graphema;
    }

    public CharacterType getCharType() {
        return charType;
    }

    public void setCharType(CharacterType charType) {
        this.charType = charType;
    }

    public String getWith() {
        return with;
    }

    public void setWith(String with) {
        this.with = with;
    }

    public CaseFoldingEntry getCanonicalForm() {
        return canonicalForm;
    }

    public void setCanonicalForm(CaseFoldingEntry canonicalForm) {
        this.canonicalForm = canonicalForm;
    }

    @Override
    public String toString()
    {
        return "caseFoldingType(" + caseFoldingType + ") charType(" + charType + ") graphema(" + graphema + ") with(" + with + ") uppercaseCode(" + Integer.toString(upperCaseCode,16) + ") lowercaseCode(" + Integer.toString(lowerCaseCode, 16) + ") language(" + language + ")";
    }

    @Override
    public int compareTo(CaseFoldingEntry CaseFoldingEntry)
    {
        int result = language.compareTo(CaseFoldingEntry.language);
        if (result != 0)
            return result;
        result = charType.ordinal() - CaseFoldingEntry.getCharType().ordinal();
        if (result != 0)
            return result;
        result = graphema.compareTo(CaseFoldingEntry.graphema);
        if (result != 0)
            return graphema.compareTo(CaseFoldingEntry.graphema);
        result = with.compareTo(CaseFoldingEntry.with);
        return result;
    }
}
