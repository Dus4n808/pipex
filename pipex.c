/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:08:45 by dufama            #+#    #+#             */
/*   Updated: 2025/11/14 13:32:26 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{

	// int id;

	if (argc != 2)
		return (0);
	// id = fork();
	// if (id != 0)
	// {
	// 	ft_printf("Je suis le proc parent\n");
	// }
	// else if (id == 0)
	// {
	// 	ft_printf("je suis l'enfant\n");
	// }
	// int i = 0;
	// // if (id != 0)
	// // 	wait(NULL);
	// if (id == 0)
	// {
	// 	for (i = 0; i < 10; i++)
	// 		ft_printf("enfant :%d\n", i);
	// }
	// else
	// {
	// 	for (i = 0; i < 10; i++)
	// 		ft_printf("parent :%d\n", i);

	// }
	char *path;
	path = ft_strjoin("/bin/", argv[1]);
	execve("/bin/", &argv[1], envp);

	return (0);
}
