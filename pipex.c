/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:25:05 by dufama            #+#    #+#             */
/*   Updated: 2025/12/02 13:06:13 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	check_input(int argc)
{
	if (argc !=  5)
	{
		ft_putstr_fd("Pipex: Usage infile cmd1 cmd2 outfile\n", 2);
		exit(EXIT_FAILURE);
	}
}

// static void	first_child(t_pipex *pipex, char **envp)
// {
// 	close(pipex->fds.pipe_fd[0]);
// 	child_process(&);
// }

// static void	second_child(t_cmd *cmd, t_fds *fds, char **envp)
// {
// 	close(fds->pipe_fd[1]);
// 	child_process(cmd, fds->pipe_fd[0], fds->fd_out, envp);
// }

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	pid_t	pid1;
	pid_t	pid2;

	check_input(argc);
	pipex.cmds = init_all_cmd(argv, argc, envp);
	pipex.fds.fd_in = open_inflile(argv[1]);
	pipex.fds.fd_out = open_outfile(argv[4]);
	safe_pipe(pipex.fds.pipe_fd);
	pid1 = safe_fork();
	if (pid1 == 0)
	{
		close(pipex.fds.pipe_fd[0]);
		child_process(&pipex, 0, envp);
	}
	pid2 = safe_fork();
	if (pid2 == 0)
	{
		close(pipex.fds.pipe_fd[1]);
		child_process(&pipex, 1, envp);
	}
	close(pipex.fds.pipe_fd[0]);
	close(pipex.fds.pipe_fd[1]);
	close(pipex.fds.fd_in);
	close(pipex.fds.fd_out);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	free_all_cmd(pipex.cmds);
	return (0);
}
