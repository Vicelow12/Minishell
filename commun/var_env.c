/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:02:06 by tcharbon          #+#    #+#             */
/*   Updated: 2024/08/05 18:02:06 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    search_var_env(t_tools *tools, int x, int i)    //on cherche des variables d'environnement entre x et i
{
    tools->size_var_env = 0;
    while (x < i)
    {
        if (tools->line[x] == '$' && is_protect(tools->line, x) != 1)      //si on en trouve une, on la traite
            tools->size_var_env += save_var_env(tools, &x);
        else
            x++;
    }
    return ;
}

int     save_var_env(t_tools *tools, int *x)    //renvoi la différence de taille provoquée par le traitement de la variable d'environnement (taille contenu - taille nom)
{
    int     size;
    char    *var;
    int     index_var;
    int     diff_size;

    size = 0;
    (*x)++;                                            //on saute le '$'
    while (ft_valid_char(tools->line[(*x)], size))
    {
        size++;                                        //on calcul la taille du nom de la variable
        (*x)++;
    }
    index_var = var_exist(tools, (*x) - size, size);   //on check si le nom correspond à une variable d'environnement existante
    if (index_var < 0)    
        return (-(size + 1));                          //si index_var = -1 alors variable inexistante, on renvoi la taille du nom en négatif (le +1 c'est pour le '$' pas compté au début)
    var = extract_var(tools, index_var);               //On récupère le contenu (uniquement) de la variable
    if (var == NULL)
        ft_exit(tools, NULL, NULL);
    add_var_list(tools, &tools->list_var, var, size + 1);      //on ajoute un élement à la liste chaînée des variables pour plus tard
    diff_size = count_diff(tools->env[index_var], size); //on compte la différence finale de taille *CONTENU - NOM*
    return (diff_size);
}

int     var_exist(t_tools *tools, int x, int size)    //check si une variable d'environnement existe et renvoi son index dans le tableau envp, sinon -1
{
    int     i;
    int     k;
    int     h;

    i = 0;
    while (tools->env[i])
    {
        k = 0;
        h = x;
        while (tools->env[i][k] != '=')
        {
            if (tools->env[i][k] == tools->line[h])
            {
                k++;
                h++;
                if (k == size)
                    return (i);
            }
            else
                break ;
        }
        i++;
    }
    add_var_list(tools, &tools->list_var, NULL, size + 1);
    return (-1);
}

char    *extract_var(t_tools *tools, int index)  //nettoie la variable d'environnement et renvoi son contenu dans une char distincte
{
    int     size;
    int     i;
    char    *var;
    int     k;

    size = 0;
    i = 0;
    while (tools->env[index][i] != '=')         //on saute le nom de la variable jusqu'au premier '='
        i++;
    i++;
    while (tools->env[index][i] != '\0')
    {
        size++;
        i++;
    }
    var = malloc (sizeof (char) * (size + 1));
    if (var == NULL)
        return (NULL);
    fill_var(&var, tools->env[index], i - size); //on récupère le reste
    return (var);
}

t_var_env *get_var(char **str, int *y, int *x, t_var_env *list) //on copie le contenu de la première variable d'env dans str, on met bien à jour les index x et y
{
    int         i;
    t_var_env   *temp_list;

    i = 0;
    if (list->var != NULL)
    {
        while (list->var[i] != '\0')
        {
            (*str)[(*y)] = list->var[i];
            (*y)++;
            i++;
        }
        free(list->var);
    }
    (*x) += list->old_size;                 //on saute le nom de la variable qu'on ne veut pas copié
    temp_list = list->next;
    free(list);
    return (temp_list);
}