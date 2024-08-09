/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:39:17 by tcharbon          #+#    #+#             */
/*   Updated: 2024/08/05 19:39:17 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    check_file(t_tools *tools, t_parsing *list)     //On parcourt la liste à la recherche de file à + de 1 mot
{
    t_parsing   *temp;
    t_parsing   *cmd;

    temp = list;
    while (temp != NULL)
    {
        if (temp->type == 2 && size_tab(temp->cmd) > 1)
        {
            cmd = find_command_backward(temp);      //On cherche si une commande est présente dans le segment
            if (cmd == NULL)
            {
                cmd = find_command_forward(temp);
                if (cmd == NULL)
                    new_cmd(tools, temp);                  //Si pas de cmd, alors les mots rattachés au file forment la cmd
                else
                    new_args(tools, cmd, temp);            //Si cmd existante, les mots rattachés au file sont des arguments à la cmd
            }
            else
                new_args(tools, cmd, temp);
        }
        temp = temp->next;
    }
    return ;
}

void    new_cmd(t_tools *tools, t_parsing *file)
{
    t_parsing   *new_cmd;
    char        **file_tab;

    new_cmd = malloc (sizeof (t_parsing));
    if (new_cmd == NULL)
        ft_exit(tools, NULL, NULL);
    new_cmd->cmd = fill_new_cmd(file->cmd);             //on récupère les mots rattachés au file
    if (new_cmd->cmd == NULL)
    {
        free(new_cmd);
        ft_exit(tools, NULL, NULL);
    }
    new_cmd->input = 0;
    new_cmd->output = 0;
    new_cmd->type = 4;
    new_cmd->next = file->next;
    new_cmd->prev = file;
    if (file->next != NULL)
        (file->next)->prev = new_cmd;
    file->next = new_cmd;
    file_tab = fill_tab_file(file->cmd);                //on supprime les mots rattachés
    if (file_tab == NULL)
        ft_exit(tools, NULL, NULL);
    free_tab(file->cmd);                                //on free l'ancien avant d'assigner le ptr sur le nouveau tab nettoyé
    file->cmd = file_tab;
    return ;
}

void    new_args(t_tools *tools, t_parsing *cmd, t_parsing *file)
{
    char    **tab_cmd;
    char    **tab_file;

    tab_cmd = fill_tab_cmd(tools, cmd->cmd, file->cmd);  //On créer le nouveau tab avec les mots rattachés
    if (tab_cmd == NULL)
        ft_exit(tools, NULL, NULL);
    tab_file = fill_tab_file(file->cmd);                //on supprime les mots rattachés
    if (tab_file == NULL)
    {
        free_tab(tab_cmd);
        ft_exit(tools, NULL, NULL);  
    }
    free_tab(cmd->cmd);         //on free les anciens
    free_tab(file->cmd);
    cmd->cmd = tab_cmd;         //on assigne les nouveaux tableaux
    file->cmd = tab_file;
    return ;
}