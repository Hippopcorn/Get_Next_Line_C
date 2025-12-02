/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evarache <evarache@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:34:30 by elsa              #+#    #+#             */
/*   Updated: 2025/12/02 12:05:26 by evarache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free(char **buf)
{
	if (*buf != NULL)
	{
		free(*buf);
		*buf = NULL;
	}
	return (NULL);
}

void	ft_read_file(int fd, char *buf_read, int *error)
{
	int		nb_read;

	*error = 0;

	nb_read = read(fd, buf_read, BUFFER_SIZE);
	if (nb_read < 0)
	{
		*error = 1;
		return ;
	}
	buf_read[nb_read] = '\0';
}

static char	*ft_cut_buffer(char *buf, char **line, int i_end_line)
{
	int		rest_len;
	char	*temp;
	
	rest_len = ft_strlen(*line) - (i_end_line + 1);
	
	
	temp = malloc((ft_strlen(*line) + 1) * sizeof(char));
	ft_memmove(temp, *line, (ft_strlen(*line) + 1));
	free(*line);
	
	
	*line = malloc ((i_end_line + 2) * sizeof(char));
	if (*line == NULL)
		return (NULL);
	ft_memmove(*line, temp, i_end_line + 1);
	(*line)[i_end_line + 1] = '\0';
	
	ft_memmove(buf, temp + i_end_line + 1, rest_len + 1);
	buf[rest_len] = '\0';
	free(temp);
	return (*line);
}


char	*get_next_line(int fd)
{
	char		*line;
	static char	static_buf[BUFFER_SIZE + 1];
	int			i_new_line;
	int			error;

	static_buf[BUFFER_SIZE] = '\0';
	if (ft_strlen(static_buf) != 0)  // on recupere static_buf et on le met au debut de line et on vide le static_buf
	{
		//line = ft_strjoin(static_buf, line);
		line = malloc((ft_strlen(static_buf) + 1) * sizeof(char));
		if (!line)
			return (NULL);
		ft_memmove(line, static_buf, (ft_strlen(static_buf) + 1)); 
		ft_bzero(static_buf, ft_strlen(static_buf));
		static_buf[0] = '\0';
	}
	else
		line = NULL;
	i_new_line = ft_strchr_index(line, '\n');  // on regarde si on a un \n
	while (i_new_line == -1)   // tant qu'on a pas de \n, on lit dans static_buff
	{
		ft_read_file(fd, static_buf, &error);  // je lis dans mon static_buf
		if (ft_strlen(static_buf) == 0)       // si je n'ai rien lu
		{
			if (line && ft_strlen(line) != 0 && error == 0)   // si j'ai quelque chose dans ma ligne, je sors du while
				break ;                                  
			return (ft_free(&line));           // si je n'ai rien dans ma ligne, je retourne NULL
		}

		line = ft_strjoin(line, static_buf);            // je rajoute le buffer lu à la suite de ma ligne
		i_new_line = ft_strchr_index(line, '\n');    // je recherche un \n
	}
	if (i_new_line != -1)
		return (ft_cut_buffer(static_buf, &line, i_new_line));
	return (line);
}

#include <fcntl.h>

// int	main()
// {
// 	int 	fd;
	
// 	fd = open("tests/one_big_line.txt", O_RDONLY);
	
// 	char *line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
	
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);

// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);

// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);

// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);

// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// }