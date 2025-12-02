/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:25:42 by dufama            #+#    #+#             */
/*   Updated: 2025/12/02 11:57:37 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// find the path /opt/bin/:/system/ etc
static char *find_env(char **envp)
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
//build the path /opt/bin/
//return a tab
static	char **build_path(char **envp)
{
	char	*env;
	char	*tmp;
	char	**path_env;
	int		i;

	env = find_env(envp);
	if (!env)
		return (NULL);
	path_env = ft_split(env, ':');
	if (!path_env)
		return (NULL);
	i = 0;
	while (path_env[i])
	{
		tmp = ft_strjoin(path_env[i], "/");
		if (!tmp)
		{
			free_tab(path_env);
			return (NULL);
		}
		free(path_env[i]);
		path_env[i] = tmp;
		i++;
	}
	return (path_env);
}
//build tab with the command /opt/bin/ls
static char	**build_path_cmd(char *cmd, char **envp)
{
	char	**env;
	char	*tmp;
	int		i;

	env = build_path(envp);
	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		tmp = ft_strjoin(env[i], cmd);
		if (!tmp)
		{
			free_tab(env);
			return (NULL);
		}
		free(env[i]);
		env[i] = tmp;
		i++;
	}
	return (env);
}
//try the path wuith access /opt/bin/ls return the real path
char	*get_path(char *cmd, char **envp)
{
	char	**env;
	char	*real_path;
	int		i;

	env = build_path_cmd(cmd, envp);
	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (access(env[i], X_OK) == 0)
		{
			real_path = ft_strdup(env[i]);
			free_tab(env);
			return (real_path);
		}
		i++;
	}
	free_tab(env);
	return (NULL);
}
//init in the struct the real path
t_cmd	*init_cmd(char *cmd, char **envp)
{
	char	**cmd_path;
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	cmd_path = ft_split(cmd, ' ');
	if (!cmd_path)
	{
		free(new);
		return (NULL);
	}
	new->path = get_path(cmd_path[0], envp);
	new->args = cmd_path;
	return (new);
}
