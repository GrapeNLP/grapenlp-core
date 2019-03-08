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
#include <grapenlp/u_context.h>

const grapenlp::u_array &&k1 = grapenlp::to_u_array_without_null(L"key1");
const grapenlp::u_array &&v1 = grapenlp::to_u_array_without_null(L"value1");
const grapenlp::u_array &&k2 = grapenlp::to_u_array_without_null(L"key2");
const grapenlp::u_array &&v2 = grapenlp::to_u_array_without_null(L"value2");
const grapenlp::u_array &&k3 = grapenlp::to_u_array_without_null(L"key3");
const grapenlp::u_array &&v3 = grapenlp::to_u_array_without_null(L"value3");

typedef grapenlp::u_context::size_type size_type;
typedef grapenlp::u_context::optimized_key optimized_key;
typedef grapenlp::u_context::optimized_value optimized_value;

class test_u_context_fixture: public ::testing::Test
{
protected:
    grapenlp::u_context c;

    void SetUp()
    {
        c.set(k1.begin(), k1.end(), v1.begin(), v1.end());
        c.set(k2.begin(), k2.end(), v2.begin(), v2.end());
    }
};

TEST_F(test_u_context_fixture, equals_k1_v1)
{
    size_type s = c.size();
    ASSERT_TRUE(c.equals(k1.begin(), k1.end(), v1.begin(), v1.end()));
    ASSERT_EQ(s, c.size());
}

TEST_F(test_u_context_fixture, equals_k2_v2)
{
    size_type s = c.size();
    ASSERT_TRUE(c.equals(k2.begin(), k2.end(), v2.begin(), v2.end()));
    ASSERT_EQ(s, c.size());
}

TEST_F(test_u_context_fixture, not_equals_k1_v2)
{
    std::size_t s = c.size();
    ASSERT_TRUE(c.not_equals(k1.begin(), k1.end(), v2.begin(), v2.end()));
    ASSERT_EQ(s, c.size());
}

TEST_F(test_u_context_fixture, not_equals_k2_v1)
{
    std::size_t s = c.size();
    ASSERT_TRUE(c.not_equals(k2.begin(), k2.end(), v1.begin(), v1.end()));
    ASSERT_EQ(s, c.size());
}

TEST_F(test_u_context_fixture, not_equals_unmaped_key)
{
    std::size_t s = c.size();
    ASSERT_TRUE(c.not_equals(k3.begin(), k3.end(), v3.begin(), v3.end()));
    ASSERT_EQ(s, c.size());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
