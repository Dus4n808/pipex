/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:05:20 by dufama            #+#    #+#             */
/*   Updated: 2025/11/17 15:36:15 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char *find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*find_cmd(char *cmd, char **envp)
{
	char	*path_env;
	char	**path_split;
	char	*tmp;
	char	*real_path;
	int		i;

	path_env = find_path(envp);
	if (!path_env)
		return (NULL);
	path_split = ft_split(path_env, ':');
	i = 0;
	while (path_split[i])
	{
		tmp = ft_strjoin(path_split[i], "/");
		real_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(real_path, X_OK) == 0)
			return (real_path);
		free(real_path);
		i++;
	}
	return (NULL);
}

void	execute_cmd(char *cmd, char **envp)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (!args || !args[0])
		exit(1);
	path = find_cmd(args[0], envp);
	if (!path)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
	execve(path, args, envp);
	exit (1);
}
