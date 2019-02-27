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
#include <grapenlp/ua_context.h>

const grapenlp::u_array &&k1 = grapenlp::to_u_array_without_null(L"key1");
const grapenlp::u_array &&v1 = grapenlp::to_u_array_without_null(L"value1");
const grapenlp::u_array &&k2 = grapenlp::to_u_array_without_null(L"key2");
const grapenlp::u_array &&v2 = grapenlp::to_u_array_without_null(L"value2");
const grapenlp::u_array &&k3 = grapenlp::to_u_array_without_null(L"key3");
const grapenlp::u_array &&v3 = grapenlp::to_u_array_without_null(L"value3");

typedef grapenlp::ua_context::size_type size_type;
typedef grapenlp::ua_context::optimized_key optimized_key;
typedef grapenlp::ua_context::optimized_value optimized_value;

class test_ua_context_fixture: public ::testing::Test
{
protected:
    grapenlp::ua_context c;

    void SetUp()
    {
        c.set(c.get_optimized_key(k1.begin(), k1.end()), c.get_optimized_value(v1.begin(), v1.end()));
        c.set(c.get_optimized_key(k2.begin(), k2.end()), c.get_optimized_value(v2.begin(), v2.end()));
    }
};

TEST_F(test_ua_context_fixture, equals)
{
    size_type s = c.size();
    optimized_key ok1 = c.get_optimized_key(k1.begin(), k1.end());
    optimized_value ov1 = c.get_optimized_value(v1.begin(), v1.end());
    optimized_key ok2 = c.get_optimized_key(k2.begin(), k2.end());
    optimized_value ov2 = c.get_optimized_value(v2.begin(), v2.end());
    ASSERT_TRUE(c.equals(ok1, ov1));
    ASSERT_TRUE(c.equals(ok2, ov2));
    ASSERT_EQ(s, c.size());
}

TEST_F(test_ua_context_fixture, not_equals)
{
    std::size_t s = c.size();
    optimized_key ok1 = c.get_optimized_key(k1.begin(), k1.end());
    optimized_value ov1 = c.get_optimized_value(v1.begin(), v1.end());
    optimized_key ok2 = c.get_optimized_key(k2.begin(), k2.end());
    optimized_value ov2 = c.get_optimized_value(v2.begin(), v2.end());
    optimized_key ok3 = c.get_optimized_key(k3.begin(), k3.end());
    optimized_value ov3 = c.get_optimized_value(v3.begin(), v3.end());
    ASSERT_TRUE(c.not_equals(ok1, ov2));
    ASSERT_TRUE(c.not_equals(ok2, ov1));
    ASSERT_TRUE(c.not_equals(ok3, ov3));
    ASSERT_EQ(s, c.size());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
