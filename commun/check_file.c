/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:58:16 by tcharbon          #+#    #+#             */
/*   Updated: 2024/07/20 14:58:16 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    check_file(t_parsing *list)
{
    t_parsing   *temp;
    t_parsing   *cmd;

    temp = list;
    while (temp != NULL)
    {
        if (temp->type == 2 && size_cmd(temp->cmd) > 1)
        {
            cmd = find_command_backward(temp);
            if (cmd == NULL)
            {
                cmd = find_command_forward(temp);
                if (cmd == NULL)
                    new_cmd(temp);
                else
                    new_args(cmd, temp);
            }
            else
                new_args(cmd, temp);
        }
        temp = temp->next;
    }
    return ;
}

void    new_cmd(t_parsing *file)
{
    t_parsing   *new_cmd;
    char        **file_tab;

    new_cmd = malloc (sizeof (t_parsing));
    if (new_cmd == NULL)
        exit ;
    new_cmd->cmd = fill_new_cmd(file->cmd);
    if (new_cmd->cmd == NULL)
        exit ;
    new_cmd->input = 0;
    new_cmd->output = 0;
    new_cmd->type = 4;
    new_cmd->next = file->next;
    new_cmd->prev = file;
    (file->next)->prev = new_cmd;
    file->next = new_cmd;
    file_tab = fill_tab_file(file->cmd);
    if (file_tab == NULL)
        exit ;
    free_tab(file->cmd);
    file->cmd = file_tab;
    return ;
}

char **fill_new_cmd(char **file_tab)
{
    char        **new_tab;
    int         size;

    size = size_cmd(file_tab);
    new_tab = malloc(sizeof (char *) * size);
    if (new_tab == NULL)
        return (NULL);
    fill(&new_tab, 0, file_tab, 1);
    new_tab[size - 1] = NULL;
    return (new_tab);
}

void    new_args(t_parsing *cmd, t_parsing *file)
{
    char    **tab_cmd;
    char    **tab_file;

    tab_cmd = fill_tab_cmd(cmd->cmd, file->cmd);
    if (tab_cmd == NULL)
        exit ;
    tab_file = fill_tab_file(file->cmd);
    if (tab_file == NULL)
        exit ;
    free_tab(cmd->cmd);
    free_tab(file->cmd);
    cmd->cmd = tab_cmd;
    file->cmd = tab_file;
    return ;
}

char    **fill_tab_cmd(char **cmd, char **file)
{
    char    **new_tab;
    int     size;

    size = size_cmd(cmd) + size_cmd(file);
    new_tab = malloc (sizeof (char *) * size);
    if (new_tab == NULL)
        return (NULL);
    fill(&new_tab, 0, cmd, 0);
    fill(&new_tab, size_cmd(cmd), file, 1);
    new_tab[size - 1] = NULL;
    return (new_tab);
}

char    **fill_tab_file(char **file)
{
    char    **new_tab;
    int     i;

    new_tab = malloc (sizeof (char *) * 2);
    if (new_tab == NULL)
        return (NULL);
    new_tab[0] = malloc (sizeof (char) * (ft_strlen(file[0]) + 1));
    if (new_tab[0] == NULL)
        return (NULL);
    i = 0;
    while (file[0][i] != '\0')
    {
        new_tab[0][i] =  file[0][i];
        i++;
    }
    new_tab[0][i] = '\0';
    new_tab[1] = NULL;
    return (new_tab);
}

void    free_tab(char **tab)
{
    int     i;

    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

void    fill(char ***tab_to_fill, int i, char **origin_tab, int x)
{
    int     k;
    char    **new_tab;

    new_tab = (*tab_to_fill);
    while (origin_tab[x])
    {
        new_tab[i] = malloc(sizeof(char) * (ft_strlen(origin_tab[x]) + 1));
        if (new_tab[i] == NULL)
            exit ;
        k = 0;
        while (origin_tab[x][k] != '\0')
        {
            new_tab[i][k] = origin_tab[x][k];
            k++;
        }
        new_tab[i][k] = '\0';
        i++;
        x++;
    }
    return ;
}