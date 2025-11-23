/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsa <elsa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:49:16 by elsa              #+#    #+#             */
/*   Updated: 2025/11/22 22:54:43 by elsa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *get_next_line(int fd)
{
	char			*buf;
    char            *line;   
	static char		*next_line;
	int				nb_read;
    int             i_end;
    
    
    // recuperer le debut de la ligne si il a été stocké
    if (next_line != NULL)
    {
        // si il y a un autre \n, on malloc une taille de 0 a l'index de \n, on fait une substr 
        //de next_line jusqu'au \n et on la retourne en conservant la fin de next_line
        i_end = ft_strchr_index(next_line, '\n');
        if (i_end != -1)
        {
            line = malloc((i_end + 2) * sizeof(char));  // +2 pour avoir l'indice 0 et pour rajouter un \0 a la fin
            ft_strlcpy(line, next_line, i_end + 1);  // +1 pour inclure l'index 0 dans la copy
            line[i_end + 1] = '\0';
            // on recupere la fin de next_line
            char *temp = ft_substr(next_line, i_end + 1, (ft_strlen(next_line) - i_end + 1));
            //free (next_line);
            next_line = malloc(ft_strlen(temp + 1) * sizeof(char));
            next_line = temp;
            return (line);
        }
        else    
        {
            // si il n'y a pas de \n, on malloc une taille de la taille de next_line
            line = malloc(ft_strlen(next_line) * sizeof(char));
            ft_strlcpy(line, next_line, ft_strlen(next_line));
            //free(next_line);  
        }
    }

    // on a une line vide ou une line avec un début de ligne dedans
    
    buf = malloc(BUFFER_SIZE * sizeof(char));
	nb_read = read(fd, buf, BUFFER_SIZE);
    // retourne un pointer sur la permiere occ de '\n'ou NULL si pas de \n
    next_line = ft_strchr(buf, '\n'); 
    if (next_line != NULL) 
    {
         next_line++; // pour exclure le \n dans buf_mem
    }
    else // tant qu'on est pas tombé sur un \n, il faut faire une boucle pour continuer de lire
    {
        // si next_line = null, on ajoute tout le buf dans line
        // on realloc de la place puis strlcat
        ft_strlcat(line, buf, BUFFER_SIZE);   
    }
    
}