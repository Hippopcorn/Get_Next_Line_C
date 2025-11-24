/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsa <elsa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:13:29 by elsa              #+#    #+#             */
/*   Updated: 2025/11/24 11:51:29 by elsa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity/unity.h"

#include "../get_next_line.h"
#define BUFFER_SIZE 1


void setUp(void) {}

void tearDown(void) {}

void test_ft_GNL_file1(void)
{
	int 	fd;
	
	fd = open("file1.txt", O_RDONLY);
	// fd ne doit pas etre egal a -1, sinon erreur
	TEST_ASSERT_MESSAGE(fd != -1, "Test failed at the aperture");
	
	// int nb_read = -1;
	// while (nb_read != 0)
	// {
	// 	nb_read = read(fd, buf, 50);
	// 	TEST_ASSERT_MESSAGE( nb_read != -1, "Test failed while reading");
	// 	buf[nb_read] = '\0';  
	// 	printf("%s\n", buf);
	// }
	
	char *line = ft_get_next_line(fd);
	TEST_ASSERT_EQUAL_STRING ("Lady Gaga, de son vrai nom Stefani Joanne Angelina Germanotta (née le 28 mars 1986 à New York), est une auteure-compositrice-interprète, productrice, actrice et philanthrope américaine.\n", line);
	free(line);
	
	line = ft_get_next_line(fd);
	TEST_ASSERT_EQUAL_STRING ("G\n", line);
	free(line);
	
	line = ft_get_next_line(fd);
	TEST_ASSERT_EQUAL_STRING ("\n", line);
	free(line);

	line = ft_get_next_line(fd);
	TEST_ASSERT_EQUAL_STRING ("\n", line);
	free(line);

	line = ft_get_next_line(fd);
	TEST_ASSERT_EQUAL_STRING ("Gaga", line);
	free(line);
	
	// cas de fin de fichier
	line = ft_get_next_line(fd);
	TEST_ASSERT_NULL (line);

	// cas d'erreurs
	TEST_ASSERT_NULL(ft_get_next_line(-1));
	TEST_ASSERT_NULL(ft_get_next_line(20000)); // fd fermé ou inexistant
	
	close(fd);
}

void test_ft_GNL_file_empty(void)
{
	int 	fd;	
	
	fd = open("file_empty.txt", O_RDONLY);
	TEST_ASSERT_MESSAGE(fd != -1, "Test failed at the aperture");  // fd ne doit pas etre egal a -1, sinon erreur
	
	char *line = ft_get_next_line(fd);
	TEST_ASSERT_NULL (line);

	// cas d'erreurs
	TEST_ASSERT_NULL(ft_get_next_line(-1));
	TEST_ASSERT_NULL(ft_get_next_line(20000)); // fd fermé ou inexistant

	
	close(fd);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_ft_GNL_file1);
    RUN_TEST(test_ft_GNL_file_empty);
    return UNITY_END();
}