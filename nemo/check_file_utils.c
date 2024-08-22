/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 21:25:04 by tcharbon          #+#    #+#             */
/*   Updated: 2024/08/05 21:25:04 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **fill_tab_file(char **file)
{
    char    **new_tab;
    int     i;

    new_tab = malloc (sizeof (char *) * 2);
    if (new_tab == NULL)
        return (NULL);
    new_tab[0] = malloc (sizeof (char) * (ft_strlen(file[0]) + 1));
    if (new_tab[0] == NULL)
    {
        free(new_tab);
        return (NULL);
    }
    i = 0;
    while (file[0][i] != '\0')
    {
        new_tab[0][i] =  file[0][i];
        i++;
    }
    new_tab[0][i] = '\0';
    new_tab[1] = NULL;
    return (new_tab);
}

char **fill_new_cmd(char **file_tab)
{
    char        **new_tab;
    int         size;

    size = size_tab(file_tab);
    new_tab = malloc(sizeof (char *) * size);
    if (new_tab == NULL)
        return (NULL);
    null_tab(&new_tab, size);
    if (fill(&new_tab, 0, file_tab, 1) == 0) //à partir de 1 car on saute le file lui-même
    {
        free_tab(new_tab);
        return (NULL);
    }
    new_tab[size - 1] = NULL;       //enlevable
    return (new_tab);
}

char    **fill_tab_cmd(t_tools *tools, char **cmd, char **file)
{
    char    **new_tab;
    int     size;

    size = size_tab(cmd) + size_tab(file);
    new_tab = malloc (sizeof (char *) * size);
    if (new_tab == NULL)
        return (NULL);
    null_tab(&new_tab, size);
    if (fill(&new_tab, 0, cmd, 0) == 0)
    {
        free_tab(new_tab);
        ft_exit(tools, NULL, NULL);
    }
    if (fill(&new_tab, size_tab(cmd), file, 1) == 0)
    {
        free_tab(new_tab);
        ft_exit(tools, NULL, NULL);
    }
    new_tab[size - 1] = NULL;           //enlevable
    return (new_tab);
}