/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsa <elsa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:34:30 by elsa              #+#    #+#             */
/*   Updated: 2025/11/28 07:39:45 by elsa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char    *get_next_line(int fd)
{
	printf("CAAAAALL\n");
    char    	*line_temp;
	char		*line;
	char		*buf_temp;
	static char	*buf_mem;
	int			i_cut;
    
	line = NULL;
	buf_temp = NULL;
	line_temp = NULL;
	if (buf_mem != NULL)
	{
		printf("IIIIIf\n");
		i_cut = ft_strchr_index(buf_mem, '\n');
		if (i_cut == -1)
			i_cut = ft_strlen(buf_mem);
		line = malloc (i_cut + 1 * sizeof(char));
		ft_memmove(line, buf_mem, i_cut + 1);
		ft_memmove(buf_mem, buf_mem + i_cut, (ft_strlen(buf_mem) + 1) - (i_cut + 1));
		buf_mem = ft_realloc(buf_mem, ft_strlen(buf_mem) + 1 - (i_cut + 1));
	}
	while (ft_strchr_index(buf_mem, '\n') == -1)
    {
		printf("WHIIIIIILE\n");
		line_temp = line;

		line = read_file(&buf_temp, line, fd);
		if (!line)
			return(NULL);
			
		buf_mem = buf_temp;
		printf("%p:%p\n", line_temp, line);
		
		if (line_temp && line_temp != line)
		{
			printf("free temp\n");
			free(line_temp);
		}
	}
    return (line);
}

char    *get_next_line_v_juju(int fd)
{
	char		*line;
	static char	*static_buf;
	int			i_new_line;
    
	// dans le cas ou buf_mem est deja allouee
	i_new_line = ft_strchr_index(static_buf, '\n');
	while (i_new_line == -1) // tant qu'on a pas de nl
    {
		line = read_file_v_juju(fd);
		if (line == NULL)
		{
			if (static_buf != NULL)
			{
				free(static_buf);	
				static_buf = NULL; // si jamais on call plusieurs fois la fonction, pour eviter de free un truc deja free
			}
			return(NULL);
		}
		if (ft_strlen(line) == 0) // si on a rien lu, ca veut pas dire qu'il n'y a plus rien a retourner!
		{
			free(line);
			break; // il faut traiter normalement static_buf
		}	

		// on realoc static_buf pour qu'il puisse pecho line
		static_buf = ft_realloc(static_buf, ft_strlen(static_buf) + ft_strlen(line) + 1);
		ft_memmove(static_buf + ft_strlen(static_buf), line, ft_strlen(line));

		i_new_line = ft_strchr_index(static_buf, '\n');
		free(line);
	}

	// on gere ce qui va etre return : uniquement tout ce qu'il y a avant (inclus) le \n
	line = malloc(sizeof(char) * i_new_line + 2);
	ft_memmove(line, static_buf, i_new_line + 1);
	line[i_new_line + 1] = '\0';

	// on la betement on rogne le static_buf pour enlever le debut
	ft_memmove(static_buf, static_buf + i_new_line + 1, ft_strlen(static_buf) - i_new_line + 1);
	static_buf = ft_realloc(static_buf, ft_strlen(static_buf) + 1);
	
    return (line);
}

// La fonction fait ce qu'elle dit faire : Elle lit le fichier
// rien de plus, rien de moins, elle fait pas des trucs chelou en plus
// c' est une notion importante a avoir en tete ca, rien de plus rien de moins
char	*read_file_v_juju(int fd)
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

char	*read_file(char **buf_temp, char *line, int fd)
{
    int 		nb_read; 
    char    	*buf_read;
	char		*current_line;
	int			i_new_line;

	buf_read = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf_read)
		return (NULL);	
	nb_read = read(fd, buf_read, BUFFER_SIZE);
	if (nb_read <= 0)
	{
		free(buf_read);
		return (error_handling(nb_read, line));	
	}
	buf_read[nb_read] = '\0';  
	
	i_new_line = ft_strchr_index(buf_read, '\n');
	current_line = get_line_until_end(buf_read, &i_new_line);
	
    *buf_temp = ft_substr(buf_read, i_new_line + 1, ft_strlen(buf_read) - (i_new_line + 1));
	
	line = ft_strjoin(line, current_line);
	free(buf_read);
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