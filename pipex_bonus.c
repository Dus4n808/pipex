/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:09:38 by dufama            #+#    #+#             */
/*   Updated: 2025/12/07 17:56:38 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	clean_struct(t_bonus *pipex)
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

static void	init_struct(int argc, char **argv, t_bonus *pipex, char **envp)
{
	if (ft_strncmp("here_doc", argv[1], 9) == 0)
		pipex->here_doc = 1;
	if (pipex->here_doc == 0)
	{
		pipex->nb_cmd = argc - NO_BONUS;
		pipex->cmds = init_all_cmd(argv, argc, envp, NO_BONUS);
		pipex->fds.fd_in = open_inflile(argv[1]);
		pipex->fds.fd_out = open_outfile(argv[argc - 1]);
	}
	else if (pipex->here_doc == 1)
	{
		pipex->nb_cmd = argc - BONUS;
		pipex->cmds = init_all_cmd_here_doc(argv, argc, envp, BONUS);
		read_from_here_doc(argv[2], pipex);
		pipex->fds.fd_out = open_out_bonus(argv[argc -1]);
	}
}

static void	parent_process(t_bonus *pipex, int i)
{
	close(pipex->fds.prev_fd);
	if (i < pipex->nb_cmd -1)
	{
		close(pipex->fds.pipe_fd[1]);
		pipex->fds.prev_fd = pipex->fds.pipe_fd[0];
	}
}

static void	wait_children(t_bonus *pipex)
{
	close(pipex->fds.fd_out);
	while (wait(NULL) > 0)
		;
	free_all_cmd(pipex->cmds);
}

int	main(int argc, char **argv, char **envp)
{
	t_bonus pipex;
	int		i;
	pid_t	pid;

	clean_struct(&pipex);
	init_struct(argc, argv, &pipex, envp);
	pipex.fds.prev_fd = pipex.fds.fd_in;
	i = 0;
	while (i < pipex.nb_cmd)
	{
		if (i < pipex.nb_cmd - 1)
			safe_pipe(pipex.fds.pipe_fd);
		pid = safe_fork();
		if (pid == 0)
			child_process_bonus(&pipex, i, envp);
		parent_process(&pipex, i);
		i++;
	}
	wait_children(&pipex);
	return (0);
}
