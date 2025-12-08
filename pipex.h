/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:08:57 by dufama            #+#    #+#             */
/*   Updated: 2025/12/08 17:49:43 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define NO_BONUS 3
# define BONUS 4
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "./libft/libft.h"
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>

typedef struct s_cmd
{
	char	**args;
	char	*path;
}	t_cmd;

typedef struct s_fds
{
	int	pipe_fd[2];
	int	fd_in;
	int	fd_out;
	int	input;
	int	output;
	int	prev_fd;
}	t_fds;

typedef struct s_pipex
{
	t_cmd	**cmds;
	t_fds	fds;
}	t_pipex;

typedef struct s_bonus
{
	t_cmd	**cmds;
	t_fds	fds;
	int		nb_cmd;
	int		here_doc;
}	t_bonus;

//utils
void	free_tab(char **tab);
void	error_cmd_not_found(char *cmd, char **tab_to_free);
void	free_cmd(t_cmd *cmd);
void	free_all_cmd(t_cmd **cmds);
pid_t	safe_fork(void);
void	safe_pipe(int *pipe_fd);
void	safe_dup(int oldfd, int newfd);
void	clean_exit(t_pipex *pipex, int code);
t_cmd	*check_empty(t_cmd *new);
//path
char	*get_path(char *cmd, char **envp);
int		is_absolute(char *cmd);
t_cmd	*init_cmd(char *cmd, char **envp);
//init
t_cmd	**init_all_cmd(char **argv, int argc, char **envp, int mode);
//open
int		open_outfile(char *filename);
int		open_inflile(char *filename);
//do
void	child_process(t_pipex *pipex, int i, char **envp);
//BONUS
void	clean_exit_b(t_bonus *pipex, int code);
void	child_process_bonus(t_bonus *pipex, int index, char **envp);
void	set_in_out_bonus(t_bonus *pipex, int index);
void	close_unused_fds(t_bonus *pipex);
void	read_from_here_doc(char *limiter, t_bonus *pipex);
int		open_out_bonus(char *filename);
t_cmd	**init_all_cmd_here_doc(char **argv, int argc, char **envp, int mode);
void	clean_struct(t_bonus *pipex);

#endif
