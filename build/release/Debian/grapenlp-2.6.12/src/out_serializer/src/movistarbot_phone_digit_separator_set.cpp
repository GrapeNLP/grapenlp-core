#include <grapenlp/movistarbot_phone_digit_separator_set.h>

namespace grapenlp
{
	movistarbot_phone_digit_separator_set::movistarbot_phone_digit_separator_set(): base_type()
	{
		base_type::add('.');
		base_type::add('-');
		base_type::add('(');
		base_type::add(')');
	}
} //namespace grapenlp
