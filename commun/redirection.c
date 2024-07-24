#include "minishell.h"

t_parsing* find_command_backward(t_parsing *node)
{
    while (node->prev != NULL && node->prev->type != 3)
	{
        node = node->prev;
        if (node->type == 4)
            return node;
    }
    return NULL;
}

t_parsing* find_command_forward(t_parsing *node)
{
    while (node->next != NULL && node->next->type != 3)
	{
        node = node->next;
        if (node->type == 4)
            return node;
    }
    return NULL;
}

int handle_redirection_output(t_parsing *temp)
{
	int fd;
	t_parsing *browse;

	fd = open(temp->next->cmd[0], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (0);
	browse = find_command_backward(temp);
	if (!browse)
		browse = find_command_forward(temp->next);
	if (browse)
		browse->output = fd;
	else
		return (0);
	return (1);
}

int handle_redirection_input(t_parsing *temp)
{
	t_parsing	*browse;
	int			fd;

	fd = open((temp->next)->cmd[0], O_RDONLY);
	if (fd == -1)
		return (0);
	browse = find_command_backward(temp);
	if (!browse) 
		browse = find_command_forward(temp->next);
	if (browse) 
		browse->input = fd;
	else
		return (0);
	return (1);
}

int handle_pipe(t_parsing *temp)
{
    int 		tube[2];
	t_parsing 	*browse;

    pipe(tube);
    temp->input = tube[1];
    temp->output = tube[0];
    browse = find_command_backward(temp);
    if (browse)
        browse->output = temp->input;
    else
        return (0);
    browse = find_command_forward(temp);
    if (browse)
        browse->input = temp->output;
    else
        return (0);
    return (1);
}

int setup_in_out(t_parsing *command_list)
{
    t_parsing *temp;

	temp = command_list;
    while (temp) 
	{
		if (ft_strcmp(temp->cmd[0], ">") == 1 || ft_strcmp(temp->cmd[0], ">>") == 1)
        {
			if (!handle_redirection_output(temp))
                return (0);
        } 
        else if (ft_strcmp(temp->cmd[0], "<") == 1 || ft_strcmp(temp->cmd[0], "<<") == 1)
        {
			if (!handle_redirection_input(temp))
                return (0);
        } 
        else if (ft_strcmp(temp->cmd[0], "|") == 1) 
        {
            if (!handle_pipe(temp))
                return (0);
        }
        temp = temp->next;
    }
    return (1);
}