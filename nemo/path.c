#include "minishell.h"

char	*try_full_path(t_tools *tools, char *og_path)
{
	char	*path;

	if (access(og_path, X_OK) == 0)
	{
		path = ft_strdup(og_path);
		if (!path)
			ft_exit(tools, NULL, NULL);
		return (path);
	}
	return (NULL);
}

int	is_path(char *str)
{
	if (str == NULL)
		return (0);
	if (ft_strlen(str) < 2)
		return (0);
	if (str[0] == '/')
		return (1);
	if (str[0] == '.' && str[1] == '/')
		return (1);
	return (0);
}

char	*find_valid_path(char **possible_path, char **current_cmd, t_tools *tools)
{
	int		i;
	char	*path;

	i = 0;
	if (current_cmd[0] == NULL)
		return (NULL);
	if (is_path(current_cmd[0]))
		return (try_full_path(tools, current_cmd[0]));
	while (possible_path[i])
	{
		path = ft_strjoin(possible_path[i], "/");
		path = ft_join_free_s1(path, current_cmd[0]); // est ce qu il y a besoin de free currentcmd ?
		if (!path)
			ft_exit(tools, NULL, NULL);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*find_path(char**envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}