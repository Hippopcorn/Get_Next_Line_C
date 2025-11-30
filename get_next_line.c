/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsa <elsa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:34:30 by elsa              #+#    #+#             */
/*   Updated: 2025/11/30 21:00:00 by elsa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *get_next_line(int fd)
{
	char		*line;
	static char	*static_buf;
	int			i_new_line;
	int 		rest_len;
	int			error;
	
	i_new_line = ft_strchr_index(static_buf, '\n');	
	while (i_new_line == -1)
	{
		line = read_file(fd, &error);
		if (line == NULL)
		{
			if (ft_strlen(static_buf) != 0)
			{
				if (error == 1)
				{
					free (static_buf);
					static_buf = NULL;
					return (NULL);
				}
				break;
			}
			
			if (static_buf != NULL)
			{
				free (static_buf);
				static_buf = NULL;
			}
			return (NULL);
		}

		static_buf = ft_str_realloc(static_buf, ft_strlen(static_buf) + ft_strlen(line) + 1);
		if (static_buf == NULL)
			return (NULL);
		
		ft_memmove(static_buf + ft_strlen(static_buf), line, ft_strlen(line) + 1);

		i_new_line = ft_strchr_index(static_buf, '\n');
		
		free(line);
	}
	if (i_new_line == -1) // gere si pas de \n dans la derniere ligne
	{
		line = malloc (ft_strlen(static_buf) + 1 * sizeof(char));  // + 2 pour avoir la len et rajouter un \0
		
		ft_memmove(line, static_buf, ft_strlen(static_buf) +1);
		line[ft_strlen(static_buf)] = '\0';
		free (static_buf);
		static_buf = NULL;
		return (line);
	}
	
	// on a static_buf avec tout dedans, reste a decouper 
	line = malloc (i_new_line + 2 * sizeof(char));  // + 2 pour avoir la len et rajouter un \0
	ft_memmove(line, static_buf, i_new_line + 1);
	line[i_new_line + 1] = '\0';
	
	rest_len = ft_strlen(static_buf) - (i_new_line + 1); // on calcule le reste a garder
	ft_memmove(static_buf, static_buf + i_new_line + 1, rest_len + 1);  //on memmove et on realloc
	static_buf[rest_len] = '\0';
	static_buf = ft_str_realloc(static_buf, rest_len + 1);
	if (static_buf == NULL)
		return (NULL);
	
	return (line);
}

// La fonction fait ce qu'elle dit faire : Elle lit le fichier
// rien de plus, rien de moins, elle fait pas des trucs chelou en plus
// c' est une notion importante a avoir en tete ca, rien de plus rien de moins
char	*read_file(int fd, int *error)
{
    int 		nb_read; 
    char    	*buf_read;

	*error = 0;
	buf_read = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf_read)
		return (NULL);	
	nb_read = read(fd, buf_read, BUFFER_SIZE);
	if (nb_read < 0) // error
	{
		*error = 1;
		free(buf_read);
		return (NULL);
	}
	if (nb_read == 0)
	{
		free(buf_read);
		return (NULL);
	}
	buf_read[nb_read] = '\0';  
	return (buf_read);	
}



// char	*error_handling(int nb_read, char *line)
// {
// 	if (nb_read == 0)   // on a atteint la fin du fichier
// 		return (line);
// 	return (NULL);
// }

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest < src)
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
		return (dest);
	}
	i = n;
	while (i != 0)
	{
		((unsigned char *)dest)[i - 1] = ((unsigned char *)src)[i - 1];
		i--;
	}
	return (dest);
}

// int main()
// {
// 	int 	fd;
// 	char	*line;
	
// 	fd = open("tests/files/pb.txt", O_RDONLY);
// 	printf("BUFFER_SIZE : %d\n", BUFFER_SIZE);
	
// 	line =  get_next_line(fd);
// 	printf("Result GNL : %s", line);
// 	free (line);

// 	line =  get_next_line(fd);
// 	printf("Result GNL : %s", line);
// 	free (line);

// 	line =  get_next_line(fd);
// 	printf("Result GNL : %s", line);
// 	free (line);

// 	line =  get_next_line(fd);
// 	printf("Result GNL : %s", line);
// 	free (line);

// 	line =  get_next_line(fd);
// 	printf("Result GNL : %s", line);
// 	free (line);

// 	line =  get_next_line(fd);
// 	printf("Result GNL : %s", line);
// 	free (line);

// 	line =  get_next_line(fd);
// 	printf("Result GNL : %s", line);
// 	free (line);

// 	line =  get_next_line(fd);
// 	printf("Result GNL : %s", line);
// 	free (line);

// }
