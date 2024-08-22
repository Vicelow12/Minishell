/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:12:56 by tcharbon          #+#    #+#             */
/*   Updated: 2024/08/05 18:12:56 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_valid_char(char c, int index)    //renvoi 1 si le char est valide pour une variable d'environnement, sinon 0
{
    if (index == 0)
    {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
            return (1);
    }
    else
    {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_' || (c >= '0' && c <= '9'))
            return (1);
    }
    return (0);
}

void    fill_var(char **var, char *env, int i)
{
    int     k;

    k = 0;
    while (env[i] != '\0')
    {
        (*var)[k] = env[i];
        k++;
        i++;
    }
    (*var)[k] = '\0';
    return ;
}

void    add_var_list(t_tools *tools, t_var_env **list, char *var, int old_size) //ajout d'un élement à la liste chaînée des variables d'environnement
{
    t_var_env   *new;

    new = malloc (sizeof (t_var_env));
    if (new == NULL)
    {
        free(var);
        ft_exit(tools, NULL, NULL) ;
    }
    new->var = var;                 //contenu final de la variable
    new->old_size = old_size;       //taille du nom
    new->next = NULL;
    if ((*list) == NULL)
        (*list) = new;
    else
    {
        while ((*list)->next != NULL)
            (*list) = (*list)->next;
        (*list)->next = new;
    }
    return ;
}

int     count_diff(char *var_env, int size)     // Calcul de la différence finale de taille *CONTENU - NOM*
{
    int     i;
    int     diff_size;

    diff_size = 0;
    i = 0;
    while (var_env[i] != '=')
        i++;
    i++;
    while (var_env[i] != '\0')
    {
        i++;
        diff_size++;
    }
    diff_size -= (size + 1);
    return (diff_size);
}