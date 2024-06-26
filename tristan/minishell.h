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

#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_token
{
    int                 index; //position du token
    int                 type; //son type/taille ('>>' = 2, '|' = 1)
    int                 saved;
    struct s_token      *next;
}   t_token;

typedef struct s_commands
{
    char                *name;
    int                 option;
    int                 argument;
    struct s_commands   *next;
}   t_commands;

//init_commands
t_commands  *init_list();
t_commands  *init_echo();
t_commands  *init_cd();
t_commands  *init_pwd();
t_commands  *init_export();
t_commands  *init_unset();
t_commands  *init_env();
t_commands  *init_exit();