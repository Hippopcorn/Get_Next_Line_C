/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsa <elsa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:50:57 by elsa              #+#    #+#             */
/*   Updated: 2025/11/30 18:38:04 by elsa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


int	ft_strchr_index(const char *s, int c)
{
	int		i;
	char	*s_cast;

	i = 0;
	if (!s)
		return (-1);
	s_cast = (char *)s;
	while (s_cast[i] != '\0')
	{
		if ((unsigned char)c == s_cast[i])
			return (i);
		i++;
	}
	return (-1);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char *ft_str_realloc(char *ptr, size_t size)
{
    char *dup; 
    size_t len; 
    
    if (!ptr)
    {
        dup = malloc(size);
        if (!dup)
            return (NULL);
		dup[0] = '\0';
        return (dup);
    }
    if (size == 0) 
    {
        free(ptr); 
        return (NULL); 
    } 
    dup = malloc(size); 
    if (!dup)
        return (NULL); 
    len = ft_strlen((char *)ptr);
    if (len >= size)
        len = size - 1;
    ft_memmove(dup, ptr, len);
    ((char *)dup)[len] = '\0';
    free(ptr); 
    return (dup); 
}
