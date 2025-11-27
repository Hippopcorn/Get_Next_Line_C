/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsa <elsa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:13:29 by elsa              #+#    #+#             */
/*   Updated: 2025/11/27 08:57:54 by elsa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity/unity.h"

#include "../get_next_line.h"
//#define BUFFER_SIZE 1


void setUp(void) {}

void tearDown(void) {}

void test_ft_GNL_file1(void)
{
	int 	fd;
	
	fd = open("tests/file1.txt", O_RDONLY);
	// fd ne doit pas etre egal a -1, sinon erreur
	TEST_ASSERT_MESSAGE(fd != -1, "Test failed at the aperture");
	
	char *line = get_next_line(fd);
	TEST_ASSERT_EQUAL_STRING ("Lady Gaga, de son vrai nom Stefani Joanne Angelina Germanotta (nee le 28 mars 1986 a New York), est une auteure-compositrice-interprete, productrice, actrice et philanthrope americaine.\n", line);
	free(line);
	
	line = get_next_line(fd);
	TEST_ASSERT_EQUAL_STRING ("G\n", line);
	free(line);
	
	line = get_next_line(fd);
	TEST_ASSERT_EQUAL_STRING ("\n", line);
	free(line);

	line = get_next_line(fd);
	TEST_ASSERT_EQUAL_STRING ("\n", line);
	free(line);

	line = get_next_line(fd);
	TEST_ASSERT_EQUAL_STRING ("Gaga\n", line);
	free(line);

	line = get_next_line(fd);
	TEST_ASSERT_EQUAL_STRING ("\n", line);
	free(line);

	line = get_next_line(fd);
	TEST_ASSERT_EQUAL_STRING ("\n", line);
	free(line);

	line = get_next_line(fd);
	TEST_ASSERT_EQUAL_STRING ("", line);
	free(line);
	
	// cas de fin de fichier
	line = get_next_line(fd);
	TEST_ASSERT_NULL (line);

	// cas d'erreurs
	TEST_ASSERT_NULL(get_next_line(-1));
	TEST_ASSERT_NULL(get_next_line(20000)); // fd fermé ou inexistant
	
	close(fd);
}

void test_ft_GNL_file_empty(void)
{
	int 	fd;	
	
	fd = open("tests/file_empty.txt", O_RDONLY);
	TEST_ASSERT_MESSAGE(fd != -1, "Test failed at the aperture");  // fd ne doit pas etre egal a -1, sinon erreur
	
	char *line = get_next_line(fd);
	TEST_ASSERT_NULL (line);

	// cas d'erreurs
	TEST_ASSERT_NULL(get_next_line(-1));
	TEST_ASSERT_NULL(get_next_line(20000)); // fd fermé ou inexistant

	close(fd);
}

int main(void) {
    UNITY_BEGIN();
	printf("BUFFER_SIZE : %d\n", BUFFER_SIZE);
    RUN_TEST(test_ft_GNL_file1);
    RUN_TEST(test_ft_GNL_file_empty);
    return UNITY_END();
}