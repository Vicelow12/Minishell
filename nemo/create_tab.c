/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:05:19 by tcharbon          #+#    #+#             */
/*   Updated: 2024/07/02 13:05:19 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    ***fill_tab(char *line)
{
    char            ***commands;
    t_token        *token_list; //structure permettant de stocker au fur et à mesure les position des séparateurs/tokens ('>>' '|')
    int             size;

    token_list = NULL;
    size = size_tab(line, &token_list);
    //printf("size tab : %d\n", size);
    commands = malloc (sizeof (char**) * (size + 1));
    if (commands == NULL)
        exit (0);
    fill_lines(commands, line, token_list, size);
    commands[size] = NULL;
    return (commands);
}

//Combien de ligne a notre tableau
// +met à jour la liste d'index des séparateurs/tokens
int     size_tab(char *line, t_token **token_list)
{
    char    *cursor;
    char    *next_char;
    int     size;
    int     token;
    char    quote;

    cursor = line;
    size = init_size(cursor);
    while (*cursor != '\0')
    {
        if (*cursor == '"' || *cursor == '\'')
        {
            quote = *cursor;
            cursor += 1;
            while (*cursor != quote)
            {
                if (*cursor == '\0')
                {
                    printf("unclosed quotes\n");
                    exit (0);
                }
                cursor += 1;
            }
            cursor += 1;
        }
        token = search_token(cursor);
        next_char = cursor + token + 1;
        if (token > 0)
        {
            maj_list(token_list, token, line, cursor);
            if (*next_char == '\0')
                size ++;
            else
                size += 2;
        }
        cursor = next_char;
    }
    return (size);
}

//petite fonction pour décharger size_tab
//définit simplement la valeur initiale de size (différente si on commence par une commande ou un token/séparateur)
int     init_size(char *cursor)
{
    if (search_token(cursor) == 0)
        return (1);
    else
        return (0);
}

//renvoi 1 ou 2 si le curseur est sur un token/separateur, sinon 0
int     search_token(char *cursor)
{
    char    *second_char;
    char    *third_char;

    second_char = cursor + 1;
    third_char = cursor + 2;
    if ((*cursor == '<' && *second_char == '<') || (*cursor == '>' && *second_char == '>'))
    {
        if (*second_char == *third_char) //token invalid : '>>>' ou '<<<' (important vu qu'on parcourt la ligne char par char)
        {
            printf("invalid token\n");
            exit (0);
        }
        return (2);
    }
    if (*cursor == '>' || *cursor == '<' || *cursor == '|')
    {
        if (*cursor == '|' && *second_char == '|') //token invalid '||'
        {
            printf("invalid token\n");
            exit (0);
        }
        return (1);
    }
    return (0);
}

//met à jour la liste des separateur/token
//line - cursor pour avoir les coordonnées
void    maj_list(t_token **token_list, int token, char *line, char *cursor)
{
    int     index;
    t_token *new_token;
    t_token *current_token;

    current_token = (*token_list);
    index = ft_strlen(line) - ft_strlen(cursor);
    new_token = malloc(sizeof (t_token));
    if (new_token == NULL)
        exit (0);
    new_token->index = index;
    new_token->type = token;
    new_token->saved = 0;
    new_token->next = NULL;
    if (*token_list == NULL)
        *token_list = new_token;
    else
    {
        while(current_token->next != NULL)
            current_token = current_token->next;
        current_token->next = new_token;
    }
    return ;
}

int     size_line(char *line, t_token *token_list, int *x)
{
    int     size;
    int     i;
    char    quote;

    size = 0;
    i = (*x);
    if (check_token(i, token_list) > 0)
    {
        (*x) += check_token(i, token_list);
        return (1);
    }
    while (check_token(i, token_list) == 0 && line[i] != '\0')
    {
        while (line[i] == ' ') //ajouter autres espaces
            i++;
        if (line[i] == '"' || line[i] == '\'')
        {
            quote = line[i];
            i++;
            while (line[i] != quote)
                i++;
            size++;
            i++;
        }
        else if (check_token(i, token_list) == 0 && line[i] != '\0')
        {
            size++;
            while (check_token(i, token_list) == 0 && line[i] != '\0' && line[i] != ' ')
                i++;
        }
        else
            break;
    }
    (*x) = i;
    return (size);
}

int     check_token(int i, t_token *token_list)
{
    t_token *index;
    
    if (token_list == NULL)
        return (0);
    index = token_list;
    while (index != NULL)
    {
        if (index->index == i)
            return (index->type);
        else
            index = index->next;
    }
    return (0);
}

void    fill_lines(char ***commands, char *line, t_token *token_list, int size)
{
    int     i;
    int     previous_i;
    int     x;
    int     size_l;

    i = 0;
    x = 0;
    while (x < size)
    {
        //printf("x : %d / size : %d\n", x, size);
        previous_i = i;
        size_l = size_line(line, token_list, &i);
        //printf("taille commande : %d\n", size_l);
        commands[x] = malloc(sizeof (char *) * (size_l + 1));
        if (commands[x] == NULL)
            exit (0);
        else
            fill_words(commands[x], previous_i, i, line);
        commands[x][size_l] = NULL;
        x++;
    }
    return ;
}

int     len_word(char *line)
{
    int     i;
    char    quote;

    i = 0;
    if (line[i] == '"' || line[i] == '\'')
    {
        quote = line[i];
        i++;
        while (line[i] != quote)
            i++;
        i++;
        return (i);
    }
    while (line[i] != ' ' && line[i] != '\0')
        i++;
    return (i);
}

void    fill_words(char **commands, int x, int i, char *line)
{
    int     len;
    int     y;
    int     k;

    y = 0;
    while (x < i)
    {
        //printf("de %d à %d\n", x, i);
        while (line[x] == ' ')
            x++;
        len = len_word(&line[x]);
        //printf("lenword : %d\n", len);
        commands[y] = malloc (sizeof (char) * (len + 1));
        k = 0;
        while (k < len)
        {
            commands[y][k] = line[x];
            k++;
            x++;
        }
        commands[y][k] = '\0';
        y++;
    }
    return ;
}