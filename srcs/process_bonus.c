/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 17:14:51 by dufama            #+#    #+#             */
/*   Updated: 2025/12/07 17:16:57 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	close_unused_fds(t_bonus *pipex)
{
	if (pipex->fds.pipe_fd[0] != -1 && pipex->fds.pipe_fd[0] != pipex->fds.input)
		close(pipex->fds.pipe_fd[0]);
	if (pipex->fds.pipe_fd[1] != -1 && pipex->fds.pipe_fd[1] != pipex->fds.output)
		close(pipex->fds.pipe_fd[1]);
	if (pipex->fds.fd_in != -1 && pipex->fds.fd_in != pipex->fds.input)
		close(pipex->fds.fd_in);
	if (pipex->fds.fd_out != -1 && pipex->fds.fd_out != pipex->fds.output)
		close(pipex->fds.fd_out);
}

void	set_in_out_bonus(t_bonus *pipex, int index)
{
	pipex->fds.input = pipex->fds.prev_fd;
	if (index == pipex->nb_cmd -1)
		pipex->fds.output = pipex->fds.fd_out;
	else
		pipex->fds.output = pipex->fds.pipe_fd[1];
}

void	child_process_bonus(t_bonus *pipex, int index, char **envp)
{
	t_cmd	*cmd;

	cmd = pipex->cmds[index];
	set_in_out_bonus(pipex, index);
	close_unused_fds(pipex);
	if (!cmd || !cmd->path)
	{
		if (cmd && cmd->args && cmd->args[0])
			error_cmd_not_found(cmd->args[0], NULL);
		clean_exit_b(pipex, 127);
	}
	if (pipex->fds.input < 0 || pipex->fds.output < 0)
		clean_exit_b(pipex, 1);
	safe_dup(pipex->fds.input, STDIN_FILENO);
	safe_dup(pipex->fds.output, STDOUT_FILENO);
	close(pipex->fds.input);
	close(pipex->fds.output);
	execve(cmd->path, cmd->args, envp);
	perror("execve");
	clean_exit_b(pipex, EXIT_FAILURE);
}
