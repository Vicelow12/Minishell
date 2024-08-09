/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:27:56 by tcharbon          #+#    #+#             */
/*   Updated: 2024/08/05 17:27:56 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tools     *init_tools(char **envp)                        //initialisation de la structure globale
{
    t_tools     *tools;
    int     size;
    char    **env;

    tools = malloc(sizeof (t_tools));
    if (tools == NULL)
        exit (0);
    tools->list_cmd = NULL;
    tools->list_var = NULL;
    size = size_tab(envp);
    tools->env = malloc(sizeof (char *) * (size + 1));
    if (tools->env == NULL)
    {
        free(tools);
        exit (0);
    }
    null_tab(&tools->env, size + 1);
    if (fill(&tools->env, 0, envp, 0) == 0)
        ft_exit(tools, NULL, NULL);
    tools->env[size] = NULL;                    //enlevable
    return (tools);
}