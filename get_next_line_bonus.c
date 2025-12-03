/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evarache <evarache@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:34:30 by elsa              #+#    #+#             */
/*   Updated: 2025/12/03 16:44:28 by evarache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n > 0)
	{
		*p = 0;
		p++;
		n--;
	}
}

static char	*get_static_buf(char *static_buf)
{
	char	*line;

	line = malloc((ft_strlen(static_buf) + 1) * sizeof(char));
	if (!line)
	{
		ft_bzero(static_buf, ft_strlen(static_buf));
		return (NULL);
	}
	ft_memmove(line, static_buf, (ft_strlen(static_buf) + 1));
	ft_bzero(static_buf, ft_strlen(static_buf));
	return (line);
}

static void	ft_read_file(int fd, char *buf_read, int *error)
{
	int		nb_read;

	*error = 0;
	nb_read = read(fd, buf_read, BUFFER_SIZE);
	if (nb_read < 0)
	{
		*error = 1;
		return ;
	}
	if (nb_read == 0)
		*error = 2;
	buf_read[nb_read] = '\0';
}

static char	*ft_cut_buffer(char *buf, char **line)
{
	int		rest_len;
	char	*temp;
	int		i_end_line;

	i_end_line = ft_strchr_index(*line, '\n');
	if (i_end_line == -1)
		return (*line);
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
	static char	static_buf[1024][BUFFER_SIZE + 1];
	int			error;

	if (fd < 0 || fd > 1024)
		return (NULL);
	line = NULL;
	if (ft_strlen(static_buf[fd]) != 0)
	{
		line = get_static_buf(static_buf[fd]);
		if (!line)
			return (NULL);
	}
	while (ft_strchr_index(line, '\n') == -1)
	{
		ft_read_file(fd, static_buf[fd], &error);
		if (error == 1)
			return (ft_free(&line));
		else if (error == 2)
			break ;
		line = ft_strjoin(line, static_buf[fd]);
		if (!line)
			return (ft_free(&line));
	}
	return (ft_cut_buffer(static_buf[fd], &line));
}
