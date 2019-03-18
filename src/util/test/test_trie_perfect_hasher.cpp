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
#include <grapenlp/trie_perfect_hasher.h>

typedef grapenlp::trie_perfect_hasher<char> c_hasher;


const std::array<char, 0> epsilon = {{}};
const std::array<char, 2> hi = {{'h', 'i'}};
const std::array<char, 3> his = {{'h', 'i', 's'}};
const std::array<char, 3> her = {{'h', 'e', 'r'}};

class test_c_trie_perfect_hasher_fixture: public ::testing::Test
{
protected:
	c_hasher h;
};

TEST_F(test_c_trie_perfect_hasher_fixture, initial_hasher_maps_epsilon_to_0_and_size_is_0)
{
    ASSERT_EQ(0, h.index_of(epsilon.begin(), epsilon.end()));
	ASSERT_EQ(0, h.size());
}

TEST_F(test_c_trie_perfect_hasher_fixture, inserting_epsilon_maps_it_to_1_and_increments_size)
{
    h.insert(epsilon.begin(), epsilon.end());
    ASSERT_EQ(1, h.index_of(epsilon.begin(), epsilon.end()));
    ASSERT_EQ(1, h.size());
}

TEST_F(test_c_trie_perfect_hasher_fixture, first_inserted_string_is_indexed_to_1_and_size_incremented_to_1)
{
    h.insert(his.begin(), his.end());
    ASSERT_EQ(1, h.index_of(his.begin(), his.end()));
    ASSERT_EQ(1, h.size());
}


TEST_F(test_c_trie_perfect_hasher_fixture, inserting_twice_the_same_string_doesnt_change_the_index_or_size)
{
    h.insert(his.begin(), his.end());
    h.insert(his.begin(), his.end());
    ASSERT_EQ(1, h.index_of(his.begin(), his.end()));
    ASSERT_EQ(1, h.size());
}

TEST_F(test_c_trie_perfect_hasher_fixture, inserting_a_prefix_of_an_indexed_string_gives_it_the_next_index_and_size_is_incremented)
{
    h.insert(his.begin(), his.end());
    h.insert(hi.begin(), hi.end());
    ASSERT_EQ(2, h.index_of(hi.begin(), hi.end()));
    ASSERT_EQ(2, h.size());
}

TEST_F(test_c_trie_perfect_hasher_fixture, requesting_index_of_unindexed_string_returns_0_and_size_is_not_modified)
{
    h.insert(his.begin(), his.end());
    ASSERT_EQ(0, h.index_of(her.begin(), her.end()));
    ASSERT_EQ(1, h.size());
}

TEST_F(test_c_trie_perfect_hasher_fixture, requesting_index_of_unindexed_string_that_is_prefix_of_and_indexed_string_returns_0_and_size_is_not_modified)
{
    h.insert(his.begin(), his.end());
    ASSERT_EQ(0, h.index_of(hi.begin(), hi.end()));
    ASSERT_EQ(1, h.size());
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
