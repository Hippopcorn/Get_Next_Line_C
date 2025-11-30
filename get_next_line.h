/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsa <elsa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:50:53 by elsa              #+#    #+#             */
/*   Updated: 2025/11/30 18:49:34 by elsa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char	*get_next_line(int fd);
char    *get_next_line_v_juju(int fd);
char	*ft_strchr(const char *s, int c);
int		ft_strchr_index(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char    *get_line_until_end(char *buf, int *i_cut);
char	*ft_strjoin(char const *s1, char const *s2);
char	*error_handling(int nb_read, char *line);
char	*read_file(int fd, int *error);
char	*read_file_v_juju(int fd);
char    *ft_str_realloc(char *ptr, size_t size);
void	*ft_memmove(void *dest, const void *src, size_t n);

#endif
