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

    setup_in_out(list);
    print_list(list);
    return ;
}

void sigint_handler(int signo) 											//gere ctr-c
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0); 										//efface ligne actuelle
		rl_on_new_line();												//indique a readline de commencer une nouvelle ligne
		rl_redisplay();													//reaffiche minishell :
	}
}

void sigquit_handler(int signo)											/* gere Ctrl-\ */
{
    // Ne rien faire pour ignorer le signal
}

//lancement du shell, attente de saisie utilisateur
int main(int argc, char **argv, char **env)
{
    char    *line;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
    if (argc > 1)
        return (0);
    while (1)
    {
        line = readline("MiniShell> ");
        if (line == NULL)
            exit(0);
		if (strlen(line) > 0 && ft_str_is_space(line) == 0)                 // si lentree n est pas vide ni rempli d espace ajoute a l historique
		    add_history(line);
        // if (ft_strcmp(line, "") == 0 || ft_str_is_space(line) == 1)
        // {
		//     free(line);														// besoin de free ?
        //     continue;														// repete la boucle sans parse
        // }	
        parse(line);
		free(line); 
    }
    return (1);
}