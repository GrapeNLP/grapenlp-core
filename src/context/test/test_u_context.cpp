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

const std::array<unichar, 4> k1 = {{'k', 'e', 'y', '1'}};
const std::array<unichar, 4> k2 = {{'k', 'e', 'y', '2'}};
const std::array<unichar, 4> k3 = {{'k', 'e', 'y', '3'}};
const std::array<unichar, 6> v1 = {{'v', 'a', 'l', 'u', 'e', '1'}};
const std::array<unichar, 6> v2 = {{'v', 'a', 'l', 'u', 'e', '2'}};
const std::array<unichar, 6> v3 = {{'v', 'a', 'l', 'u', 'e', '3'}};

typedef grapenlp::u_context::hash_type hash_type;

class test_u_context_fixture: public ::testing::Test
{
protected:
    grapenlp::u_context_key_value_hasher h;
    std::unique_ptr<grapenlp::u_context> c_ref;

    void SetUp()
    {
        h.key_hasher.insert(k1.begin(), k1.end());
        h.key_hasher.insert(k2.begin(), k2.end());
        h.value_hasher.insert(v1.begin(), v1.end());
        h.value_hasher.insert(v2.begin(), v2.end());
        
        c_ref.reset(new grapenlp::u_context(h));
        c_ref->set(k1.begin(), k1.end(), v1.begin(), v1.end());
        c_ref->set(k2.begin(), k2.end(), v2.begin(), v2.end());
    }
};

TEST_F(test_u_context_fixture, equals_k1_v1)
{
    ASSERT_TRUE(c_ref->equals(k1.begin(), k1.end(), v1.begin(), v1.end()));
}

TEST_F(test_u_context_fixture, equals_k2_v2)
{
    ASSERT_TRUE(c_ref->equals(k2.begin(), k2.end(), v2.begin(), v2.end()));
}

TEST_F(test_u_context_fixture, not_equals_k1_v2)
{
    ASSERT_TRUE(c_ref->not_equals(k1.begin(), k1.end(), v2.begin(), v2.end()));
}

TEST_F(test_u_context_fixture, not_equals_k2_v1)
{
    ASSERT_TRUE(c_ref->not_equals(k2.begin(), k2.end(), v1.begin(), v1.end()));
}

TEST_F(test_u_context_fixture, not_equals_unmaped_key)
{
    ASSERT_TRUE(c_ref->not_equals(k3.begin(), k3.end(), v3.begin(), v3.end()));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
