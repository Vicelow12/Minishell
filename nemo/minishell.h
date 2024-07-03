/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:36:52 by tcharbon          #+#    #+#             */
/*   Updated: 2024/06/11 14:36:52 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

//structure qui sert à la création du tableau de départ
typedef struct s_token
{
    int                 index; //position du token
    int                 type; //son type/taille ('>>' = 2, '|' = 1)
    int                 saved;
    struct s_token      *next;
}   t_token;

//liste de structures principale des commandes
typedef struct s_command
{
    char                **cmd;

    int                 input;
    int                 output;

    struct s_command   *prev;
    struct s_command   *next;
}   t_command;

//main.c
int main(int argc, char **argv);
void    parse(char *line);

//create_tab.c
char    ***fill_tab(char *line);
int     size_tab(char *line, t_token **token_list);
int     init_size(char *cursor);
int     search_token(char *cursor);
void    maj_list(t_token **token_list, int token, char *line, char *cursor);
int     size_line(char *line, t_token *token_list, int *x);
int     check_token(int i, t_token *token_list);
void    fill_lines(char ***commands, char *line, t_token *token_list, int size);
int     len_word(char *line);
void    fill_words(char **commands, int x, int i, char *line);

//init_list.c
t_command *init_list(char ***tab);
int     maj_list_data(t_command *list, int i, char ***tab);
void    add_cmd(t_command *list, char **cmd);
t_command *last_element(t_command *list);
t_command   *create_element(char **cmd);
int     type_command(char **tab);
int     size_cmd(char **tab);

//libft.c
int	ft_strlen(const char *s);
int ft_strcmp(unsigned char *str1, unsigned char *str2);
int	ft_str_is_space(char *str);

#endif