/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:14:02 by tcharbon          #+#    #+#             */
/*   Updated: 2024/08/05 17:14:02 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h> //Gestion des signaux
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h> //'NULL' sur WSL

typedef struct s_parsing                    //commandes et infos (in, out...)
{
    char                **cmd;

    int                 input;
    int                 output;
    int                 type;

    struct s_parsing   *prev;
    struct s_parsing   *next;
}   t_parsing;

typedef struct s_var_env                    //variable d'environnement et infos (modif taille)
{
    char                *var;
    int                 old_size;
    struct s_var_env    *next;
}   t_var_env;

typedef struct s_tools                      //structure globale
{
    char                *line;              //entrée brute de l'utilisateur
    char                **env;              //variables d'environnement stockées

    t_parsing           *list_cmd;          //liste chaînée finale du parsing qui contient les commandes et leurs infos (in, out, ...)
    
    t_var_env           *list_var;          //liste chaînée qui stocke les variables d'environnement pendant le parsing
    int                 size_var_env;       //variation totale de taille pour insérer les variables d'environnement
}   t_tools;

//main.c
int parse(t_tools *tools);
int main(int argc, char **argv, char **envp);

//signal.c
void sigint_handler(int signo);
void sigquit_handler(int signo);

//tools.c
t_tools *init_tools(char **envp);

//init_list.c
int init_list(t_tools *tools, char *line);
int search_sep(char *line, int i);
int save_element(t_tools *tools, int x, int i);
char *extract_str(t_tools *tools, int x, int i);
char *extract_sep(t_tools *tools, int i, char *str);

//list_utils.c
void add_element(t_tools *tools, t_parsing **list, char *str, char *str_free);
t_parsing *init_element(t_tools *tools, char *str, char *str_free);
t_parsing *last_element(t_parsing *list);
t_parsing* find_command_backward(t_parsing *node);
t_parsing* find_command_forward(t_parsing *node);

//split_segment.c
char **split_cmd(char *str);
int count_words(char *str);
int fill_tab(char ***tab_ptr, int size, char *str);
char *extract_word(char *str, int k);

//var_env.c
void search_var_env(t_tools *tools, int x, int i);
int save_var_env(t_tools *tools, int *x);
int var_exist(t_tools *tools, int x, int size);
char *extract_var(t_tools *tools, int index);
t_var_env *get_var(char **str, int *y, int *x, t_var_env *list);

//var_env_utils.c
int ft_valid_char(char c, int index);
void fill_var(char **var, char *env, int i);
void add_var_list(t_tools *tools, t_var_env **list, char *var, int old_size);
int count_diff(char *var_env, int size);

//define_type.c
int type_list(t_parsing *list);
void find_sep(t_parsing *list);
int check_double_sep(t_parsing *list);
void find_file(t_parsing *list);
void complete_type(t_parsing *list);

//check_file.c
void check_file(t_tools *tools, t_parsing *list);
void new_cmd(t_tools *tools, t_parsing *file);
void new_args(t_tools *tools, t_parsing *cmd, t_parsing *file);

//check_file_utils.c
char **fill_new_cmd(char **file_tab);
char **fill_tab_file(char **file);
char **fill_tab_cmd(t_tools *tools, char **cmd, char **file);

//redirections.c
int setup_in_out(t_parsing *command_list);
int handle_redirection_output(t_parsing *temp);
int handle_redirection_input(t_parsing *temp);
int handle_pipe(t_parsing *temp);

//utils.c
int size_tab(char **tab);
int pass_quote(char *line, int i, int mode);
int fill(char ***tab_to_fill, int i, char **origin_tab, int x);
int is_protect(char *line, int index);
int	ft_str_is_space(char *str);
int ft_char_is_space(char c);
void null_tab(char ***tab, int size);

//libft.c
size_t ft_strlen(const char *s);
int ft_strcmp(unsigned char *str1, unsigned char *str2);

//free_tools.c
void free_tab(char **tab);
void ft_reset(t_tools *tools);
void ft_exit(t_tools *tools, char *str, char *sep);
void free_var_list(t_var_env *list);
void free_parsing_list(t_parsing *list);

//tests.c
void print_list(t_parsing *head);