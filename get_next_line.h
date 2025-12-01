/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evarache <evarache@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:50:53 by elsa              #+#    #+#             */
/*   Updated: 2025/12/01 14:14:39 by evarache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	10
# endif

# include <unistd.h>
# include <stdlib.h>

char		*get_next_line(int fd);
int			ft_strchr_index(const char *s, int c);
size_t		ft_strlen(const char *str);
char		*ft_str_realloc(char *ptr, size_t size);
void		*ft_memmove(void *dest, const void *src, size_t n);

#endif
