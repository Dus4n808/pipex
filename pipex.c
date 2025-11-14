/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:08:45 by dufama            #+#    #+#             */
/*   Updated: 2025/11/14 15:35:56 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(void)
{
	printf("Child\n");
}

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

int	main(int argc, char **argv, char **envp)
{

	if (argc != 2)
		return (0);
	char *path;
	char *cmd;

	char **args = ft_split(argv[1], ' ');

	cmd = args[0];

	path = find_cmd(cmd, envp);

	// int id = fork();
	// if (id == 0)
	// 	child_process();
	// else
	// 	parent_processe();

	// char *path;
	// path = ft_strjoin("/bin/", argv[1]);
	execve(path, args, envp);
	printf("%s\n", path);
	return (0);
}
