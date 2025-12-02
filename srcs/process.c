/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:57:02 by dufama            #+#    #+#             */
/*   Updated: 2025/12/02 15:53:19 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_cmd	**init_all_cmd(char **argv, int argc, char **envp)
{
	int		nb_cmd;
	t_cmd	**cmds;
	int		i;

	nb_cmd = argc - 3;
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
