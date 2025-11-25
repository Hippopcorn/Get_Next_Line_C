/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evarache <evarache@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:34:30 by elsa              #+#    #+#             */
/*   Updated: 2025/11/25 15:45:17 by evarache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char    *get_next_line_v3(int fd)
{
    char    	*buf;
	char		*line;
	char		*current_line;
	static char	*buf_mem;
    int 		nb_read; 
    
	line = NULL;
	while (ft_strchr_index(line, '\n') == -1) // tant qu'on est pas tombé sur un \n
    {
		nb_read = -1;
    	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
   		if (!buf)
    		return (NULL);
    	nb_read = read(fd, buf, BUFFER_SIZE);
    	if (nb_read == -1 || nb_read == 0) // modifier pour dans le cas ou on lit rien
        	return (NULL);
    	buf[nb_read] = '\0';  
		current_line = get_line_until_end(buf);

		if (current_line != buf) // si on a coupé le buf pour ne récupérer que le début
		{
			// stocker la fin
		}
		//printf("current_line : %s\n", current_line);
		
		// on malloc une taille ok pour contenir line + le buf
		line = ft_realloc (line, (ft_strlen(current_line) + ft_strlen(line) + 1) * sizeof(char));  // realloc agrandis la taille malloc et met line dedans
		//printf("line before add current_line : %s\n", line);
		
		// on ajoute le buf a notre ligne
		ft_strlcat(line, current_line, ft_strlen(current_line) + ft_strlen(line) + 1); // on ajoute le buf
		//printf("line after : %s\n", line);

		free(buf);
	}
    return (line);
}

// retourne buf jusqu'a \n ou buf entier
char    *get_line_until_end(char *buf)
{
    int     i_end_line;
    
    i_end_line = ft_strchr_index(buf, '\n');
    if (i_end_line != -1)
        return(ft_substr(buf, 0, i_end_line + 1)); // str, i_start et len 
    return (buf);
}

void	*ft_realloc(void *ptr, size_t size)  // imaginons ptr = line et size est la nouvelle taille 
{
	void	*dup;
	size_t	len;
	
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
	len = ft_strlen((char *)ptr);
	//printf("len of line : %zu\n", len);
	if (len > size - 1)
		len = size - 1;
	ft_memcpy(dup, ptr, len);
	((char *)dup)[len] = '\0';
	free(ptr);
	return (dup);
}

// ft_memcpy copies n bytes from memory area src to memory 
// area dest. The memory areas must not overlap.  
// Use memmove(3) if the memory areas do overlap.

void	*ft_memcpy( void *dest, const void *src, size_t n)
{
	char			*dest_cast;
	char			*src_cast;
	unsigned char	i;

	i = 0;
	dest_cast = (char *)dest;
	src_cast = (char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		dest_cast[i] = src_cast[i];
		i++;
	}
	return (dest);
}

// #include <string.h>
// int main()
// {
// 	char *line = malloc(5);
// 	strcpy(line, "chat");

// 	char *dup = ft_realloc(line, 10);

// 	if (!dup)
// 	printf("ERREUR malloc\n");

// 	// test contenu
// 	if (strcmp(dup, "chat") != 0)
// 	printf("ERREUR contenu recopié\n");

// 	// test écriture dans le nouvel espace
// 	dup[4] = 'X';
// 	dup[5] = 'Y';
// 	dup[6] = 'Z';
// 	dup[7] = 0;

// 	printf("%s\n", dup); // doit afficher chaXYZ

// }