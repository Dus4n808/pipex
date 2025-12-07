/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 17:35:10 by dufama            #+#    #+#             */
/*   Updated: 2025/12/07 17:51:42 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	read_from_here_doc(char *limiter, t_bonus *pipex)
{
	char	*line;
	int		pipefd[2];
	size_t	len;

	len = ft_strlen(limiter);
	safe_pipe(pipefd);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, len) == 0 && line[len] == '\n')
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipefd[1]);
		free(line);
	}
	close(pipefd[1]);
	pipex->fds.fd_in = pipefd[0];
}

int	open_out_bonus(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		perror("open");
	return (fd);
}

t_cmd	**init_all_cmd_here_doc(char **argv, int argc, char **envp, int mode)
{
	int		nb_cmd;
	t_cmd	**cmds;
	int		i;

	nb_cmd = argc - mode;
	cmds = malloc(sizeof(t_cmd *) * (nb_cmd + 1));
	if (!cmds)
		return (NULL);
	i = 0;
	while (i < nb_cmd)
	{
		cmds[i] = init_cmd(argv[i + 3], envp);
		i++;
	}
	cmds[i] = NULL;
	return (cmds);
}
