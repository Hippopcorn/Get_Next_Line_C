/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_example.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsa <elsa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:13:29 by elsa              #+#    #+#             */
/*   Updated: 2025/11/23 21:35:43 by elsa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity/unity.h"

#include "../get_next_line.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_ft_strchr_index(void)
{
	TEST_ASSERT_EQUAL (-1, ft_strchr_index("", '\n'));
	TEST_ASSERT_EQUAL (-1, ft_strchr_index("chat", '\n'));
	TEST_ASSERT_EQUAL (2, ft_strchr_index("ch\nat", '\n'));
	TEST_ASSERT_EQUAL (0, ft_strchr_index("\nchat", '\n'));
	TEST_ASSERT_EQUAL (4, ft_strchr_index("chat\n", '\n'));
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_ft_strchr_index);
    return UNITY_END();
}