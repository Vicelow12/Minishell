/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 02:50:34 by tcharbon          #+#    #+#             */
/*   Updated: 2024/07/09 02:50:34 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_list(t_parsing *list)
{
    int     i;
    int     y;
    
    y = 0;
    printf("[print_list] : %p\n", list);
    while(list != NULL)
    {
        printf("Element %d | type : %d\n", y, list->type);
        i = 0;
        while (list->cmd[i] != NULL)
        {
            printf("$%s$ ", list->cmd[i]);
            i++;
        }
        list = list->next;
        y++;
        printf("\n");
    }
    printf("[print_list FIN]\n");
    return ;
}