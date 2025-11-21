/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsa <elsa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:50:57 by elsa              #+#    #+#             */
/*   Updated: 2025/11/20 20:18:44 by elsa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUFFER_SIZE 50

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int	ft_open_file(const char *file)
{
	int fd;
	
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	return (fd);
}
// the read function returns the number of characters that it has read, or -1 in case of error. return 0 when it is at the end of the file (EOF)
// size_t read(int fd, void *buf, size_t count);

int    ft_count_carac(int fd)
{
	char	buf[BUFFER_SIZE];
	size_t	nb_carac;
	int		nb_read;
	
	nb_read = -1; //count the nb of carac read
	nb_carac = 0;
	while (nb_read != 0)
	{
		nb_read = read(fd, buf, BUFFER_SIZE);
		if (nb_read == -1)
			return (0);
		nb_carac += nb_read;
	}
	return (nb_carac);
}


char	*ft_get_file(int fd, int nb_carac)
{
	//int	i;
	char	*buf;
	
	buf = malloc((nb_carac + 1) * sizeof(char));
	 read(fd, buf, nb_carac);
	//buf[i] = '\0';
	return (buf);
}

int main()
{
	int fd;
	
	fd = ft_open_file("cat.txt");
    printf("%d\n", ft_count_carac(fd));
    printf("%s\n", ft_get_file(fd, ft_count_carac(fd)));
}