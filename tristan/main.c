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

//test préliminaires sur le tableau avant de créer la liste principale ?
/*
void    check_tab(char ***tab)
{
    //Si on trouve une case : ';' on peut renvoyer "unexpected token" puisqu'on doit pas l'interpreter comme '><' ou '<>'
}
*/

//Noeud parsing
void    parse(char *line)
{
    char        ***commands;
    t_command  *list;

    commands = fill_tab(line); //on créer un big tableau
    print_tab(commands);
    //check_tab(commands); //on peut commencer à checker des erreurs ?
    //list = init_list(commands); //créer la liste chaînée centrale du parsing
    //une fois la liste chaînée des commandes à jour, vérifier pour chaque élements (commande) si on trouve bien le fichier dans les PATH sinon cmd inexistante

    return ;
}

//lancement du shell, attente de saisie utilisateur
int main(int argc, char **argv)
{
    char    *line;

    while (1)
    {
        line = readline("MiniShell> ");
        if (line == NULL)
            exit(0);
        parse(line);
    }
    return (1);
}