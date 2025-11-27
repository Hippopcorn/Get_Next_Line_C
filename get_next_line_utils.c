/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsa <elsa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:50:57 by elsa              #+#    #+#             */
/*   Updated: 2025/11/27 20:38:40 by elsa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*s_cast;

	i = 0;
	s_cast = (char *)s;
	while (s_cast[i] != '\0')
	{
		if ((unsigned char)c == s_cast[i])
			return (&s_cast[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return (&s_cast[i]);
	return (NULL);
}

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


char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int				i;
	unsigned int	end;
	char			*substring;
	int				alloc;

	i = 0;
	end = start + len;
	if (start >= ft_strlen(s))
		return (NULL);
	if (end >= ft_strlen(s))
		alloc = ft_strlen(s) - start;
	else
		alloc = len;
	substring = malloc((alloc + 1 * sizeof(char)));
	if (!substring)
		return (NULL);
	while (start < end && start < ft_strlen(s))
	{
		substring[i] = s[start];
		i++;
		start++;
	}
	substring[i] = '\0';
	return (substring);
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

// Allocates memory (using malloc(3)) and returns a new string, 
// which is the result of concatenating ’s1’ and ’s2’.

char	*ft_strjoin(char const *s1, char const *s2)
{
    char *new;
    size_t len1 = ft_strlen(s1);
    size_t len2 = ft_strlen(s2);

    new = malloc(len1 + len2 + 1);
    if (!new)
        return (NULL);
    ft_memmove(new, s1, len1);
    ft_memmove(new + len1, s2, len2 + 1);
    free((char*)s1);
	free((char*)s2);
    return (new);
}



void *ft_realloc(void *ptr, size_t size) // imaginons ptr = line et size est la nouvelle taille
{ 
	void *dup; 
	size_t len; 
	if (!ptr) 
		return(malloc(size)); 
	if (size == 0) 
	{
		 free(ptr); 
		 return (NULL); 
	} 
	dup = malloc(size); 
	if (!dup)
		return (NULL); 
	len = ft_strlen((char *)ptr); //printf("len of line : %zu\n", len); 
	if (len > size - 1)
		len = size - 1; 
	ft_memmove(dup, ptr, len); 
	((char *)dup)[len] = '\0'; 
	free(ptr); 
	return (dup); 
}