/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:08:57 by dufama            #+#    #+#             */
/*   Updated: 2025/12/01 12:11:31 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "./libft/libft.h"
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
#include <sys/types.h>

typedef struct s_cmd
{
	char	**args;
	char	*path;
} t_cmd	;

//utils
void	free_tab(char **tab);
void	error_cmd_not_found(char *cmd, char **tab_to_free);
void	free_cmd(t_cmd *cmd);
void	free_all_cmd(t_cmd **cmds);
pid_t	safe_fork(void);
void	safe_pipe(int *pipe_fd);
//path
char	*get_path(char *cmd, char **envp);
t_cmd	*init_cmd(char *cmd, char **envp);
//init
t_cmd	**init_all_cmd(char **argv, int argc, char **envp);
//open
int	open_outfile(char *filename);
int	open_inflile(char *filename);

#endif
