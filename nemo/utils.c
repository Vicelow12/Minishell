/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:30:05 by tcharbon          #+#    #+#             */
/*   Updated: 2024/08/05 17:30:05 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     size_tab(char **tab)        //renvoi la taille d'un tableau
{
    int i;

    i = 0;
    while (tab[i])
        i++;
    return (i);
}

int     pass_quote(char *line, int i, int mode)     //passe les guillemets, mode 1 : renvoi l'index actuel, mode 2 : renvoi le nombre de char sautés
{
    char    quote;
    int     index;

    index = i;
    quote = line[i];
    i++;
    while (line[i] != quote || (line[i] == quote && is_protect(line, i) == 1))
    {
        if (line[i] == '\0')
        {
            printf("Error : unclosed quotes\n");
            return (-1);
        }
        i++;
    }
    i++;
    if (mode == 1)
        return (i);
    else
        return (i - index);
}

int    fill(char ***tab_to_fill, int i, char **origin_tab, int x)      //rempli tab_to_fill à partir de sa i-ème ligne depuis origin_tab à partir de sa x-ème ligne
{
    int     k;
    char    **new_tab;

    new_tab = (*tab_to_fill);
    while (origin_tab[x])
    {
        new_tab[i] = malloc(sizeof(char) * (ft_strlen(origin_tab[x]) + 1));
        if (new_tab[i] == NULL)
            return (0);
        k = 0;
        while (origin_tab[x][k] != '\0')
        {
            new_tab[i][k] = origin_tab[x][k];
            k++;
        }
        new_tab[i][k] = '\0';
        i++;
        x++;
    }
    return (1);
}

void    null_tab(char ***tab, int size)
{
    int     i;

    i = 0;
    while (i < size)
    {
        (*tab)[i] = NULL;
        i++;
    }
    return ;
}

int     is_protect(char *line, int index)           //détermine si le char placé à l'index de line est protégé
{
    if (line == NULL || line[0] == '\0')
        return (0);
    if (index == 0)
        return (0);
    if (line[index - 1] == '\\' && is_protect(line, index - 1) != 1)
        return (1);
    return (0);
}

int	ft_str_is_space(char *str)
{
	size_t	i;

	if (str == NULL || str[0] == '\0')
		return (0);
	i = 0;
	while(str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\v'
		&& str[i] != '\r' && str[i] != '\f' && str[i] != '\n')
			return (0);
        i++;
	}
	return (1);
}

int ft_char_is_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\v' || c == '\r' || c == '\f' || c == '\n')
		return (1);
    return (0);
}