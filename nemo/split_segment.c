/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:26:17 by tcharbon          #+#    #+#             */
/*   Updated: 2024/08/05 19:26:17 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **split_cmd(char *str) //split le segment par les espaces
{
    char    **tab;
    int     size;

    size = count_words(str);
    tab = malloc (sizeof (char *) * (size + 1));
    if (tab == NULL)
        return (NULL);
    null_tab(&tab, size + 1);
    if (fill_tab(&tab, size, str) == 0)
    {
        free_tab(tab);
        return (NULL);
    }
    return (tab);
}

int     count_words(char *str)
{
    int     size;
    int     i;

    if (!str)
        return (0);
    i = 0;
    if (ft_char_is_space(str[i]) == 0)
    {
        size = 1;
        while ((ft_char_is_space(str[i]) == 0 || (ft_char_is_space(str[i]) == 1 && is_protect(str, i) == 1)) && str[i] != '\0')
            i++;
    }
    else
        size = 0;
    while (str[i] != '\0')
    {
        while (ft_char_is_space(str[i]) == 1 && is_protect(str, i) != 1)
            i++;
        if (str[i] != '\0')
        {
            size++;
            if ((str[i] == '"' || str[i] == '\'') && is_protect(str, i) != 1)
                i = pass_quote(str, i, 1);                                      //quotes non fermées déjà vérifiée dans 'init_list' donc pas besoin de refaire remonter l'erreur ici
            else
            {
                while ((ft_char_is_space(str[i]) == 0 || (ft_char_is_space(str[i]) == 1 && is_protect(str, i) == 1)) && str[i] != '\0')
                    i++;
            }
        }
    }
    return (size);
}

int    fill_tab(char ***tab_ptr, int size, char *str)  //on remplit mot par mot
{
    char    **tab;
    int     k;
    int     i;

    if (!str)
        return (1);
    tab = (*tab_ptr);
    k = 0;
    i = 0;
    while (k < size)
    {
        while (ft_char_is_space(str[i]) == 1)
            i++;
        tab[k] = extract_word(str, i);
        if (tab[k] == NULL)
            return (0);
        while ((ft_char_is_space(str[i]) == 0 || (ft_char_is_space(str[i]) == 1 && is_protect(str, i) == 1)) && str[i] != '\0')
            i++;
        k++;
    }
    tab[k] = NULL;
    return (1);
}

char    *extract_word(char *str, int k)
{
    char    *word;
    int     size;
    int     i;

    size = 0;
    str+= k;        //on saute les espaces
    while ((ft_char_is_space(str[size]) == 0 || (ft_char_is_space(str[size]) == 1 && is_protect(str, size) == 1)) && str[size] != '\0')
    {
        if (str[size] == '\\' && is_protect(str, size) != 1)
            size++;
        else if ((str[size] == '"' || str[size] == '\'') && is_protect(str, size) != 1)
            size += pass_quote(str, size, 2);           //quotes ouvertes déjà verif dans 'init_list'
        else
            size++;
    }
    word = malloc (sizeof (char) * (size + 1));
    if (word == NULL)
        return (NULL);
    i = 0;
    while (i < size)
    {
        word[i] = str[i];
        i++;
    }
    word[i] = '\0';
    return (word);
}