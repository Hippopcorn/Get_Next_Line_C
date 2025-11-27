/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsa <elsa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:34:30 by elsa              #+#    #+#             */
/*   Updated: 2025/11/27 21:07:05 by elsa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char    *get_next_line(int fd)
{
    char    	*line_temp;
	char		*line;
	static char	*buf_mem;
	int			i_cut;
	//char		*line_read;
    
	line = NULL;
	if (buf_mem != NULL)
	{
		i_cut = ft_strchr_index(buf_mem, '\n');
		if (i_cut == -1)
			i_cut = ft_strlen(buf_mem);
		line = malloc (i_cut + 1 * sizeof(char));
		ft_memmove(line, buf_mem, i_cut + 1);
		ft_memmove(buf_mem, buf_mem + i_cut, (ft_strlen(buf_mem) + 1) - (i_cut + 1));
		buf_mem = ft_realloc(buf_mem, ft_strlen(buf_mem) + 1 - (i_cut + 1));
	}
	while (ft_strchr_index(line, '\n') == -1)
    {
		line_temp = line;  // 
		line = read_file(&buf_mem, line, fd);
		if (line == NULL || line_temp == line)
			return (line);
	}
    return (line);
}

char	*read_file(char **buf_mem, char *line, int fd)
{
    int 		nb_read; 
    char    	*buf;
	char		*current_line;
	int			i_cut;

	nb_read = -1;
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);	
	nb_read = read(fd, buf, BUFFER_SIZE);
	if (nb_read == 0 || nb_read == -1)  //  a voir 
	{
		free(buf);
		return (error_handling(nb_read, buf_mem, line));	
	}
	buf[nb_read] = '\0';  
	
	i_cut = ft_strchr_index(buf, '\n');
	current_line = get_line_until_end(buf, &i_cut);
	
	free(*buf_mem);
    *buf_mem = ft_substr(buf, i_cut + 1, ft_strlen(buf) - (i_cut + 1));
	
	line = ft_strjoin(line, current_line);
	free(buf);
	return (line);
	
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

char	*error_handling(int nb_read, char **buf_mem, char *line)
{
	if (*buf_mem != NULL)
		free(*buf_mem);
	if (nb_read == 0)   // on a atteint la fin du fichier
	{
		*buf_mem = NULL;
		return (line);
	}
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