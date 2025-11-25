/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evarache <evarache@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:50:53 by elsa              #+#    #+#             */
/*   Updated: 2025/11/25 16:06:18 by evarache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUFFER_SIZE 50

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

char	*get_next_line(int fd);
char	*get_next_line_v3(int fd);
char	*ft_strchr(const char *s, int c);
int		ft_strchr_index(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char    *get_line_until_end(char *buf);
void	*ft_realloc(void *ptr, size_t size);
void	*ft_memcpy( void *dest, const void *src, size_t n);
int		count_carac(char *str, char c);
