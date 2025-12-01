/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:25:05 by dufama            #+#    #+#             */
/*   Updated: 2025/12/01 11:57:32 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int	main(int argc, char **argv, char **envp)
{
	t_cmd	**cmds;
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
