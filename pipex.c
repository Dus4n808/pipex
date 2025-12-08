/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:25:05 by dufama            #+#    #+#             */
/*   Updated: 2025/12/08 17:51:40 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_input(int argc)
{
	if (argc != 5)
	{
		ft_putstr_fd("Pipex: Usage infile cmd1 cmd2 outfile\n", 2);
		exit(EXIT_FAILURE);
	}
}

static void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->cmds = init_all_cmd(argv, argc, envp, NO_BONUS);
	pipex->fds.fd_in = open_inflile(argv[1]);
	pipex->fds.fd_out = open_outfile(argv[4]);
	pipex->fds.prev_fd = -1;
}

static void	first_child(t_pipex *pipex, int index, char **envp)
{
	close(pipex->fds.pipe_fd[0]);
	child_process(pipex, index, envp);
}

static void	second_child(t_pipex *pipex, int index, char **envp)
{
	close(pipex->fds.pipe_fd[1]);
	child_process(pipex, index, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	pid_t	pid1;
	pid_t	pid2;

	check_input(argc);
	init_pipex(&pipex, argc, argv, envp);
	safe_pipe(pipex.fds.pipe_fd);
	pid1 = safe_fork();
	if (pid1 == 0)
		first_child(&pipex, 0, envp);
	pid2 = safe_fork();
	if (pid2 == 0)
		second_child(&pipex, 1, envp);
	close(pipex.fds.pipe_fd[0]);
	close(pipex.fds.pipe_fd[1]);
	close(pipex.fds.fd_in);
	close(pipex.fds.fd_out);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	free_all_cmd(pipex.cmds);
	return (0);
}
