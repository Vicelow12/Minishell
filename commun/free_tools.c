/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:47:00 by tcharbon          #+#    #+#             */
/*   Updated: 2024/08/05 19:47:00 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_tab(char **tab)
{
    int     i;

    i = 0;
    while (tab[i] != NULL)
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

void    ft_reset(t_tools *tools)
{
    t_parsing   *temp;
    t_parsing   *next;
    
    if (tools->line != NULL)
        free(tools->line);
    if (tools->list_cmd != NULL)
        free_parsing_list(tools->list_cmd);
    tools->line = NULL;
    tools->list_cmd = NULL;
    return ;
}

void    ft_exit(t_tools *tools, char *str1, char *str2)
{
    if (str1 != NULL)
        free(str1);
    if (str2 != NULL)
        free(str2);
    if (tools->list_var != NULL)
        free_var_list(tools->list_var);
    if (tools->list_cmd != NULL)
        free_parsing_list(tools->list_cmd);
    free_tab(tools->env);
    free(tools);
    exit (0);
}

void    free_var_list(t_var_env *list)
{
    t_var_env   *next;
    
    while (list != NULL)
    {
        if (list->var != NULL)
            free(list->var);
        next = list->next;
        free(list);
        list = next;
    }
    return ;
}

void    free_parsing_list(t_parsing *list)
{
    t_parsing   *next;

    while (list != NULL)
    {
        if (list->cmd != NULL)
            free_tab(list->cmd);
        next = list->next;
        free(list);
        list = next;
    }
    return ;
}