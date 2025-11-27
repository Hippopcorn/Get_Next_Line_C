/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsa <elsa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:34:30 by elsa              #+#    #+#             */
/*   Updated: 2025/11/27 09:06:33 by elsa             ###   ########.fr       */
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
    
	line = NULL;
	if (buf_mem != NULL)
	{
		line = malloc (ft_strlen(get_line_until_end(buf_mem)) + 1 * sizeof(char));
		ft_memcpy(line, get_line_until_end(buf_mem), ft_strlen(get_line_until_end(buf_mem)) + 1);
		
		if (line != buf_mem)  // si on a trouvé un \n dans buf_mem, on garde dans buf_meme que la fin apres le \n
			buf_mem = ft_substr(buf_mem, ft_strchr_index(buf_mem, '\n') + 1,
			(ft_strlen(buf_mem) + 1) - (ft_strchr_index(buf_mem, '\n') + 1));	
	}
	
	while (ft_strchr_index(line, '\n') == -1) // tant qu'on est pas tombé sur un \n ou que nb_read est de la taille de BUFFER_SIZE
    {
		nb_read = -1;
    	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));  // est ce vraiment necessaire?
   		if (!buf)
    		return (NULL);
    	nb_read = read(fd, buf, BUFFER_SIZE);
		
		if (nb_read == 0)   // on a atteint la fin du fichier
		{
			free(buf_mem);
			buf_mem = NULL;
			return (line);
		}
    	if (nb_read == -1) // si on a une erreur a la lecture, on return NULL
		{
			free(buf_mem);
			return (NULL);
		}
    	buf[nb_read] = '\0';  
		current_line = get_line_until_end(buf);
		//printf("buf : %s\n", buf);
		//printf("current_line : %s\n", current_line);
		
		if (current_line != buf) // si on a coupé le buf pour ne récupérer que le début
			//buf_mem = (ft_strchr(buf, '\n') + 1);   // remplacer par substr
			buf_mem = (ft_substr(buf, (ft_strchr_index(buf, '\n') + 1), (ft_strlen(buf) + 1) - (ft_strchr_index(buf, '\n') + 1)));   
			//printf("buf_mem au debut  : %s\n", buf_mem);

			line = ft_strjoin(line, current_line);

			free(buf);  // on perd buf_mem
			//printf("buf_mem apres free buf : %s\n", buf_mem);

		}
	//printf("buf_mem de fin : %s\n", buf_mem);
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


// int main()
// {
// 	int 	fd;
// 	char	*line;
	
// 	fd = open("to_do.txt", O_RDONLY);
// 	printf("BUFFER_SIZE : %d\n", BUFFER_SIZE);
	
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