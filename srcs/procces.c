/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procces.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:47:41 by dufama            #+#    #+#             */
/*   Updated: 2025/11/18 18:24:41 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int input_fd, int output_fd, char *cmd, char **envp)
{
	if (dup2(input_fd, STDIN_FILENO) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(1);
	}
	if (dup2(output_fd, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(1);
	}
	if (close(input_fd) == -1)
		ft_putstr_fd(strerror(errno), 2);
	if (close(output_fd) == -1)
		ft_putstr_fd(strerror(errno), 2);
	execute_cmd(cmd, envp);
	ft_putstr_fd("execve error: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	exit(1);
}

int	check_input(int argc)
{
	if (argc < 5)
	{
		ft_putstr_fd("Usage : ./pipex infile cm1 cm2 .... outfile\n", 2);
		return (1);
	}
	return (0);
}

void	init_struct(t_data *pipex, int argc, char **argv)
{
		pipex->nb_cmd = argc - 3;
		pipex->infile_fd = open_infile(argv[1]);
		pipex->outfile_fd = open_outfile(argv[argc - 1]);
		pipex->argv = argv;
}

void	run_child(t_data *pipex, int pipe_fd[2], char **envp, int i)
{
	pipex->input = pipex->prev_fd;
	if (i == pipex->nb_cmd - 1)
		pipex->output = pipex->outfile_fd;
	else
		pipex->output = pipe_fd[1];
	child_process(pipex->input, pipex->output, pipex->argv[2 + i], envp);
}

void	clean_parent(t_data *pipex, int pipe_fd[2], int i)
{
	close(pipex->prev_fd);
	if (i < pipex->nb_cmd - 1)
	{
		close(pipe_fd[1]);
		pipex->prev_fd = pipe_fd[0];
	}
}



