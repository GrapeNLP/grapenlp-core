/*
 * GRAPENLP
 *
 * Copyright (C) 2004-2021 Javier Miguel Sastre Martínez <javier.sastre@gmail.com>
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

#include <gtest/gtest.h>
#include <iostream>
#include <grapenlp/ansi_text_attribute_codes.h>

void print_fg(const char* special_attrib_code, const char* special_attrib_name, const char* bg_color_code, const char* bg_color_name)
{
	std::cout << special_attrib_code << bg_color_code << ANSI_BLACK_FG << special_attrib_name << " black foreground in " << bg_color_name << " background" << ANSI_DEFAULT << std::endl;
	std::cout << special_attrib_code << bg_color_code << ANSI_RED_FG << special_attrib_name << " red foreground in " << bg_color_name << " background" << ANSI_DEFAULT << std::endl;
	std::cout << special_attrib_code << bg_color_code << ANSI_GREEN_FG << special_attrib_name << " green foreground in " << bg_color_name << " background" << ANSI_DEFAULT << std::endl;
	std::cout << special_attrib_code << bg_color_code << ANSI_YELLOW_FG << special_attrib_name << " yellow foreground in " << bg_color_name << " background" << ANSI_DEFAULT << std::endl;
	std::cout << special_attrib_code << bg_color_code << ANSI_BLUE_FG << special_attrib_name << " blue foreground in " << bg_color_name << " background" << ANSI_DEFAULT << std::endl;
	std::cout << special_attrib_code << bg_color_code << ANSI_MAGENTA_FG << special_attrib_name << " magenta foreground in " << bg_color_name << " background" << ANSI_DEFAULT << std::endl;
	std::cout << special_attrib_code << bg_color_code << ANSI_CYAN_FG << special_attrib_name << " cyan foreground in " << bg_color_name << " background" << ANSI_DEFAULT << std::endl;
	std::cout << special_attrib_code << bg_color_code << ANSI_WHITE_FG << special_attrib_name << " white foreground in " << bg_color_name << " background" << ANSI_DEFAULT << std::endl;

	std::cout << special_attrib_code << bg_color_code << ANSI_BRIGHT_BLACK_FG << special_attrib_name << " bright black foreground in " << bg_color_name << " background" << ANSI_DEFAULT << std::endl;
	std::cout << special_attrib_code << bg_color_code << ANSI_BRIGHT_RED_FG << special_attrib_name << " bright red foreground in " << bg_color_name << " background" << ANSI_DEFAULT << std::endl;
	std::cout << special_attrib_code << bg_color_code << ANSI_BRIGHT_GREEN_FG << special_attrib_name << " bright green foreground in " << bg_color_name << " background" << ANSI_DEFAULT << std::endl;
	std::cout << special_attrib_code << bg_color_code << ANSI_BRIGHT_YELLOW_FG << special_attrib_name << " bright yellow foreground in " << bg_color_name << " background" << ANSI_DEFAULT << std::endl;
	std::cout << special_attrib_code << bg_color_code << ANSI_BRIGHT_BLUE_FG << special_attrib_name << " bright blue foreground in " << bg_color_name << " background" << ANSI_DEFAULT << std::endl;
	std::cout << special_attrib_code << bg_color_code << ANSI_BRIGHT_MAGENTA_FG << special_attrib_name << " bright magenta foreground in " << bg_color_name << " background" << ANSI_DEFAULT << std::endl;
	std::cout << special_attrib_code << bg_color_code << ANSI_BRIGHT_CYAN_FG << special_attrib_name << " bright cyan foreground in " << bg_color_name << " background" << ANSI_DEFAULT << std::endl;
	std::cout << special_attrib_code << bg_color_code << ANSI_BRIGHT_WHITE_FG << special_attrib_name << " bright white foreground in " << bg_color_name << " background" << ANSI_DEFAULT << std::endl;
}

void print_fg_x_bg(const char* special_attrib_code, const char* special_attrib_name)
{
	print_fg(special_attrib_code, special_attrib_name, ANSI_BLACK_BG, "black");
	print_fg(special_attrib_code, special_attrib_name, ANSI_RED_BG, "red");
	print_fg(special_attrib_code, special_attrib_name, ANSI_GREEN_BG, "green");
	print_fg(special_attrib_code, special_attrib_name, ANSI_YELLOW_BG, "yellow");
	print_fg(special_attrib_code, special_attrib_name, ANSI_BLUE_BG, "blue");
	print_fg(special_attrib_code, special_attrib_name, ANSI_MAGENTA_BG, "magenta");
	print_fg(special_attrib_code, special_attrib_name, ANSI_CYAN_BG, "cyan");
	print_fg(special_attrib_code, special_attrib_name, ANSI_WHITE_BG, "white");

	print_fg(special_attrib_code, special_attrib_name, ANSI_BRIGHT_BLACK_BG, "bright black");
	print_fg(special_attrib_code, special_attrib_name, ANSI_BRIGHT_RED_BG, "bright red");
	print_fg(special_attrib_code, special_attrib_name, ANSI_BRIGHT_GREEN_BG, "bright green");
	print_fg(special_attrib_code, special_attrib_name, ANSI_BRIGHT_YELLOW_BG, "bright yellow");
	print_fg(special_attrib_code, special_attrib_name, ANSI_BRIGHT_BLUE_BG, "bright blue");
	print_fg(special_attrib_code, special_attrib_name, ANSI_BRIGHT_MAGENTA_BG, "bright magenta");
	print_fg(special_attrib_code, special_attrib_name, ANSI_BRIGHT_CYAN_BG, "bright cyan");
	print_fg(special_attrib_code, special_attrib_name, ANSI_BRIGHT_WHITE_BG, "bright white");
}

void print_fg_x_bg_x_special()
{
	print_fg_x_bg(ANSI_DEFAULT, "default");
	print_fg_x_bg(ANSI_BOLD, "bold");
	print_fg_x_bg(ANSI_FAINT, "faint");
	print_fg_x_bg(ANSI_ITALIC, "italic");
	print_fg_x_bg(ANSI_UNDERLINE, "underline");
	print_fg_x_bg(ANSI_SLOW_BLINK, "slow blink");
	print_fg_x_bg(ANSI_RAPID_BLINK, "rapid blink");
	print_fg_x_bg(ANSI_INVERSE, "inverse");
	print_fg_x_bg(ANSI_CONCEAL, "conceal");
	print_fg_x_bg(ANSI_CROSSED_OUT, "crossed out");
	print_fg_x_bg(ANSI_DEFAULT_FONT, "default font");
	print_fg_x_bg(ANSI_ALTERNATIVE_FONT_1, "alternative font 1");
	print_fg_x_bg(ANSI_ALTERNATIVE_FONT_2, "alternative font 2");
	print_fg_x_bg(ANSI_ALTERNATIVE_FONT_3, "alternative font 3");
	print_fg_x_bg(ANSI_ALTERNATIVE_FONT_4, "alternative font 4");
	print_fg_x_bg(ANSI_ALTERNATIVE_FONT_5, "alternative font 5");
	print_fg_x_bg(ANSI_ALTERNATIVE_FONT_6, "alternative font 6");
	print_fg_x_bg(ANSI_ALTERNATIVE_FONT_7, "alternative font 7");
	print_fg_x_bg(ANSI_ALTERNATIVE_FONT_8, "alternative font 8");
	print_fg_x_bg(ANSI_ALTERNATIVE_FONT_9, "alternative font 9");
	print_fg_x_bg(ANSI_FRAKTUR, "fraktur");
	print_fg_x_bg(ANSI_BOLD_OFF, "bold off");
	print_fg_x_bg(ANSI_NORMAL_INTENSITY, "normal intensity");
	print_fg_x_bg(ANSI_NOT_ITALIC_OR_FRAKTUR, "not italic or fraktur");
	print_fg_x_bg(ANSI_UNDERLINE_OFF, "underline off");
	print_fg_x_bg(ANSI_BLINK_OFF, "blink off");
	print_fg_x_bg(ANSI_INVERSE_OFF, "inverse off");
	print_fg_x_bg(ANSI_CONCEAL_OFF, "conceal off");
	print_fg_x_bg(ANSI_CROSSED_OUT_OFF, "crossed out off");
}

/** This test simply prints text formatted with ANSI codes to the terminal;
 * one is to manually see if the terminal properly formats them or not,
 * that is, the characters are printed using the corresponding foreground
 * and background colors and other special effects such as blinking,
 * underlining, etc. **/

TEST(ansi_text_attribute_test, terminal_interprets_ansi_formatting_characters)
{
	print_fg_x_bg_x_special();
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
