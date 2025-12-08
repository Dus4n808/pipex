/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:57:02 by dufama            #+#    #+#             */
/*   Updated: 2025/12/08 18:04:16 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static char	**trim_args(char **args)
{
	int		i;
	char	*tmp;

	i = 0;
	while (args[i])
	{
		tmp = ft_strtrim(args[i], "'");
		free(args[i]);
		args[i] = tmp;
		i++;
	}
	return (args);
}

//init in the struct the real path
t_cmd	*init_cmd(char *cmd, char **envp)
{
	char	**cmd_path;
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	if (!cmd || !cmd[0])
		return (check_empty(new));
	cmd_path = ft_split(cmd, ' ');
	if (!cmd_path || !cmd_path[0])
	{
		free(new);
		if (cmd_path)
			free(cmd_path);
		return (NULL);
	}
	cmd_path = trim_args(cmd_path);
	if (is_absolute(cmd_path[0]))
		new->path = ft_strdup(cmd_path[0]);
	else
		new->path = get_path(cmd_path[0], envp);
	new->args = cmd_path;
	return (new);
}

t_cmd	**init_all_cmd(char **argv, int argc, char **envp, int mode)
{
	int		nb_cmd;
	t_cmd	**cmds;
	int		i;

	nb_cmd = argc - mode;
	cmds = malloc(sizeof(t_cmd *) * (nb_cmd + 1));
	if (!cmds)
		return (NULL);
	i = 0;
	while (i < nb_cmd)
	{
		cmds[i] = init_cmd(argv[i + 2], envp);
		i++;
	}
	cmds[i] = NULL;
	return (cmds);
}

static void	set_input_output(t_pipex *pipex, int index)
{
	if (index == 0)
	{
		pipex->fds.input = pipex->fds.fd_in;
		pipex->fds.output = pipex->fds.pipe_fd[1];
	}
	else
	{
		pipex->fds.input = pipex->fds.pipe_fd[0];
		pipex->fds.output = pipex->fds.fd_out;
	}
}

void	child_process(t_pipex *pipex, int i, char **envp)
{
	t_cmd	*cmd;

	cmd = pipex->cmds[i];
	set_input_output(pipex, i);
	if (!cmd || !cmd->path)
	{
		if (cmd && cmd->args && cmd->args[0])
			error_cmd_not_found(cmd->args[0], NULL);
		clean_exit(pipex, 127);
	}
	if (pipex->fds.input < 0 || pipex->fds.output < 0)
		clean_exit(pipex, 1);
	safe_dup(pipex->fds.input, STDIN_FILENO);
	safe_dup(pipex->fds.output, STDOUT_FILENO);
	close(pipex->fds.input);
	close(pipex->fds.output);
	execve(cmd->path, cmd->args, envp);
	perror("execve");
	clean_exit(pipex, EXIT_FAILURE);
}
