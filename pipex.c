/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:25:05 by dufama            #+#    #+#             */
/*   Updated: 2025/12/01 14:44:46 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_input(int argc)
{
	if (argc !=  5)
	{
		ft_putstr_fd("Pipex: Usage infile cmd1 cmd2 outfile\n", 2);
		exit(EXIT_FAILURE);
	}
}


int	main(int argc, char **argv, char **envp)
{
	t_cmd	**cmds;
	check_input(argc);
	cmds = init_all_cmd(argv, argc, envp);
	int i = 0;
	while (cmds[i])
	{
		printf("---- Command %d ----\n", i);

		printf("PATH: %s\n", cmds[i]->path);

		int j = 0;
		while (cmds[i]->args[j])
		{
			printf("ARG[%d] : %s\n", j, cmds[i]->args[j]);
			j++;
		}
		printf("\n");

		i++;
	}
	free_all_cmd(cmds);
	return (0);
}
