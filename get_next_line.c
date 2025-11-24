/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsa <elsa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:34:30 by elsa              #+#    #+#             */
/*   Updated: 2025/11/24 19:24:55 by elsa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *get_next_line_v2(int fd)
{
    char    *buf;
	char	*line;
	char	*line_temp;
    int nb_read; 
    
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
		
		// on malloc une taille ok pour contenir line + le buf
		line_temp = malloc ((ft_strlen(get_line_until_end(buf)) + ft_strlen(line) + 1) * sizeof(char));
		
		// on ajoute le retour de get_line_until_end a notre ligne
		ft_strlcpy(line_temp, line, ft_strlen(line)); // on copie line dans line temp
		ft_strlcpy(line_temp, get_line_until_end(buf), ft_strlen(get_line_until_end(buf))); // on ajoute le buf
		free(line); // ca va pas ca 
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