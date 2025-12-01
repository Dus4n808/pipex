/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:57:02 by dufama            #+#    #+#             */
/*   Updated: 2025/12/01 11:59:21 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_cmd	**init_all_cmd(char **argv, int argc, char **envp)
{
	int		nb_cmd;
	t_cmd	**cmds;
	int		i;

	nb_cmd = argc - 3;
	cmds = malloc(sizeof(t_cmd *) * (nb_cmd + 1));
	i = 0;
	while (i < nb_cmd)
	{
		cmds[i] = init_cmd(argv[i + 2], envp);
		i++;
	}
	cmds[i] = NULL;
	return (cmds);
}
