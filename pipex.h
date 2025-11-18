/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:08:57 by dufama            #+#    #+#             */
/*   Updated: 2025/11/18 18:38:44 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "./libft/libft.h"
# include "sys/wait.h"
# include <errno.h>
# include <string.h>
# include <fcntl.h>

typedef struct s_data {
	char **argv;
	int	nb_cmd;
	int	infile_fd;
	int	outfile_fd;
	int	prev_fd;
	int	input;
	int	output;
	int	here_doc;
} t_data;

char	*find_path(char **envp);
char	*find_cmd(char *cmd, char **envp);
void	execute_cmd(char *cmd, char **envp);
int		open_infile(char *file);
int		open_outfile(char *file);
void	child_process(int input_fd, int output_fd, char *cmd, char **envp);
void	run_child(t_data *pipex, int pipe_fd[2], char **envp, int i);
void	init_struct(t_data *pipex, int argc, char **argv);
void	clean_parent(t_data *pipex, int pipe_fd[2], int i);
int		check_input(int argc);
void	check_if_is_absolue(char **args, char **envp);
void	free_tab(char **tab);
void	check_empty_cmd(char **args);

#endif
