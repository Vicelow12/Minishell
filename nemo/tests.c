/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:12:14 by tcharbon          #+#    #+#             */
/*   Updated: 2024/07/02 13:12:14 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_list(t_token *list)
{
    while(list != NULL)
    {
        printf("Token -> %d (%d)\n", list->index, list->type);
        list = list->next;
    }
    return ;
}

void    print_tab(char ***tab)
{
    int     x;
    int     y;

    x = 0;
    while (tab[x] != NULL)
    {
        y = 0;
        while (tab[x][y] != NULL)
        {
            printf(" %s", tab[x][y]);
            y++;
        }
        printf("$\n");
        x++;
    }
}