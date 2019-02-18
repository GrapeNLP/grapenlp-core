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

#include <gtest/gtest.h>
#include <grapenlp/context.h>

const std::array<unichar, 4> k1 = { {'k', 'e', 'y', '1'} };
const std::array<unichar, 4> k2 = { {'k', 'e', 'y', '2'} };
const std::array<unichar, 4> k3 = { {'k', 'e', 'y', '3'} };
const std::array<unichar, 6> v1 = { {'v', 'a', 'l', 'u', 'e', '1'} };
const std::array<unichar, 6> v2 = { {'v', 'a', 'l', 'u', 'e', '2'} };
const std::array<unichar, 6> v3 = { {'v', 'a', 'l', 'u', 'e', '3'} };

class test_context_fixture: public ::testing::Test
{
protected:
    grapenlp::context c;

    void SetUp()
    {
        c.set(c.get_key_const_ref(k1), c.get_value_const_ref(v1));
        c.set(c.get_key_const_ref(k2), c.get_value_const_ref(v2));
    }
};

TEST_F(test_context_fixture, equals)
{
    std::size_t s = c.size();
    grapenlp::u_trie_string_const_ref k1r = c.get_key_const_ref(k1);
    grapenlp::u_trie_string_const_ref v1r = c.get_value_const_ref(v1);
    grapenlp::u_trie_string_const_ref k2r = c.get_key_const_ref(k2);
    grapenlp::u_trie_string_const_ref v2r = c.get_value_const_ref(v2);
    ASSERT_TRUE(c.equals(k1r, v1r));
    ASSERT_TRUE(c.equals(k2r, v2r));
    ASSERT_EQ(s, c.size());
}

TEST_F(test_context_fixture, not_equals)
{
    std::size_t s = c.size();
    grapenlp::u_trie_string_const_ref k1r = c.get_key_const_ref(k1);
    grapenlp::u_trie_string_const_ref v1r = c.get_value_const_ref(v1);
    grapenlp::u_trie_string_const_ref k2r = c.get_key_const_ref(k2);
    grapenlp::u_trie_string_const_ref v2r = c.get_value_const_ref(v2);
    grapenlp::u_trie_string_const_ref k3r = c.get_key_const_ref(k3);
    grapenlp::u_trie_string_const_ref v3r = c.get_value_const_ref(v3);
    ASSERT_TRUE(c.not_equals(k1r, v2r));
    ASSERT_TRUE(c.not_equals(k2r, v1r));
    ASSERT_TRUE(c.not_equals(k3r, v3r));
    ASSERT_EQ(s, c.size());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
