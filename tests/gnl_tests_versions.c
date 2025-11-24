/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_tests_versions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsa <elsa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:13:29 by elsa              #+#    #+#             */
/*   Updated: 2025/11/24 17:42:00 by elsa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity/unity.h"

#include "../get_next_line.h"
//#define BUFFER_SIZE 10


void setUp(void) {}

void tearDown(void) {}

void test_ft_GNL_file1_v1(void)
{
	int 	fd;
	
	fd = open("tests/file1.txt", O_RDONLY);
	// fd ne doit pas etre egal a -1, sinon erreur
	TEST_ASSERT_MESSAGE(fd != -1, "Test failed at the aperture");
	
	// TEST_ASSERT_EQUAL_STRING("Lady Gaga, de son vrai nom Stefani Joanne Angelina", get_next_line_v1(fd));
	// TEST_ASSERT_EQUAL_STRING(" Germanotta (nee le 28 mars 1986 a New York), est ", get_next_line_v1(fd));
	// TEST_ASSERT_EQUAL_STRING("une auteure-compositrice-interprete, productrice, ", get_next_line_v1(fd));
	// TEST_ASSERT_EQUAL_STRING("actrice et philanthrope americaine.\nG\n\n\nGaga", get_next_line_v1(fd));
	// TEST_ASSERT_NULL(get_next_line_v1(fd));

	close(fd);
}

void test_ft_GNL_file_test_v2(void)
{
	int 	fd;
	
	fd = open("tests/file_test_v2.txt", O_RDONLY);
	// fd ne doit pas etre egal a -1, sinon erreur
	TEST_ASSERT_MESSAGE(fd != -1, "Test failed at the aperture");
	
	TEST_ASSERT_EQUAL_STRING("Lady Gaga, de son vrai\n", get_next_line_v2(fd));
	TEST_ASSERT_EQUAL_STRING("a\n", get_next_line_v2(fd));

	TEST_ASSERT_NULL(get_next_line_v2(fd));
	
	close(fd);
}

void test_ft_GNL_file1_v2(void)
{
	int 	fd;
	
	fd = open("tests/file1.txt", O_RDONLY);
	// fd ne doit pas etre egal a -1, sinon erreur
	TEST_ASSERT_MESSAGE(fd != -1, "Test failed at the aperture");
	
	TEST_ASSERT_EQUAL_STRING("Lady Gaga, de son vrai nom Stefani Joanne Angelina", get_next_line_v2(fd));
	TEST_ASSERT_EQUAL_STRING(" Germanotta (nee le 28 mars 1986 a New York), est ", get_next_line_v2(fd));
	TEST_ASSERT_EQUAL_STRING("une auteure-compositrice-interprete, productrice, ", get_next_line_v2(fd));
	TEST_ASSERT_EQUAL_STRING("actrice et philanthrope americaine.\n", get_next_line_v2(fd));

	TEST_ASSERT_NULL(get_next_line_v2(fd));
	
	close(fd);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_ft_GNL_file1_v2);
    RUN_TEST(test_ft_GNL_file_test_v2);
    return UNITY_END();
}