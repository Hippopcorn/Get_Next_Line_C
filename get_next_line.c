/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evarache <evarache@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:34:30 by elsa              #+#    #+#             */
/*   Updated: 2025/12/02 13:39:16 by evarache         ###   ########.fr       */
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
	if (!temp)
		return (ft_free(line));
	ft_memmove(temp, *line, (ft_strlen(*line) + 1));
	free(*line);
	
	*line = malloc ((i_end_line + 2) * sizeof(char));
	if (*line == NULL)
		return (ft_free(&temp));
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

	if (ft_strlen(static_buf) != 0)
	{
		line = malloc((ft_strlen(static_buf) + 1) * sizeof(char));
		if (!line)
			return (NULL);
		ft_memmove(line, static_buf, (ft_strlen(static_buf) + 1)); 
		ft_bzero(static_buf, ft_strlen(static_buf));
	}
	else
		line = NULL;
	i_new_line = ft_strchr_index(line, '\n');
	while (i_new_line == -1)
	{
		ft_read_file(fd, static_buf, &error);
		if (ft_strlen(static_buf) == 0)
		{
			if (line && error == 0)
				break ;                                  
			return (ft_free(&line));
		}

		line = ft_strjoin(line, static_buf);
		if (!line)
		{
			static_buf[0] = '\0';
			return (ft_free(&line));
		}
		i_new_line = ft_strchr_index(line, '\n');
	}
	if (i_new_line != -1)
		return (ft_cut_buffer(static_buf, &line, i_new_line));
	return (line);
}
