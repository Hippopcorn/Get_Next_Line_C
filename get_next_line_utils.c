/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evarache <evarache@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:50:57 by elsa              #+#    #+#             */
/*   Updated: 2025/11/26 15:16:05 by evarache         ###   ########.fr       */
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
		return (malloc(sizeof(char)));
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
	//i++;
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
	char	*new_string;
	size_t	i;
	size_t	i_s2;
	size_t	new_len;

	i = 0;
	i_s2 = 0;
	new_len = ft_strlen(s1) + ft_strlen(s2);
	new_string = malloc(new_len + 1 * sizeof(char));
	if (!new_string)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		new_string[i] = s1[i];
		i++;
	}
	while (i < new_len)
	{
		new_string[i] = s2[i_s2];
		i++;
		i_s2++;
	}
	new_string[i + 1] = '\0';
	return (new_string);
}
