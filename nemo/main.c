/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:14:17 by tcharbon          #+#    #+#             */
/*   Updated: 2024/08/05 17:14:17 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parse(t_tools *tools)
{
    if (init_list(tools, tools->line) == 0)             //tri la ligne d'entrée dans une liste chaînée (split par token puis par espace)
        return (0);                                        //Si renvoi (0) c'est que des quotes sont pas fermées : message d'erreur + reset (mais pas d'exit total)
    if (type_list(tools->list_cmd) == 0)                //Définition des types (0-NC, 4-cmd, 2-file, 3-pipe, 1-redir, 5-delim)
        return (0);                                          //Si renvoi 0, erreur de syntaxe (2 token à coté) : message d'erreur + reset (mais pas d'exit total)
    check_file(tools, tools->list_cmd);                //On check les file à plusieurs mots : cela signifie que des mots sont à replacer
    if (setup_in_out(tools->list_cmd) == 0)              //on assigne les valeurs in et out de chaque élement cmd
        return (0);                                         //si renvoi 0, erreur d'open file
    return (1);
}

int main(int argc, char **argv, char **envp)
{
    t_tools     *tools;                            //structure globale

    signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
    if (argc > 1)
        return (0);
    tools = init_tools(envp);                      //initialisation de la structure globale
    while (1)
    {
        tools->line = readline("MiniShell> ");
        if (tools->line == NULL)
            ft_exit(tools, NULL, NULL);
        if (tools->line[0] == '\0' || ft_str_is_space(tools->line) == 1)
            free(tools->line);
        else
        {
            add_history(tools->line); //a secure ?
            if (parse(tools) != 0)
            {
                exec(tools, envp);
                print_list(tools->list_cmd);
            }
            ft_reset(tools);   
        }
    }
    //free_total
    return (1);
}