/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evarache <evarache@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:34:30 by elsa              #+#    #+#             */
/*   Updated: 2025/11/26 14:31:23 by evarache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char    *get_next_line(int fd)
{
    char    	*buf;
	char		*line;
	char		*current_line;
	static char	*buf_mem;
    int 		nb_read; 
	int			eof;
    
	line = NULL;
	eof = 0;
	if (buf_mem != NULL)
	{
		//printf("buf_mem = %s\n", buf_mem);
		//printf("get_line_until_end = %s\n", get_line_until_end(buf_mem));
		line = malloc (ft_strlen(get_line_until_end(buf_mem)) + 1 * sizeof(char));
		ft_memcpy(line, get_line_until_end(buf_mem), ft_strlen(get_line_until_end(buf_mem)) + 1);  //OK
		//printf("line : %s\n", line);
		
		if (line != buf_mem)  // si on a trouvé un \n dans buf_mem
		{
			buf_mem = ft_realloc(ft_substr(buf_mem, ft_strchr_index(buf_mem, '\n') + 1, (ft_strlen(buf_mem) + 1)
			- (ft_strchr_index(buf_mem, '\n') + 1)), (ft_strlen(buf_mem) + 1) - (ft_strchr_index(buf_mem, '\n') + 1));  // on restocke la fin de buf_mem // pb : on pert un carac a la fin a chaque fois qu'on stocke 
			//printf("buf_mem : %s\n", buf_mem);
		}
			
	}

	//RAJOUTER UNE CONDITION POUR QUITTER LA BOUCLE SI ON A ATTEINT LA FIN DU FICHIER
	while (count_carac(line, '\n') != 1) // tant qu'on est pas tombé sur un \n ou que nb_read est de la taille de BUFFER_SIZE
    {
		nb_read = -1;
    	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
   		if (!buf)
    		return (NULL);
    	nb_read = read(fd, buf, BUFFER_SIZE);
		if (nb_read == 0)
		{
			free(buf_mem);
			buf_mem = NULL;
			return (line);
		}
		//printf("nb_read : %d\n", nb_read);
    	if (nb_read == -1 || nb_read == 0) // modifier pour dans le cas ou on lit rien
			return (NULL);
    	buf[nb_read] = '\0';  
		//printf("buf : %s\n", buf);
		current_line = get_line_until_end(buf);
		//printf("current_line : %s\n", current_line);
		if (current_line != buf) // si on a coupé le buf pour ne récupérer que le début
		{
			// stocker la fin
			buf_mem = ft_substr(buf, ft_strchr_index(buf, '\n') + 1, (ft_strlen(buf) + 1) - (ft_strchr_index(buf, '\n') + 1));   // a modifier
		}
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
	//printf("i_end_line : %d\n", i_end_line);
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

int	count_carac(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

// int main()
// {
// 	int 	fd;
// 	char	*line;
	
// 	fd = open("to_do.txt", O_RDONLY);
	
// 	line =  get_next_line(fd);
// 	printf("Result GNL : %s", line);
// 	free (line);

// 	line =  get_next_line(fd);
// 	printf("Result GNL : %s", line);
// 	free (line);

// 	line =  get_next_line(fd);
// 	printf("Result GNL : %s", line);
// 	free (line);

// 	line =  get_next_line(fd);
// 	printf("Result GNL : %s", line);
// 	free (line);

// 	line =  get_next_line(fd);
// 	printf("Result GNL : %s", line);
// 	free (line);

// 	line =  get_next_line(fd);
// 	printf("Result GNL : %s", line);
// 	free (line);

// 	line =  get_next_line(fd);
// 	printf("Result GNL : %s", line);
// 	free (line);

// 	line =  get_next_line(fd);
// 	printf("Result GNL : %s", line);
// 	free (line);

// }

// fonctionne avec buffer size 4 a 353
// pb avec derniere ligne