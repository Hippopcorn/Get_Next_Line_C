/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evarache <evarache@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:34:30 by elsa              #+#    #+#             */
/*   Updated: 2025/12/01 16:26:17 by evarache         ###   ########.fr       */
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

static char	*ft_read_file(int fd, int *error)
{
	int		nb_read;
	char	*buf_read;

	*error = 0;
	buf_read = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf_read)
	{
		*error = 1;
		return (NULL);
	}
	nb_read = read(fd, buf_read, BUFFER_SIZE);
	if (nb_read < 0)
	{
		*error = 1;
		return (ft_free(&buf_read));
	}
	if (nb_read == 0)
		return (ft_free(&buf_read));
	buf_read[nb_read] = '\0';
	return (buf_read);
}

static char	*ft_cut_buffer(char **buf, char **line, int i_end_line, size_t len)
{
	int	rest_len;

	*line = malloc (i_end_line + 2 * sizeof(char));
	if (*line == NULL)
		return (ft_free(buf));
	ft_memmove(*line, *buf, i_end_line + 1);
	(*line)[i_end_line + 1] = '\0';
	rest_len = len - (i_end_line + 1);
	ft_memmove(*buf, *buf + i_end_line + 1, rest_len + 1);
	(*buf)[rest_len] = '\0';
	*buf = ft_str_realloc(*buf, rest_len + 1);
	if (*buf == NULL)
		ft_free(line);
	return (*line);
}

static char	*ft_fill_line(char **static_buf, char **line, int i_end_line)
{
	size_t	len_static_buf;

	len_static_buf = ft_strlen(*static_buf);
	if (i_end_line != -1)
		return (ft_cut_buffer(static_buf, line, i_end_line, len_static_buf));
	*line = malloc (len_static_buf + 1 * sizeof(char));
	if (*line == NULL)
		return (ft_free(static_buf));
	ft_memmove(*line, *static_buf, len_static_buf + 1);
	(*line)[len_static_buf] = '\0';
	ft_free(static_buf);
	return (*line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*static_buf;
	int			i_new_line;
	int			error;
	size_t		len_buf;

	i_new_line = ft_strchr_index(static_buf, '\n');
	while (i_new_line == -1)
	{
		len_buf = ft_strlen(static_buf);
		line = ft_read_file(fd, &error);
		if (line == NULL)
		{
			if (static_buf && len_buf != 0 && error == 0)
				break ;
			return (ft_free(&static_buf));
		}
		static_buf = ft_str_realloc(static_buf, len_buf + ft_strlen(line) + 1);
		if (static_buf == NULL)
			return (ft_free(&line));
		ft_memmove(static_buf + len_buf, line, ft_strlen(line) + 1);
		i_new_line = ft_strchr_index(static_buf, '\n');
		ft_free(&line);
	}
	return (ft_fill_line(&static_buf, &line, i_new_line));
}
