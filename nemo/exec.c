#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 1 || ft_strcmp(cmd, "cd") == 1 || ft_strcmp(cmd, "pwd") == 1 || ft_strcmp(cmd, "export") == 1 
		|| ft_strcmp(cmd, "unset") == 1 || ft_strcmp(cmd, "env") == 1 || ft_strcmp(cmd, "exit") == 1)
	{
		return (1);
	}
	return (0);
}
int	count_cmd(t_parsing *temp)
{
	int	i;

	i = 0;
	while (temp)
	{
		if (temp->type == 4)
			i++;
		temp = temp->next;
	}
	return (i);
}
void	do_dup(t_tools *tools, t_parsing *temp)
{
	if (temp->input != 0)
		dup2(temp->input, 0); // a secure
	if (temp->output != 0)
		dup2(temp->output, 1);
}
int	child_process(t_tools *tools, char **envp, t_parsing *temp, int	*process_id)
{

	(*process_id) = fork();
	if ((*process_id) == -1)
		ft_exit(tools, NULL, NULL);
	if ((*process_id) == 0)
	{
		printf("process id :%d\n", (*process_id));
		do_dup(tools, temp);
		if (temp->input != 0)
			close (temp->input);
		if (temp->output != 0)
			close (temp->output);
		if(is_builtin(temp->cmd[0]) == 0)
		{
			printf("avant exec cmd : %s \n", temp->cmd[0]);
			execve(temp->valid_path, temp->cmd, envp);

		}
	}
	return(0);
}
int exec(t_tools *tools, char **envp)
{
	char ** possible_path;
	t_parsing *temp;
	pid_t *process_ids;
	int	i;
	int status;
	int total_cmds = count_cmd(tools->list_cmd);

	temp = tools->list_cmd;
	possible_path = ft_split(find_path(envp), ':');
	if (!possible_path)
    	ft_exit(tools, NULL, NULL);													//reset ou exit ?
	while (temp)
	{
		if (temp->type == 4 && is_builtin(temp->cmd[0]) == 0)
		{
			temp->valid_path = find_valid_path(possible_path, temp->cmd, tools);		// est ce qu il y a besoin de free temp->cmd[0] avant de lui changer sa valeur ?
			printf("\nvalidpath : %s \n",temp->valid_path);
			if (temp->valid_path == NULL)
				ft_exit(tools, NULL, NULL);											//reset ou exit ?
		}
		temp = temp->next;
	}
	temp = tools->list_cmd; //obsolete ?
	i = 0;
	process_ids = malloc(total_cmds * sizeof(pid_t));							// comment gerer le free besoin d 'ajouter dans tool ??
	temp = tools->list_cmd; //obsolete ?
	if (process_ids == NULL) 
		ft_exit(tools, NULL, NULL);													//reset ou exit ?
	while (temp)
	{
		 printf("Processing command: %s\n", temp->cmd[0]);
		if (temp->type == 4)
		{
			child_process(tools, envp, temp, &process_ids[i]);
			i++;
			printf("\ncmd : %s    number : %d\n",temp->cmd[0], i);
		}
		temp = temp->next;
	}
	i = 0;
	while (i < total_cmds)
	{
		if (waitpid(process_ids[i], &status, 0) == -1)
			ft_exit(tools, NULL, NULL);
		i++;
	}
	return (0);
}