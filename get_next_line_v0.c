/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsa <elsa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:49:16 by elsa              #+#    #+#             */
/*   Updated: 2025/11/24 15:17:09 by elsa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *get_next_line(int fd)
{
	char			*buf[BUFFER_SIZE];
    char            *line;   
    char            *line_temp;
	static char		*next_line;
	int				nb_read;
    int             i_end;
    int             nb_malloc_next;
    
    
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
            return (line); // qui sera free dans le main
        }
        else    
        {
            // si il n'y a pas de \n, on malloc une taille de la taille de next_line
            line_temp = malloc(ft_strlen(next_line) * sizeof(char));
            ft_strlcpy(line_temp, next_line, ft_strlen(next_line));
            free(next_line);  
        }
    }
    
    //line_temp = null ou debut de ligne
    // on a une line vide ou une line avec un début de ligne dedans
    
	nb_read = read(fd, buf, BUFFER_SIZE);
    // retourne un pointer sur la premiere occ de '\n' ou NULL si pas de \n
    nb_malloc_next = ft_strlen(ft_strchr(buf, '\n'));
    
    while (nb_malloc_next == 0) // tant qu'on ne tombe pas sur un \n
    {
 
        line = malloc((ft_strlen(line_temp) + BUFFER_SIZE) * sizeof(char));
        // on ajoute toute la ligne
        
        ft_strlcpy(line, line_temp, ft_strlen(line_temp));
        ft_strlcpy(line, buf, BUFFER_SIZE);
        // on continue de lire 
        nb_read = read(fd, buf, BUFFER_SIZE);
        nb_malloc_next = ft_strlen(ft_strchr(buf, '\n'));
        
        line_temp = malloc(ft_strlen(line) * sizeof(char));
        line_temp = line;
        
    }
    next_line = malloc(nb_malloc_next * sizeof(char));
    next_line = ft_strchr(buf, '\n'); 
    next_line++; // pour exclure le \n dans buf_mem
    

    
    else // tant qu'on est pas tombé sur un \n, il faut faire une boucle pour continuer de lire
    {
        // si next_line = null, on ajoute tout le buf dans line
        // on realloc de la place puis strlcat
          
    }
    
}