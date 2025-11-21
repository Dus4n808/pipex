/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:08:45 by dufama            #+#    #+#             */
/*   Updated: 2025/11/21 12:42:30 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	security_check_pipe(int process)
{
	if (process == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(1);
	}
}

static int	security_check_fork(int process)
{
	if (process == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(1);
	}
	return (process);
}

int	read_from_here_doc(char *limiter)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(1);
	}
	while (1)
	{
		ft_putchar_fd('>', 1);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	int		i;
	pid_t	pid;
	t_data	pipex;

	if (check_input(argc))
		exit (1);
	init_struct(&pipex, argc, argv);
	i = 0;
	pipex.prev_fd = pipex.infile_fd;
	while (i < pipex.nb_cmd)
	{
		if (i < pipex.nb_cmd - 1)
			security_check_pipe(pipe(pipe_fd));
		pid = security_check_fork(fork());
		if (pid == 0)
			run_child(&pipex, pipe_fd, envp, i);
		clean_parent(&pipex, pipe_fd, i);
		i++;
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	close(pipex.outfile_fd);
	return (0);
}
