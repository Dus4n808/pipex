/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:41:08 by dufama            #+#    #+#             */
/*   Updated: 2025/11/26 00:00:02 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_infile(char *file)
{
	int	fd_file;

	fd_file = open(file, O_RDONLY);
	if (fd_file < 0)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		exit(1);
	}
	return (fd_file);
}

int	open_outfile(char *file)
{
	int	fd_outfile;

	fd_outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_outfile < 0)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		exit(1);
	}
	return (fd_outfile);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	close_all_fds_except_std(int fd1, int fd2, int fd3)
{
	int	max_fd;
	int	fd;

	max_fd = 1024;
	fd = 3;
	while (fd < max_fd)
	{
		if (fd != fd1 && fd != fd2 && fd != fd3)
			close(fd);
		fd++;
	}
}
