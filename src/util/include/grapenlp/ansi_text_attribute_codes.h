/*
 * GRAPENLP
 *
 * Copyright (C) 2004-2019 Javier Miguel Sastre Martínez <javier.sastre@telefonica.net>
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

#ifndef GRAPENLP_ANSI_COLORS_H
#define GRAPENLP_ANSI_COLORS_H

#ifdef UNIX

#define ANSI_DEFAULT "\033[0m"
#define ANSI_BOLD "\033[1m"
#define ANSI_FAINT "\033[2m"
#define ANSI_ITALIC "\033[3m"
#define ANSI_UNDERLINE "\033[4m"
#define ANSI_SLOW_BLINK "\033[5m"
#define ANSI_RAPID_BLINK "\033[6m"
#define ANSI_INVERSE "\033[7m"
#define ANSI_CONCEAL "\033[8m"
#define ANSI_CROSSED_OUT "\033[9m"
#define ANSI_DEFAULT_FONT "\033[10m"
#define ANSI_ALTERNATIVE_FONT_1 "\033[11m"
#define ANSI_ALTERNATIVE_FONT_2 "\033[12m"
#define ANSI_ALTERNATIVE_FONT_3 "\033[13m"
#define ANSI_ALTERNATIVE_FONT_4 "\033[14m"
#define ANSI_ALTERNATIVE_FONT_5 "\033[15m"
#define ANSI_ALTERNATIVE_FONT_6 "\033[16m"
#define ANSI_ALTERNATIVE_FONT_7 "\033[17m"
#define ANSI_ALTERNATIVE_FONT_8 "\033[18m"
#define ANSI_ALTERNATIVE_FONT_9 "\033[19m"
#define ANSI_FRAKTUR "\033[20m"

#define ANSI_BOLD_OFF "\033[21m"
#define ANSI_NORMAL_INTENSITY "\033[22m"
#define ANSI_NOT_ITALIC_OR_FRAKTUR "\033[23m"
#define ANSI_UNDERLINE_OFF "\033[24m"
#define ANSI_BLINK_OFF "\033[25m"
#define ANSI_INVERSE_OFF "\033[27m"
#define ANSI_CONCEAL_OFF "\033[28m"
#define ANSI_CROSSED_OUT_OFF "\033[29m"

#define ANSI_BLACK_FG "\033[30m"
#define ANSI_RED_FG "\033[31m"
#define ANSI_GREEN_FG "\033[32m"
#define ANSI_YELLOW_FG "\033[33m"
#define ANSI_BLUE_FG "\033[34m"
#define ANSI_MAGENTA_FG "\033[35m"
#define ANSI_CYAN_FG "\033[36m"
#define ANSI_WHITE_FG "\033[37m"
#define ANSI_BRIGHT_BLACK_FG "\033[90m"
#define ANSI_BRIGHT_RED_FG "\033[91m"
#define ANSI_BRIGHT_GREEN_FG "\033[92m"
#define ANSI_BRIGHT_YELLOW_FG "\033[93m"
#define ANSI_BRIGHT_BLUE_FG "\033[94m"
#define ANSI_BRIGHT_MAGENTA_FG "\033[95m"
#define ANSI_BRIGHT_CYAN_FG "\033[96m"
#define ANSI_BRIGHT_WHITE_FG "\033[97m"

#define ANSI_BLACK_BG "\033[40m"
#define ANSI_RED_BG "\033[41m"
#define ANSI_GREEN_BG "\033[42m"
#define ANSI_YELLOW_BG "\033[43m"
#define ANSI_BLUE_BG "\033[44m"
#define ANSI_MAGENTA_BG "\033[45m"
#define ANSI_CYAN_BG "\033[46m"
#define ANSI_WHITE_BG "\033[47m"
#define ANSI_BRIGHT_BLACK_BG "\033[100m"
#define ANSI_BRIGHT_RED_BG "\033[101m"
#define ANSI_BRIGHT_GREEN_BG "\033[102m"
#define ANSI_BRIGHT_YELLOW_BG "\033[103m"
#define ANSI_BRIGHT_BLUE_BG "\033[104m"
#define ANSI_BRIGHT_MAGENTA_BG "\033[105m"
#define ANSI_BRIGHT_CYAN_BG "\033[106m"
#define ANSI_BRIGHT_WHITE_BG "\033[107m"

#else

#define ANSI_DEFAULT ""
#define ANSI_BOLD ""
#define ANSI_FAINT ""
#define ANSI_ITALIC ""
#define ANSI_UNDERLINE ""
#define ANSI_SLOW_BLINK ""
#define ANSI_RAPID_BLINK ""
#define ANSI_INVERSE ""
#define ANSI_CONCEAL ""
#define ANSI_CROSSED_OUT ""
#define ANSI_DEFAULT_FONT ""
#define ANSI_ALTERNATIVE_FONT_1 ""
#define ANSI_ALTERNATIVE_FONT_2 ""
#define ANSI_ALTERNATIVE_FONT_3 ""
#define ANSI_ALTERNATIVE_FONT_4 ""
#define ANSI_ALTERNATIVE_FONT_5 ""
#define ANSI_ALTERNATIVE_FONT_6 ""
#define ANSI_ALTERNATIVE_FONT_7 ""
#define ANSI_ALTERNATIVE_FONT_8 ""
#define ANSI_ALTERNATIVE_FONT_9 ""
#define ANSI_FRAKTUR ""

#define ANSI_BOLD_OFF ""
#define ANSI_NORMAL_INTENSITY ""
#define ANSI_NOT_ITALIC_OR_FRAKTUR ""
#define ANSI_UNDERLINE_OFF ""
#define ANSI_BLINK_OFF ""
#define ANSI_INVERSE_OFF ""
#define ANSI_CONCEAL_OFF ""
#define ANSI_CROSSED_OUT_OFF ""

#define ANSI_BLACK_FG ""
#define ANSI_RED_FG ""
#define ANSI_GREEN_FG ""
#define ANSI_YELLOW_FG ""
#define ANSI_BLUE_FG ""
#define ANSI_CYAN_FG ""
#define ANSI_MAGENTA_FG ""
#define ANSI_WHITE_FG ""
#define ANSI_BRIGHT_BLACK_FG ""
#define ANSI_BRIGHT_RED_FG ""
#define ANSI_BRIGHT_GREEN_FG ""
#define ANSI_BRIGHT_YELLOW_FG ""
#define ANSI_BRIGHT_BLUE_FG ""
#define ANSI_BRIGHT_MAGENTA_FG ""
#define ANSI_BRIGHT_CYAN_FG ""
#define ANSI_BRIGHT_WHITE_FG ""

#define ANSI_BLACK_BG ""
#define ANSI_RED_BG ""
#define ANSI_GREEN_BG ""
#define ANSI_YELLOW_BG ""
#define ANSI_BLUE_BG ""
#define ANSI_MAGENTA_BG ""
#define ANSI_CYAN_BG ""
#define ANSI_WHITE_BG ""
#define ANSI_BRIGHT_BLACK_BG ""
#define ANSI_BRIGHT_RED_BG ""
#define ANSI_BRIGHT_GREEN_BG ""
#define ANSI_BRIGHT_YELLOW_BG ""
#define ANSI_BRIGHT_BLUE_BG ""
#define ANSI_BRIGHT_MAGENTA_BG ""
#define ANSI_BRIGHT_CYAN_BG ""
#define ANSI_BRIGHT_WHITE_BG ""

#endif

//Same but for wide chars

#ifdef UNIX

#define WANSI_DEFAULT L"\033[0m"
#define WANSI_BOLD L"\033[1m"
#define WANSI_FAINT L"\033[2m"
#define WANSI_ITALIC L"\033[3m"
#define WANSI_UNDERLINE L"\033[4m"
#define WANSI_SLOW_BLINK L"\033[5m"
#define WANSI_RAPID_BLINK L"\033[6m"
#define WANSI_INVERSE L"\033[7m"
#define WANSI_CONCEAL L"\033[8m"
#define WANSI_CROSSED_OUT L"\033[9m"
#define WANSI_DEFAULT_FONT L"\033[10m"
#define WANSI_ALTERNATIVE_FONT_1 L"\033[11m"
#define WANSI_ALTERNATIVE_FONT_2 L"\033[12m"
#define WANSI_ALTERNATIVE_FONT_3 L"\033[13m"
#define WANSI_ALTERNATIVE_FONT_4 L"\033[14m"
#define WANSI_ALTERNATIVE_FONT_5 L"\033[15m"
#define WANSI_ALTERNATIVE_FONT_6 L"\033[16m"
#define WANSI_ALTERNATIVE_FONT_7 L"\033[17m"
#define WANSI_ALTERNATIVE_FONT_8 L"\033[18m"
#define WANSI_ALTERNATIVE_FONT_9 L"\033[19m"
#define WANSI_FRAKTUR L"\033[20m"

#define WANSI_BOLD_OFF L"\033[21m"
#define WANSI_NORMAL_INTENSITY L"\033[22m"
#define WANSI_NOT_ITALIC_OR_FRAKTUR L"\033[23m"
#define WANSI_UNDERLINE_OFF L"\033[24m"
#define WANSI_BLINK_OFF L"\033[25m"
#define WANSI_INVERSE_OFF L"\033[27m"
#define WANSI_CONCEAL_OFF L"\033[28m"
#define WANSI_CROSSED_OUT_OFF L"\033[29m"

#define WANSI_BLACK_FG L"\033[30m"
#define WANSI_RED_FG L"\033[31m"
#define WANSI_GREEN_FG L"\033[32m"
#define WANSI_YELLOW_FG L"\033[33m"
#define WANSI_BLUE_FG L"\033[34m"
#define WANSI_MAGENTA_FG L"\033[35m"
#define WANSI_CYAN_FG L"\033[36m"
#define WANSI_WHITE_FG L"\033[37m"
#define WANSI_BRIGHT_BLACK_FG L"\033[90m"
#define WANSI_BRIGHT_RED_FG L"\033[91m"
#define WANSI_BRIGHT_GREEN_FG L"\033[92m"
#define WANSI_BRIGHT_YELLOW_FG L"\033[93m"
#define WANSI_BRIGHT_BLUE_FG L"\033[94m"
#define WANSI_BRIGHT_MAGENTA_FG L"\033[95m"
#define WANSI_BRIGHT_CYAN_FG L"\033[96m"
#define WANSI_BRIGHT_WHITE_FG L"\033[97m"

#define WANSI_BLACK_BG L"\033[40m"
#define WANSI_RED_BG L"\033[41m"
#define WANSI_GREEN_BG L"\033[42m"
#define WANSI_YELLOW_BG L"\033[43m"
#define WANSI_BLUE_BG L"\033[44m"
#define WANSI_MAGENTA_BG L"\033[45m"
#define WANSI_CYAN_BG L"\033[46m"
#define WANSI_WHITE_BG L"\033[47m"
#define WANSI_BRIGHT_BLACK_BG L"\033[100m"
#define WANSI_BRIGHT_RED_BG L"\033[101m"
#define WANSI_BRIGHT_GREEN_BG L"\033[102m"
#define WANSI_BRIGHT_YELLOW_BG L"\033[103m"
#define WANSI_BRIGHT_BLUE_BG L"\033[104m"
#define WANSI_BRIGHT_MAGENTA_BG L"\033[105m"
#define WANSI_BRIGHT_CYAN_BG L"\033[106m"
#define WANSI_BRIGHT_WHITE_BG L"\033[107m"

#else

#define WANSI_DEFAULT L""
#define WANSI_BOLD L""
#define WANSI_FAINT L""
#define WANSI_ITALIC L""
#define WANSI_UNDERLINE L""
#define WANSI_SLOW_BLINK L""
#define WANSI_RAPID_BLINK L""
#define WANSI_INVERSE L""
#define WANSI_CONCEAL L""
#define WANSI_CROSSED_OUT L""
#define WANSI_DEFAULT_FONT L""
#define WANSI_ALTERNATIVE_FONT_1 L""
#define WANSI_ALTERNATIVE_FONT_2 L""
#define WANSI_ALTERNATIVE_FONT_3 L""
#define WANSI_ALTERNATIVE_FONT_4 L""
#define WANSI_ALTERNATIVE_FONT_5 L""
#define WANSI_ALTERNATIVE_FONT_6 L""
#define WANSI_ALTERNATIVE_FONT_7 L""
#define WANSI_ALTERNATIVE_FONT_8 L""
#define WANSI_ALTERNATIVE_FONT_9 L""
#define WANSI_FRAKTUR L""

#define WANSI_BOLD_OFF L""
#define WANSI_NORMAL_INTENSITY L""
#define WANSI_NOT_ITALIC_OR_FRAKTUR L""
#define WANSI_UNDERLINE_OFF L""
#define WANSI_BLINK_OFF L""
#define WANSI_INVERSE_OFF L""
#define WANSI_CONCEAL_OFF L""
#define WANSI_CROSSED_OUT_OFF L""

#define WANSI_BLACK_FG L""
#define WANSI_RED_FG L""
#define WANSI_GREEN_FG L""
#define WANSI_YELLOW_FG L""
#define WANSI_BLUE_FG L""
#define WANSI_CYAN_FG L""
#define WANSI_MAGENTA_FG L""
#define WANSI_WHITE_FG L""
#define WANSI_BRIGHT_BLACK_FG L""
#define WANSI_BRIGHT_RED_FG L""
#define WANSI_BRIGHT_GREEN_FG L""
#define WANSI_BRIGHT_YELLOW_FG L""
#define WANSI_BRIGHT_BLUE_FG L""
#define WANSI_BRIGHT_MAGENTA_FG L""
#define WANSI_BRIGHT_CYAN_FG L""
#define WANSI_BRIGHT_WHITE_FG L""

#define WANSI_BLACK_BG L""
#define WANSI_RED_BG L""
#define WANSI_GREEN_BG L""
#define WANSI_YELLOW_BG L""
#define WANSI_BLUE_BG L""
#define WANSI_MAGENTA_BG L""
#define WANSI_CYAN_BG L""
#define WANSI_WHITE_BG L""
#define WANSI_BRIGHT_BLACK_BG L""
#define WANSI_BRIGHT_RED_BG L""
#define WANSI_BRIGHT_GREEN_BG L""
#define WANSI_BRIGHT_YELLOW_BG L""
#define WANSI_BRIGHT_BLUE_BG L""
#define WANSI_BRIGHT_MAGENTA_BG L""
#define WANSI_BRIGHT_CYAN_BG L""
#define WANSI_BRIGHT_WHITE_BG L""

#endif

namespace grapenlp
{
} //namespace grapenlp

#endif /*GRAPENLP_ANSI_COLORS_H*/
