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

#include <memory>

#include <gtest/gtest.h>
#include <grapenlp/u_context_mask_factory.h>

template<std::size_t L, std::size_t M, std::size_t N>
void exercise_make_u_context_mask(const wchar_t (&key)[L], const wchar_t (&value)[M], const wchar_t (&expression)[N])
{
    const grapenlp::u_array &&ua_key = grapenlp::to_u_array_without_null(key);
    const grapenlp::u_array &&ua_value = grapenlp::to_u_array_without_null(value);
    const grapenlp::u_array &&ua_expression = grapenlp::to_u_array_without_null(expression);
    grapenlp::u_context_key_value_hasher hasher;
    hasher.key_hasher.insert(ua_key.begin(), ua_key.end());
    hasher.value_hasher.insert(ua_value.begin(), ua_value.end());
    grapenlp::u_context ctx(hasher);
#ifdef TRACE
    grapenlp::u_context_mask expected(hasher.key_hasher.index_of(ua_key.begin(), ua_key.end()), hasher.value_hasher.index_of(ua_value.begin(), ua_value.end()), ua_key.begin(), ua_key.end(), ua_value.begin(), ua_value.end());
#else
    grapenlp::u_context_mask expected(hasher.key_hasher.index_of(ua_key.begin(), ua_key.end()), hasher.value_hasher.index_of(ua_value.begin(), ua_value.end()));
#endif
    std::unique_ptr<grapenlp::u_context_mask> actual_p(make_u_context_mask(ua_expression.begin(), ua_expression.end(), hasher));
    ASSERT_EQ(expected, *actual_p);
}

TEST(test_u_make_context_mask_factory, keqv)
{
    exercise_make_u_context_mask(L"k", L"v", L"k=v");
}

TEST(test_u_make_context_mask_factory, _k_eq_v_)
{
    exercise_make_u_context_mask(L"k", L"v", L" k = v ");
}

TEST(test_u_make_context_mask_factory, __k__eq__v__)
{
    exercise_make_u_context_mask(L"k", L"v", L"  k  =  v  ");
}

TEST(test_u_make_context_mask_factory, keyeqvalue)
{
    exercise_make_u_context_mask(L"key", L"value", L"key=value");
}

TEST(test_u_make_context_mask_factory, key1eqvalue1)
{
    exercise_make_u_context_mask(L"key1", L"value1", L"key1=value1");
}

TEST(test_u_make_context_mask_factory, key_1eqvalue_1)
{
    exercise_make_u_context_mask(L"key_1", L"value_1", L"key_1=value_1");
}

TEST(test_u_make_context_mask_factory, _key_1_eq_value_1_)
{
    exercise_make_u_context_mask(L"key_1", L"value_1", L" key_1 = value_1 ");
}

TEST(test_u_make_context_mask_factory, __key_1__eq__value_1__)
{
    exercise_make_u_context_mask(L"key_1", L"value_1", L"  key_1  =  value_1  ");
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
