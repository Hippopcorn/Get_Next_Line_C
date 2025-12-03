/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evarache <evarache@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:50:53 by elsa              #+#    #+#             */
/*   Updated: 2025/12/03 10:41:16 by evarache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	10
# endif

# include <unistd.h>
# include <stdlib.h>

char		*get_next_line(int fd);
int			ft_strchr_index(const char *s, int c);
size_t		ft_strlen(const char *str);
void		*ft_memmove(void *dest, const void *src, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_free(char **buf);

#endif
