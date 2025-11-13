/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:51:52 by dufama            #+#    #+#             */
/*   Updated: 2025/10/28 16:23:00 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putnbr_unsigned(unsigned long nb)
{
	int				i;

	i = 0;
	if (nb < 10)
		i += ft_putchar_printf(nb + '0');
	else
	{
		i += ft_putnbr_unsigned(nb / 10);
		i += ft_putnbr_unsigned(nb % 10);
	}
	return (i);
}

int	ft_print_pointer(void *ptr)
{
	int	i;

	if (!ptr)
		return (write(1, "(nil)", 5));
	i = write(1, "0x", 2);
	i += ft_putnbr_hex((unsigned long)ptr);
	return (i);
}
