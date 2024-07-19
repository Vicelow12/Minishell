/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:40:30 by tcharbon          #+#    #+#             */
/*   Updated: 2024/06/11 12:40:30 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
//test préliminaires sur le tableau avant de créer la liste principale ?
/*
void    check_tab(char ***tab)
{

}
*/

//Noeud parsing
// void    parse(char *line)
// {
//     char        ***commands;
//     t_command  *list;

//     commands = fill_tab(line); //on créer un big tableau
//     //print_tab(commands);
//     //check_tab(commands); //on peut commencer à checker des erreurs ?
//     list = init_list(commands); //créer la liste chaînée centrale du parsing
//     //une fois la liste chaînée des commandes à jour, vérifier pour chaque élements (commande) si on trouve bien le fichier dans les PATH sinon cmd inexistante

//     return ;
// }

//lancement du shell, attente de saisie utilisateur

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

int main(int argc, char **argv)
{
    char    *line;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);									// pas besoin d implementer ??
    while (1)
    {
        line = readline("MiniShell> ");
        if (line == NULL)
            exit(0);
        if (strlen(line) > 0 && ft_str_is_space(line) == 0)                 // si lentree n est pas vide ni rempli d espace ajoute a l historique
		    add_history(line);
        if (ft_strcmp(line, "") == 0 || ft_str_is_space(line) == 1)
        {
		    free(line);														// besoin de free ?
            continue;														// repete la boucle sans parse
        }    
    // parse(line);
		free(line); 
    }
    return (1);
}