/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:50:19 by dufama            #+#    #+#             */
/*   Updated: 2025/12/02 12:40:21 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	error_cmd_not_found(char *cmd, char **tab_to_free)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	if (tab_to_free)
		free_tab(tab_to_free);
}

void	clean_exit(t_pipex *pipex, int code)
{
	if (pipex->cmds)
		free_all_cmd(pipex->cmds);
	if (pipex->fds.fd_in > 0)
		close(pipex->fds.fd_in);
	if (pipex->fds.fd_out > 0)
		close(pipex->fds.fd_out);
	if (pipex->fds.pipe_fd[0] > 0)
		close(pipex->fds.pipe_fd[0]);
	if (pipex->fds.pipe_fd[1] > 0)
		close(pipex->fds.pipe_fd[1]);
	exit(code);
}
