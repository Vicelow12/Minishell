/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 02:48:58 by tcharbon          #+#    #+#             */
/*   Updated: 2024/07/09 02:48:58 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Noeud parsing
void    parse(char *line)
{
    t_parsing  *list;

    list = init_list(line);
    type_list(list);
    print_list(list);
    return ;
}

//lancement du shell, attente de saisie utilisateur
int main(int argc, char **argv, char **env)
{
    char    *line;

    if (argc > 1)
        return (0);
    while (1)
    {
        line = readline("MiniShell> ");
        if (line == NULL)
            exit(0);
        parse(line);
    }
    return (1);
}