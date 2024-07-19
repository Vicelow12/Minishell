/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 02:52:18 by tcharbon          #+#    #+#             */
/*   Updated: 2024/07/09 02:52:18 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parsing   *init_list(char *line)
{
    t_parsing   *list;
    int         i;
    int         x;

    i = 0;
    x = 0;
    list = NULL;
    while (line[i] != '\0')
    {
        if (line[i] == '"' || line[i] == '\'')
            i = pass_quote(line, i, 1);
        else if (search_sep(&line[i]) > 0)
        {
            i = save_element(line, x, i, &list);
            x = i;
        }
        else
            i++;
    }
    save_element(line, x, i, &list);
    return (list);
}

int     pass_quote(char *line, int i, int mode)
{
    char    quote;
    int     index;

    index = i;
    quote = line[i];
    i++;
    while (line[i] != quote)
    {
        if (line[i] == '\0')
        {
            printf("Error : unclosed quotes\n");
            exit (0);
        }
        i++;
    }
    i++;
    if (mode == 1)
        return (i);
    else
        return (i - index);
}

//renvoi 1 ou 2 si le curseur est sur un separateur, sinon 0
//à modifier pour vérifier si char d'avant est une protection '\' ?
int     search_sep(char *cursor)
{
    char    *second_char;
    char    *third_char;

    if (*cursor == '\0')
        return (0);
    second_char = cursor + 1;
    third_char = cursor + 2;
    if ((*cursor == '<' && *second_char == '<') || (*cursor == '>' && *second_char == '>'))
    {
        if (*second_char == *third_char) //separateur invalid : '>>>' ou '<<<' (important vu qu'on parcourt la ligne char par char)
        {
            printf("syntax error near unexpected token '%c'\n", *third_char);
            exit (0);
        }
        return (2);
    }
    if (*cursor == '>' || *cursor == '<' || *cursor == '|')
    {
        if (*cursor == '>' && *second_char == '<')
        {
            printf("syntax error near unexpected token '<'\n");
            exit (0);
        }
        if (*cursor == '<' && *second_char == '>')
        {
            printf("syntax error near unexpected token '>'\n");
            exit (0);
        }
        if (*cursor == '|' && *second_char == '|') //separateur invalid '||'
        {
            printf("syntax error near unexpected token '|'\n");
            exit (0);
        }
        return (1);
    }
    return (0);
}

int     save_element(char *line, int x, int i, t_parsing **list)
{
    char    *element;
    char    *sep;
    int     index;

    element = extract_str(line, x, i);
    sep = extract_sep(line, i);
    if (element != NULL)
        add_element(list, element);
    if (sep != NULL)
        add_element(list, sep);
    index = i + search_sep(&line[i]);
    return (index);
}

char    *extract_str(char *line, int x, int i)
{
    char    *str;
    int     y;
    int     size;

    y = 0;
    size = i - x;
    if (size == 0)
        return (NULL);
    str = malloc(sizeof (char) * (size + 1));
    if (str == NULL)
        exit (0);
    while (x != i)
    {
        str[y] = line[x];
        y++;
        x++; 
    }
    str[y] = '\0';
    return (str);
}

char    *extract_sep(char *line, int i)
{
    char    *sep;
    int     size;
    int     y;
    
    size = search_sep(&line[i]);
    if (size == 0)
        return (NULL);
    sep = malloc (sizeof (char) * (size + 1));
    if (sep == NULL)
        exit (0);
    y = 0;
    while (y < size)
    {
        sep[y] = line[i];
        y++;
        i++;
    }
    sep[y] = '\0';
    return (sep);
}

void    add_element(t_parsing **list, char *str)
{
    t_parsing   *element;
    t_parsing   *last;

    element = init_element(str);
    if ((*list) == NULL)
        (*list) = element;
    else
    {
        last = last_element((*list));
        element->prev = last;
        last->next = element;
    }
    return ;
}

t_parsing   *init_element(char *str)
{
    t_parsing   *element;
    
    if (str == NULL)
        return (NULL);
    element = malloc (sizeof (t_parsing));
    if (element == NULL)
        exit (0);
    element->cmd = split_cmd(str);
    element->input = 0;
    element->output = 1;
    element->type = 0;
    element->next = NULL;
    element->prev = NULL;
    return (element);
}

t_parsing *last_element(t_parsing *list)
{
    t_parsing *index;

    index = list;
    while (index->next != NULL)
        index = index->next;
    return (index);
}

char    **split_cmd(char *str)
{
    char    **tab;
    int     size;

    size = count_words(str);
    tab = malloc (sizeof (char *) * (size + 1));
    if (tab == NULL)
        exit (0);
    fill_tab(&tab, size, str);
    return (tab);
}

int     count_words(char *str)
{
    int     size;
    int     i;

    if (!str)
        return (0);
    i = 0;
    if (str[i] != ' ')
    {
        size = 1;
        while (str[i] != ' ' && str[i] != '\0')
            i++;
    }
    else
        size = 0;
    while (str[i] != '\0')
    {
        while (str[i] == ' ')
            i++;
        if (str[i] != '\0')
        {
            size++;
            if (str[i] == '"' || str[i] == '\'')
                i = pass_quote(str, i, 1);
            else
            {
                while (str[i] != ' ' && str[i] != '\0')
                    i++;
            }
        }
    }
    return (size);
}

void    fill_tab(char ***tab_ptr, int size, char *str)
{
    char    **tab;
    int     k;
    int     i;

    tab = (*tab_ptr);
    k = 0;
    i = 0;
    while (k < size)
    {
        while (*str == ' ')
            str += 1;
        tab[k] = extract_word(str);
        while (*str != ' ' && *str != '\0')
            str += 1;
        k++;
    }
    tab[k] = NULL;
    return ;
}

char    *extract_word(char *str)
{
    char    *word;
    int     size;
    int     i;

    if (!str)
        return (NULL);
    size = 0;
    while (str[size] != ' ' && str[size] != '\0')
    {
        if (str[size] == '"' || str[size] == '\'')
            size += pass_quote(str, size, 2);
        else
            size++;
    }
    word = malloc (sizeof (char) * (size + 1));
    if (word == NULL)
        exit (0);
    i = 0;
    while (i < size)
    {
        word[i] = str[i];
        i++;
    }
    word[i] = '\0';
    return (word);
}

// 0-NC, 1-cmd, 2-file, 3-pipe, 4-redir, 5-delim
void    type_list(t_parsing *list)
{
    find_sep(list);
    check_double_sep(list);
    find_file(list);
    complete_type(list);
    return ;
}

void    find_sep(t_parsing *list)
{
    t_parsing   *index;

    index = list;
    while (index != NULL)
    {
        if (size_cmd(index->cmd) != 1)
            index = index->next;
        else 
        {
            if (ft_strcmp(index->cmd[0], ">>") == 1 || ft_strcmp(index->cmd[0], "<<") == 1
                || ft_strcmp(index->cmd[0], ">") == 1 || ft_strcmp(index->cmd[0], "<") == 1)
                index->type = 4;
            else if (ft_strcmp(index->cmd[0], "|") == 1)
                index->type = 3;
            index = index->next;
        }
    }
    return ;
}

void    check_double_sep(t_parsing *list)
{
    t_parsing   *index;

    index = list;
    while (index != NULL)
    {
        if (index->type == 4 || index->type == 3 || index->type == 5)
        {
            index = index->next;
            if (index->type == 4 || index->type == 3 || index->type == 5)
            {
                printf("syntax error near unexpected token '%s'\n", index->cmd[0]);
                exit(0);
            }
        }
        index = index->next;
    }
    return ;
}

void    find_file(t_parsing *list)
{
    t_parsing   *index;

    index = list;
    while (index != NULL)
    {
        if (index->type == 4)
        {
            if (ft_strcmp(index->cmd[0], ">>") == 1 || ft_strcmp(index->cmd[0], ">") == 1 || ft_strcmp(index->cmd[0], "<") == 1)
            {
                index = index->next;
                index->type = 2;
            }
            else if (ft_strcmp(index->cmd[0], "<<") == 1)
            {
                index = index->next;
                index->type = 5;
            }
        }
        index = index->next;
    }
    return ;
}

void    complete_type(t_parsing *list)
{
    t_parsing   *index;

    index = list;
    while (index != NULL)
    {
        if (index->type == 0)
            index->type = 1;
        index = index->next;
    }
    return ;
}
