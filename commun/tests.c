/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:37:45 by tcharbon          #+#    #+#             */
/*   Updated: 2024/08/05 19:37:45 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_list(t_parsing *head)
{
    t_parsing *temp = head;
    while (temp) {
        printf("Command: ");
        for (char **arg = temp->cmd; *arg; ++arg) {
            printf("#%s# ", *arg);
        }
        printf("\nInput: %d, Output: %d, Type: %d\n", temp->input, temp->output, temp->type);
        temp = temp->next;
    }
    printf("-----------------------\n");
}