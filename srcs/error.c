/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:50:19 by dufama            #+#    #+#             */
/*   Updated: 2025/12/01 11:20:07 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	error_cmd_not_found(char *cmd, char **tab_to_free)
{
	ft_putstr_fd("pipex : command not found ", 2);
	ft_putstr_fd(cmd, 2);
	free_tab(tab_to_free);
	exit(127);
}
