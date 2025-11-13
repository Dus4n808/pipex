/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:08:45 by dufama            #+#    #+#             */
/*   Updated: 2025/11/12 17:38:53 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(void)
{
	int fd[2];
	pid_t id;

	if (pipe(fd) == -1)
	{
		ft_printf("Erreur lors de la création du pipe\n");
		return (1);
	}

	id = fork();
	if (id == -1)
	{
		ft_printf("Erreur lors du fork\n");
		return (1);
	}

	if (id == 0)
	{
		// Processus enfant
		close(fd[0]); // on ferme le côté lecture (inutile ici)
		int i = 42;
		write(fd[1], &i, sizeof(i)); // on écrit dans le pipe
		ft_printf("Enfant: j'ai envoyé %d au parent\n", i);
		close(fd[1]);
	}
	else
	{
		// Processus parent
		close(fd[1]); // on ferme le côté écriture (inutile ici)
		int received;
		read(fd[0], &received, sizeof(received)); // on lit depuis le pipe
		ft_printf("Parent: j'ai reçu %d de l'enfant\n", received);
		close(fd[0]);
		wait(NULL); // on attend la fin du fils
	}
	return (0);
}
