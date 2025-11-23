/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsa <elsa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:50:57 by elsa              #+#    #+#             */
/*   Updated: 2025/11/23 21:39:19 by elsa             ###   ########.fr       */
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
	s_cast = (char *)s;
	while (s_cast[i] != '\0')
	{
		if ((unsigned char)c == s_cast[i])
			return (i);
		i++;
	}
	return (-1);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	char			*src_cast;
	size_t				result;

	i = 0;
	src_cast = (char *)src;
	result = ft_strlen(src_cast);
	if (size > 0)
	{
		while ((src_cast[i] != '\0') && (i < (size - 1)))
		{
			dst[i] = src_cast[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (result);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	len_dest;
	unsigned int	len_src;
	char			*src_cast;
	size_t			i;

	src_cast = (char *)src;
	len_src = ft_strlen(src_cast);
	len_dest = ft_strlen(dst);
	i = 0;
	if (size <= len_dest)
		return (len_src + size);
	if (size == 0)
		return (len_src);
	while (src_cast[i] != '\0' && i < (size - len_dest - 1))
	{
		dst[len_dest + i] = src_cast[i];
		i++;
	}
	dst[len_dest + i] = '\0';
	return (len_dest + len_src);
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
		return (ft_calloc(1, sizeof(char)));
	if (end >= ft_strlen(s))
		alloc = ft_strlen(s) - start;
	else
		alloc = len;
	substring = ft_calloc((alloc + 1), sizeof(char));
	if (!substring)
		return (NULL);
	while (start < end && start < ft_strlen(s))
	{
		substring[i] = s[start];
		i++;
		start++;
	}
	i++;
	substring[i] = '\0';
	return (substring);
}


// int	ft_open_file(const char *file)
// {
// 	int fd;
	
// 	fd = open(file, O_RDONLY);
// 	if (fd == -1)
// 		return (1);
// 	return (fd);
// }
// the read function returns the number of characters that it has read, or -1 in case of error. return 0 when it is at the end of the file (EOF)
// size_t read(int fd, void *buf, size_t count);

// int    ft_count_carac(int fd)
// {
// 	char	buf[BUFFER_SIZE];
// 	size_t	nb_carac;
// 	int		nb_read;
	
// 	nb_read = -1; //count the nb of carac read
// 	nb_carac = 0;
// 	while (nb_read != 0)
// 	{
// 		nb_read = read(fd, buf, BUFFER_SIZE);
// 		if (nb_read == -1)
// 			return (0);
// 		nb_carac += nb_read;
// 	}
// 	return (nb_carac);
// }


// char	*ft_get_file(int fd, int nb_carac)
// {
// 	//int	i;
// 	char	*buf;
	
// 	buf = malloc((nb_carac + 1) * sizeof(char));
// 	 read(fd, buf, nb_carac);
// 	//buf[i] = '\0';
// 	return (buf);
// }


// int main()
// {
// 	int fd;
	
// 	fd = ft_open_file("cat.txt");
//     printf("%d\n", ft_count_carac(fd));
//     printf("%s\n", ft_get_file(fd, ft_count_carac(fd)));
// }