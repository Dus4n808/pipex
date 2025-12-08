/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 17:17:40 by dufama            #+#    #+#             */
/*   Updated: 2025/12/08 15:42:27 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	clean_exit_b(t_bonus *pipex, int code)
{
	if (pipex->fds.pipe_fd[0] != -1)
		close(pipex->fds.pipe_fd[0]);
	if (pipex->fds.pipe_fd[1] != -1)
		close(pipex->fds.pipe_fd[1]);
	if (pipex->fds.prev_fd != -1)
		close(pipex->fds.prev_fd);
	if (pipex->fds.fd_in != -1)
		close(pipex->fds.fd_in);
	if (pipex->fds.fd_out != -1)
		close(pipex->fds.fd_out);
	if (pipex->fds.input != -1)
		close(pipex->fds.input);
	if (pipex->fds.output != -1)
		close(pipex->fds.output);
	free_all_cmd(pipex->cmds);
	exit(code);
}

void	clean_struct(t_bonus *pipex)
{
	pipex->nb_cmd = 0;
	pipex->cmds = NULL;
	pipex->fds.input = -1;
	pipex->fds.output = -1;
	pipex->fds.fd_in = -1;
	pipex->fds.fd_out = -1;
	pipex->fds.pipe_fd[0] = -1;
	pipex->fds.pipe_fd[1] = -1;
	pipex->fds.prev_fd = -1;
	pipex->here_doc = 0;
}
