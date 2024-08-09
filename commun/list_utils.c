/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:22:42 by tcharbon          #+#    #+#             */
/*   Updated: 2024/08/05 19:22:42 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    add_element(t_tools *tools, t_parsing **list, char *str, char *str_free)  //Ajoute l'élément de la commande à la liste chaînée finale
{
    t_parsing   *element;
    t_parsing   *last;

    element = init_element(tools, str, str_free);
    if ((*list) == NULL)
        (*list) = element;
    else
    {
        last = last_element((*list));
        element->prev = last;
        last->next = element;
    }
    return ;
}

t_parsing   *init_element(t_tools *tools, char *str, char *str_free)  //initie l'élement et ses valeurs de base
{
    t_parsing   *element;
    
    if (str == NULL)
        return (NULL);
    element = malloc (sizeof (t_parsing));
    if (element == NULL)
        ft_exit(tools, str, str_free);
    element->cmd = split_cmd(str);                  //il faut split le segment par les espaces pour séparer les différents élements
    if (element->cmd == NULL)
    {
        free(element);
        ft_exit(tools, str, str_free);
    }
    element->input = 0;
    element->output = 0;
    element->type = 0;
    element->next = NULL;
    element->prev = NULL;
    return (element);
}

t_parsing *last_element(t_parsing *list)
{
    t_parsing *index;

    index = list;
    while (index->next != NULL)
        index = index->next;
    return (index);
}

t_parsing* find_command_backward(t_parsing *node)
{
    while (node->prev != NULL && node->prev->type != 3)
	{
        node = node->prev;
        if (node->type == 4)
            return node;
    }
    return NULL;
}

t_parsing* find_command_forward(t_parsing *node)
{
    while (node->next != NULL && node->next->type != 3)
	{
        node = node->next;
        if (node->type == 4)
            return node;
    }
    return NULL;
}