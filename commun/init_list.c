/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:55:01 by tcharbon          #+#    #+#             */
/*   Updated: 2024/08/05 17:55:01 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    init_list(t_tools *tools, char *line)   //tri la ligne d'entrée dans une liste chaînée (split par token puis par espace)
{
    int         i;
    int         x;

    i = 0;
    x = 0;
    while (line[i] != '\0')
    {
        if ((line[i] == '"' || line[i] == '\'') && is_protect(line, i) != 1)
            i = pass_quote(line, i, 1);
        if (i < 0)
            return (0);
        else if (search_sep(line, i) > 0)
        {
            i = save_element(tools, x, i);                 //on vient de trouver une séparateur/token ce qui nous donne un segment à traiter
            x = i;
        }
        else
            i++;
    }
    save_element(tools, x, i);                         //dernier segment de la ligne
    return (1);
}

//renvoi 1 ou 2 si le curseur est sur un separateur, sinon 0
int     search_sep(char *line, int i)
{
    if (line == NULL || line[i] == '\0')
        return (0);
    if (line[i] == '|' && is_protect(line, i) != 1)
        return (1);
    if (line[i] == '<' && is_protect(line, i) != 1)
    {
        if (line[i + 1] == '<')
            return (2);
        else
            return (1);
    }
    if (line[i] == '>' && is_protect(line, i) != 1)
    {
        if (line[i + 1] == '>')
            return (2);
        else
            return (1);
    }
    return (0);
}

int     save_element(t_tools *tools, int x, int i)  //on enregistre le segment de x à i
{
    char    *element;
    char    *sep;
    int     index;

    search_var_env(tools, x, i);                        //on check si il y a une variable d'environnement dans ce segment
    element = extract_str(tools, x, i);                 //on récupère le contenu du segment à traiter
    sep = extract_sep(tools, i, element);               //on récupère le token/séparateur du segment
    if (element != NULL)
        add_element(tools, &tools->list_cmd, element, sep);
    if (sep != NULL)
        add_element(tools, &tools->list_cmd, sep, element);
    free(element);
    free(sep);
    index = i + search_sep(tools->line, i);
    tools->size_var_env = 0;
    return (index);
}

char    *extract_str(t_tools *tools, int x, int i)  //On recupére le contenu du segment et on remplace les variables d'environnement si il y en a
{
    char    *str;
    int     y;
    int     size;
    int     k;

    y = 0;
    size = i - x + tools->size_var_env;     //On calcule la taille du contenu du segment avec l'intervalle (i et x) + la différence causée par la variable d'environnement
    if (size <= 0)
        return (NULL);
    str = malloc(sizeof (char) * (size + 1));
    if (str == NULL)
        ft_exit(tools, NULL, NULL);
    while (y < size)
    {
        if (tools->line[x] == '$' && is_protect(tools->line, x) != 1 )   //si on croise un '$' on va copier le contenu de la variable
            tools->list_var = get_var(&str, &y, &x, tools->list_var);
        else 
        {
            str[y] = tools->line[x];
            y++;
            x++;
        }
    }
    str[y] = '\0';
    if (ft_str_is_space(str) == 1)
        return (NULL);
    return (str);
}

char    *extract_sep(t_tools *tools, int i, char *str)     //on récupère le séparateur
{
    char    *sep;
    int     size;
    int     y;

    size = search_sep(tools->line, i); //nous renvoi 1 ou 2, la taille du séparateur
    if (size == 0)
        return (NULL);
    sep = malloc (sizeof (char) * (size + 1));
    if (sep == NULL)
        ft_exit(tools, str, NULL);
    y = 0;
    while (y < size)
    {
        sep[y] = tools->line[i];
        y++;
        i++;
    }
    sep[y] = '\0';
    return (sep);
}
