/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:32:17 by tcharbon          #+#    #+#             */
/*   Updated: 2024/08/05 19:32:17 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 0-NC, 4-cmd, 2-file, 3-pipe, 1-redir, 5-delim
int    type_list(t_parsing *list)
{
    find_sep(list);             //on commence par repérer les redirections, les pipes, etc..
    if (check_double_sep(list) == 0)     //on vérifie qu'il n'y a pas 2 séparateurs côte à côte (erreur)
        return (0);
    find_file(list);            //On repère les files après les redirections
    complete_type(list);        //les élements non-typés restants sont forcément des cmd
    return (1);
}

void    find_sep(t_parsing *list)  //On parcourt la liste pour déterminer les tokens (pipe, redir...)
{
    t_parsing   *index;

    index = list;
    while (index != NULL)
    {
        if (size_tab(index->cmd) != 1)
            index = index->next;
        else 
        {
            if (ft_strcmp(index->cmd[0], ">>") == 1 || ft_strcmp(index->cmd[0], "<<") == 1
                || ft_strcmp(index->cmd[0], ">") == 1 || ft_strcmp(index->cmd[0], "<") == 1)
                index->type = 1;
            else if (ft_strcmp(index->cmd[0], "|") == 1)
                index->type = 3;
            index = index->next;
        }
    }
    return ;
}

int    check_double_sep(t_parsing *list)  //on vérifie qu'il n'y a pas 2 séparateurs côte à côte (erreur)
{
    t_parsing   *index;

    index = list;
    while (index != NULL)
    {
        if (index->type == 1 || index->type == 3 || index->type == 5)
        {
            index = index->next;
            if (index == NULL)
                break ;
            if (index->type == 1 || index->type == 3 || index->type == 5)
            {
                printf("syntax error near unexpected token '%s'\n", index->cmd[0]);
                return (0);   //reset pas exit
            }
        }
        index = index->next;
    }
    return (1);
}

void    find_file(t_parsing *list) //On repère les files après les redirections
{
    t_parsing   *index;

    index = list;
    while (index->next != NULL)
    {
        if (index->type == 1)
        {
            if (ft_strcmp(index->cmd[0], ">>") == 1 || ft_strcmp(index->cmd[0], ">") == 1 || ft_strcmp(index->cmd[0], "<") == 1)
            {
                index = index->next;
                index->type = 2;
            }
            else if (ft_strcmp(index->cmd[0], "<<") == 1)
            {
                index = index->next;
                index->type = 5;
            }
        }
        if (index->next != NULL)
            index = index->next;
    }
    return ;
}

void    complete_type(t_parsing *list)  //les élements non-typés restants sont forcément des cmd 
{
    t_parsing   *index;

    index = list;
    while (index != NULL)
    {
        if (index->type == 0)
            index->type = 4;
        index = index->next;
    }
    return ;
}