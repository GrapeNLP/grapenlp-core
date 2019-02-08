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
 */

package com.grapenlp;

import java.io.File;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.net.URL;
import java.net.URLDecoder;
import java.util.TreeSet;

public class CaseFoldingTableHeadersGenerator implements WriterConstants
{
    private CaseFoldingParser caseFoldingParser;
    private UppercaseTableHeaderWriter uppercaseTableHeaderWriter;
    private LowercaseTableHeaderWriter lowercaseTableHeaderWriter;
    private ToUppercaseTableHeaderWriter toUppercaseTableHeaderWriter;
    private ToLowercaseTableHeaderWriter toLowercaseTableHeaderWriter;

    public CaseFoldingTableHeadersGenerator()
    {
        caseFoldingParser = new CaseFoldingParser();
        uppercaseTableHeaderWriter = new UppercaseTableHeaderWriter();
        lowercaseTableHeaderWriter = new LowercaseTableHeaderWriter();
        toUppercaseTableHeaderWriter = new ToUppercaseTableHeaderWriter();
        toLowercaseTableHeaderWriter = new ToLowercaseTableHeaderWriter();
    }

    private String getExecutingClassPathName()
    {
        URL url = CaseFoldingTableHeadersGenerator.class.getProtectionDomain().getCodeSource().getLocation();
        String pathName = null;
        try
        {
            pathName = URLDecoder.decode(url.getPath(), "UTF-8");
            pathName = pathName + CaseFoldingTableHeadersGenerator.class.getPackage().getName().replace('.', '/');
        }
        //Should not throw since UTF-8 is a supported encoding
        catch (UnsupportedEncodingException e)
        {
            e.printStackTrace();
        }
        return pathName;
    }

    public void generate(File folder, boolean verbose) throws UnknownCharacterTypeException, IOException, DuplicatedEntryException, NotACanonicalEntryException, CharacterCanonicalEntryNotFoundException, NotACorrespondingCanonicalEntryException
    {
        File caseFoldingResourceFile = new File(getExecutingClassPathName(), "CaseFolding.txt");
        TreeSet<CaseFoldingEntry> entries = caseFoldingParser.parse(caseFoldingResourceFile);

        File uppercaseTableHeaderFile = new File(folder, uppercaseTableHeaderFileName);
        File lowercaseTableHeaderFile = new File(folder, lowercaseTableHeaderFileName);
        File toUppercaseTableHeaderFile = new File(folder, toUppercaseTableHeaderFileName);
        File toLowercaseTableHeaderFile = new File(folder, toLowercaseTableHeaderFileName);

        uppercaseTableHeaderWriter.write(entries, uppercaseTableHeaderFile, verbose);
        lowercaseTableHeaderWriter.write(entries, lowercaseTableHeaderFile, verbose);
        toUppercaseTableHeaderWriter.write(entries, toUppercaseTableHeaderFile, verbose);
        toLowercaseTableHeaderWriter.write(entries, toLowercaseTableHeaderFile, verbose);
    }
}
