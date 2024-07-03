/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:12:38 by tcharbon          #+#    #+#             */
/*   Updated: 2024/07/02 15:12:38 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//compte le nb de mots dans la ligne du tab
int     size_cmd(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
        i++;
    return (i);
}

//determine le type de la ligne
int     type_command(char **tab)
{
    if (size_cmd(tab) > 1) //si plusieurs mots dans la ligne = cmd car pipe et redirection  = 1 mot
        return (1);
    if (ft_strcmp(tab[0], ">>") == 1 || ft_strcmp(tab[0], "<<") == 1 || ft_strcmp(tab[0], "|") == 1) //si 1 mot, on vérifie si c'est pipe/redir 
        return (0);
    return (1); //sinon c'est une commande à 1 mot
}

//malloc et initialise les données d'un élement
t_command   *create_element(char **cmd)
{
    t_command *element;
    
    element = malloc (sizeof (t_command));
    if (element == NULL)
        return (NULL);
    element->cmd = cmd; //la liste de mots : commande + option + arguments
    element->input = 0; //entrée standard par défaut
    element->output = 1; //sortie standard par défaut
    element->prev = NULL; 
    element->next = NULL;
    return (element);
}

//renvoi un pointeur sur le dernier élement de la liste
t_command *last_element(t_command *list)
{
    t_command *index;

    index = list;
    while (index->next != NULL)
        index = index->next;
    return (index);
}

//ajoute un élement à la liste chaînée
void    add_cmd(t_command *list, char **cmd)
{
    t_command *index;
    
    if (list == NULL)
        list = create_element(cmd);
    else
    {
        index = last_element(list);
        index->next = create_element(cmd);
        (index->next)->prev = index;
    }
}

//va mettre à jour les infos de la liste (pipe, redirections, etc...)
int     maj_list_data(t_command *list, int i, char ***tab)
{
    //si c'est un pipe, mettre à jour l'output de l'élement/commande (i - 1) et l'input de l'élement/commande (i + 1)
    //si c'est une redirection '>>', mettre à jour l'output de l'élement (i - 1) vers le fichier (i + 1) (fonction open)
    //si c'est une redirection '>', pareil mais ça écrase le contenu du fichier s'il existe au lieu d'ajouter à la fin.
    //si c'est une redirection '<<', truc chelou ou la commande (i - 1) va prendre en input tout ce que l'utilisateur écrit dans le terminal jusqu'à que le délimiteur (i + 1) soit rentré
    //si c'est une redirection '<', la commande (i - 1) prend en input le contenu du fichier (i + 1)
}

//création de la liste chaînée principale
t_command *init_list(char ***tab)
{
    t_command   *list;
    int         i;

    list = NULL;
    i = 0;
    while (tab[i])
    {
        if (type_command(tab[i]) == 1) //si la ligne correspond à une commande on ajoute un élement à la liste
            add_cmd(list, tab[i]);
        else
            i = maj_list_data(list, i, tab); //sinon on met à jour les données des élements existants (redirection, etc...)
        i++;
    }
    return (list);
}