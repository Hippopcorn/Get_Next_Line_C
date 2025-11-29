/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsa <elsa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:34:30 by elsa              #+#    #+#             */
/*   Updated: 2025/11/29 11:03:07 by elsa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *get_next_line(int fd)
{
	char		*line;
	static char	*static_buf;  //buf_mem
	int			i_new_line;
	int 		rest_len;

	i_new_line = ft_strchr_index(static_buf, '\n');
	while (i_new_line == -1)
	{
		//printf("WHILE\n");
		line = read_file(fd);

		if (line == NULL)
		{
			if (ft_strlen(static_buf) != 0)
				break;
			
			if (static_buf != NULL)
			{
				free (static_buf);
				static_buf = NULL;
			}
			return (NULL);
		}
		//printf("static_buf 1 :%s\n", static_buf);
		// on realloc static_buf pour qu'il puisse contenir static_buf + line
		static_buf = ft_realloc(static_buf, ft_strlen(static_buf) + ft_strlen(line) + 1);
		ft_memmove(static_buf + ft_strlen(static_buf), line, ft_strlen(line));

		i_new_line = ft_strchr_index(static_buf, '\n');
		free(line);
	}

	if (i_new_line == -1)
	{
		line = malloc (ft_strlen(static_buf) + 1 * sizeof(char));  // + 2 pour avoir la len et rajouter un \0
		
		ft_memmove(line, static_buf, ft_strlen(static_buf));
		line[ft_strlen(static_buf) + 1] = '\0';
		free (static_buf);
		static_buf = NULL;
		//return (static_buf);
	}
	//printf("i_new_line :%d\n", i_new_line);
	else 
	{
		// on a static_buf avec tout dedans, reste a decouper 
		line = malloc (i_new_line + 2 * sizeof(char));  // + 2 pour avoir la len et rajouter un \0
		ft_memmove(line, static_buf, i_new_line + 1);
		line[i_new_line + 1] = '\0';
		//printf("line :%s\n", line);
		
		rest_len = ft_strlen(static_buf) - (i_new_line + 1); // on calcule le reste a garder
		ft_memmove(static_buf, static_buf + i_new_line + 1, rest_len);  //on memmove et on realloc
		static_buf[rest_len] = '\0';
		static_buf = ft_realloc(static_buf, rest_len + 1);
	}
	
	return (line);
}

// La fonction fait ce qu'elle dit faire : Elle lit le fichier
// rien de plus, rien de moins, elle fait pas des trucs chelou en plus
// c' est une notion importante a avoir en tete ca, rien de plus rien de moins
char	*read_file(int fd)
{
    int 		nb_read; 
    char    	*buf_read;

	buf_read = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf_read)
		return (NULL);	
	nb_read = read(fd, buf_read, BUFFER_SIZE);
	if (nb_read <= 0)
	{
		free(buf_read);
		return (NULL);
	}
	buf_read[nb_read] = '\0';  
	return (buf_read);	
}


// retourne buf jusqu'a \n ou buf entier
char    *get_line_until_end(char *buf, int *i_cut)
{
	if (*i_cut == -1)
		*i_cut = ft_strlen(buf);
    //if (i_cut != -1)
    return(ft_substr(buf, 0, *i_cut + 1)); // str, i_start et len 
    //return (buf);
}

char	*error_handling(int nb_read, char *line)
{
	if (nb_read == 0)   // on a atteint la fin du fichier
		return (line);
	return (NULL);
}

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
	}
	else
	{
		i = n;
		while (i != 0)
		{
			((unsigned char *)dest)[i - 1] = ((unsigned char *)src)[i - 1];
			i--;
		}
	}
	return (dest);
}

// int main()
// {
// 	int 	fd;
// 	char	*line;
	
// 	fd = open("to_do.txt", O_RDONLY);
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

// fonctionne avec buffer size 4 a 353	