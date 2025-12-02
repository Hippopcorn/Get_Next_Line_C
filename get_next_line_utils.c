/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evarache <evarache@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:50:57 by elsa              #+#    #+#             */
/*   Updated: 2025/12/02 12:24:58 by evarache         ###   ########.fr       */
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

	if (!str)
		return (0);
	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_str_realloc(char *ptr, size_t size)
{
	char	*dup;
	size_t	len;

	if (!ptr || size == 0)
	{
		dup = malloc(size);
		if (!dup)
			return (NULL);
		dup[0] = '\0';
		return (dup);
	}
	dup = malloc(size);
	if (!dup)
	{
		free(ptr);
		return (NULL);
	}
	len = ft_strlen((char *)ptr);
	ft_memmove(dup, ptr, len + 1);
	free(ptr);
	return (dup);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (dest);
	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest < src)
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
		return (dest);
	}
	i = n;
	while (i != 0)
	{
		((unsigned char *)dest)[i - 1] = ((unsigned char *)src)[i - 1];
		i--;
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_string;
	size_t	i;
	size_t	i_s2;
	size_t	new_len;
	size_t	len_s1;

	i = 0;
	i_s2 = 0;
	len_s1 = ft_strlen(s1);
	new_len = len_s1 + ft_strlen(s2);
	new_string = malloc(new_len + 1 * sizeof(char));
	if (!new_string)
		return (NULL);
	while (i < len_s1)
	{
		new_string[i] = s1[i];
		i++;
	}
	while (i < new_len + 1)
	{
		new_string[i] = s2[i_s2];
		i++;
		i_s2++;
	}
	free((char*)s1);
	return (new_string);
}

void	ft_bzero(void *s, size_t n)
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
