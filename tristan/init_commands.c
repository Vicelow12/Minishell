/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:53:10 by tcharbon          #+#    #+#             */
/*   Updated: 2024/06/25 16:53:10 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands  *init_list()
{
    t_commands  *list;

    list = init_echo();
    list->next = init_cd();
    (list->next)->next = init_pwd();
    ((list->next)->next)->next = init_export();
    (((list->next)->next)->next)->next = init_unset();
    ((((list->next)->next)->next)->next)->next = init_env();
    (((((list->next)->next)->next)->next)->next)->next = init_exit();
    ((((((list->next)->next)->next)->next)->next)->next)->next = NULL;
    return (list);
}

t_commands  *init_echo()
{
    t_commands  *echo;

    echo = malloc (sizeof (t_commands));
    if (echo == NULL)
        exit (0);
    echo->name = malloc(sizeof (char) * 5);
    if (echo->name == NULL)
        exit (0);
    echo->name[0] = 'e';
    echo->name[1] = 'c';
    echo->name[2] = 'h';
    echo->name[3] = 'o';
    echo->name[4] = '\0';
    echo->argument = 1;
    echo->option = 1;
    return (echo);
}

t_commands  *init_cd()
{
    t_commands  *cd;

    cd = malloc (sizeof (t_commands));
    if (cd == NULL)
        exit (0);
    cd->name = malloc(sizeof (char) * 3);
    if (cd->name == NULL)
        exit (0);
    cd->name[0] = 'c';
    cd->name[1] = 'd';
    cd->name[2] = '\0';
    cd->argument = 1;
    cd->option = 0;
    return (cd);
}

t_commands  *init_pwd()
{
    t_commands  *pwd;

    pwd = malloc (sizeof (t_commands));
    if (pwd == NULL)
        exit (0);
    pwd->name = malloc(sizeof (char) * 4);
    if (pwd->name == NULL)
        exit (0);
    pwd->name[0] = 'p';
    pwd->name[1] = 'w';
    pwd->name[2] = 'd';
    pwd->name[3] = '\0';
    pwd->argument = 1;
    pwd->option = 0;
    return (pwd);
}

t_commands  *init_export()
{
    t_commands  *export;

    export = malloc (sizeof (t_commands));
    if (export == NULL)
        exit (0);
    export->name = malloc(sizeof (char) * 7);
    if (export->name == NULL)
        exit (0);
    export->name[0] = 'e';
    export->name[1] = 'x';
    export->name[2] = 'p';
    export->name[3] = 'o';
    export->name[4] = 'r';
    export->name[5] = 't';
    export->name[6] = '\0';
    export->argument = 1;
    export->option = 0;
    return (export);
}

t_commands  *init_unset()
{
    t_commands  *unset;

    unset = malloc (sizeof (t_commands));
    if (unset == NULL)
        exit (0);
    unset->name = malloc(sizeof (char) * 6);
    if (unset->name == NULL)
        exit (0);
    unset->name[0] = 'u';
    unset->name[1] = 'n';
    unset->name[2] = 's';
    unset->name[3] = 'e';
    unset->name[4] = 't';
    unset->name[5] = '\0';
    unset->argument = 1;
    unset->option = 0;
    return (unset);
}

t_commands  *init_env()
{
    t_commands  *env;

    env = malloc (sizeof (t_commands));
    if (env == NULL)
        exit (0);
    env->name = malloc(sizeof (char) * 4);
    if (env->name == NULL)
        exit (0);
    env->name[0] = 'e';
    env->name[1] = 'n';
    env->name[2] = 'v';
    env->name[3] = '\0';
    env->argument = 0;
    env->option = 0;
    return (env);
}

t_commands  *init_exit()
{
    t_commands  *ex;

    ex = malloc (sizeof (t_commands));
    if (ex == NULL)
        exit (0);
    ex->name = malloc(sizeof (char) * 5);
    if (ex->name == NULL)
        exit (0);
    ex->name[0] = 'e';
    ex->name[1] = 'x';
    ex->name[2] = 'i';
    ex->name[3] = 't';
    ex->name[4] = '\0';
    ex->argument = 1;
    ex->option = 0;
    return (ex);
}