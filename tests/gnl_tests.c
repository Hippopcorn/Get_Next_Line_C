/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsa <elsa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:13:29 by elsa              #+#    #+#             */
/*   Updated: 2025/11/23 22:10:24 by elsa             ###   ########.fr       */
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

void test_ft_get_next_line(void)
{
	char *fd = "chat\nchien\ncheval\nloutre";
	
	TEST_ASSERT_EQUAL_STRING ("chat\n", ft_get_next_line(fd));
	TEST_ASSERT_EQUAL_STRING ("chien\n", ft_get_next_line(fd));
	TEST_ASSERT_EQUAL_STRING ("cheval\n", ft_get_next_line(fd));
	TEST_ASSERT_EQUAL_STRING ("loutre\0", ft_get_next_line(fd));
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_ft_get_next_line);
    return UNITY_END();
}