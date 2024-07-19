/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 02:49:45 by tcharbon          #+#    #+#             */
/*   Updated: 2024/07/09 02:49:45 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

//liste de structures principale
typedef struct s_parsing
{
    char                **cmd;

    int                 input;
    int                 output;
    int                 type;

    struct s_parsing   *prev;
    struct s_parsing   *next;
}   t_parsing;

//main.c
int     main(int argc, char **argv, char **env);
void    parse(char *line);

//tests.c
void    print_list(t_parsing *list);

//init_list.c
t_parsing   *init_list(char *line);
int     pass_quote(char *line, int i, int mode);
int     search_sep(char *cursor);
int     save_element(char *line, int x, int i, t_parsing **list);
char    *extract_str(char *line, int x, int i);
char    *extract_sep(char *line, int i);
void    add_element(t_parsing **list, char *str);
t_parsing   *init_element(char *str);
t_parsing *last_element(t_parsing *list);
char    **split_cmd(char *str);
int     count_words(char *str);
void    fill_tab(char ***tab_ptr, int size, char *str);
char    *extract_word(char *str);
void    type_list(t_parsing *list);
void    find_sep(t_parsing *list);
void    check_double_sep(t_parsing *list);
void    find_file(t_parsing *list);
void    complete_type(t_parsing *list);

//libft.c
int     ft_strcmp(unsigned char *str1, unsigned char *str2);
int     size_cmd(char **tab);