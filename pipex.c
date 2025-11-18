/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:08:45 by dufama            #+#    #+#             */
/*   Updated: 2025/11/18 12:46:49 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	pipe_fd[2];
	int	i;
	pid_t	pid;
	t_data pipex;

	if (check_input(argc))
		exit (1);
	init_struct(&pipex, argc, argv);
	i = 0;
	pipex.prev_fd = pipex.infile_fd;
	while (i < pipex.nb_cmd)
	{
		if (i < pipex.nb_cmd - 1)
			pipe(pipe_fd);
		pid = fork();
		if (pid == 0)
			run_child(&pipex, pipe_fd, envp, i);
		clean_parent(&pipex, pipe_fd, i);
		i++;
	}
	while (waitpid(-1 , NULL, 0) > 0)
		;
	return (0);
}
