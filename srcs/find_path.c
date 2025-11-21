/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:05:20 by dufama            #+#    #+#             */
/*   Updated: 2025/11/21 12:42:47 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*find_path(char **envp)
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
	if (!path_split)
		free_tab(path_split);
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
	free_tab(path_split);
	return (NULL);
}

void	check_if_is_absolue(char **args, char **envp)
{
	if (ft_strchr(args[0], '/'))
	{
		if (access(args[0], X_OK) == 0)
			execve(args[0], args, envp);
		else
		{
			ft_putstr_fd("pipex: command not found", 2);
			ft_putstr_fd(args[0], 2);
			ft_putstr_fd("\n", 2);
			free_tab(args);
			exit (1);
		}
	}
}

void	check_empty_cmd(char **args)
{
	if (!args[0] || args[0][0] == '\0')
	{
		ft_putstr_fd("pipex: empty command", 2);
		ft_putstr_fd("\n", 2);
		free_tab(args);
		exit (1);
	}
}

void	execute_cmd(char *cmd, char **envp)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (!args)
		exit(1);
	check_empty_cmd(args);
	check_if_is_absolue(args, envp);
	path = find_cmd(args[0], envp);
	if (!path)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd("\n", 2);
		free_tab(args);
		exit(1);
	}
	execve(path, args, envp);
	exit (1);
}
