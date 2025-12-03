
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
int main()
{
	int fd = open("tests/one_line_no_nl.txt", O_RDONLY);
	int fd2 = open("tests/file_test_v2.txt", O_RDONLY);
	int fd3 = open("tests/test.txt", O_RDONLY);
	
	char * line;

	line = get_next_line(fd);
	printf("%s", line);
	free(line);

	line = get_next_line(fd2);
	printf("%s", line);
	free(line);

	line = get_next_line(fd3);
	printf("%s", line);
	free(line);

	line = get_next_line(-1);
	printf("%s", line);
	free(line);

	line = get_next_line(fd2);
	printf("%s", line);
	free(line);
	
	line = get_next_line(fd3);
	printf("%s", line);
	free(line);

	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	
	close(fd);
	close(fd2);
	close(fd3);

	return 0;
}