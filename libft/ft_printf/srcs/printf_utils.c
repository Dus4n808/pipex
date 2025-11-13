/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:20:49 by dufama            #+#    #+#             */
/*   Updated: 2025/10/28 16:23:07 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putchar_printf(char c)
{
	return (write (1, &c, 1));
}

int	ft_putstr_printf(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (s[i])
		write(1, &s[i++], 1);
	return (i);
}

int	ft_putnbr_printf(long nb)
{
	int		i;

	i = 0;
	if (nb < 0)
	{
		i = ft_putchar_printf('-');
		nb *= -1;
	}
	if (nb <= 9)
		i += ft_putchar_printf(nb + '0');
	else
	{
		i += ft_putnbr_printf(nb / 10);
		i += ft_putnbr_printf(nb % 10);
	}
	return (i);
}

int	ft_putnbr_hex(unsigned long nb)
{
	int		i;
	char	*tab;

	tab = "0123456789abcdef";
	i = 0;
	if (nb < 16)
		i += ft_putchar_printf(tab[nb]);
	else
	{
		i += ft_putnbr_hex(nb / 16);
		i += ft_putnbr_hex(nb % 16);
	}
	return (i);
}

int	ft_putnbr_hex_maj(unsigned long nb)
{
	int			i;
	char		*tab;

	tab = "0123456789ABCDEF";
	i = 0;
	if (nb < 16)
		i += ft_putchar_printf(tab[nb]);
	else
	{
		i += ft_putnbr_hex_maj(nb / 16);
		i += ft_putnbr_hex_maj(nb % 16);
	}
	return (i);
}
