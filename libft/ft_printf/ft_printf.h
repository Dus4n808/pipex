/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:46:02 by dufama            #+#    #+#             */
/*   Updated: 2025/10/09 11:58:26 by dufama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

int	ft_putchar_printf(char c);
int	ft_putstr_printf(char *s);
int	ft_printf(const char *str, ...);
int	ft_check_args(va_list *args, char c);
int	ft_putnbr_printf(long nb);
int	ft_putnbr_hex(unsigned long nb);
int	ft_putnbr_hex_maj(unsigned long nb);
int	ft_putnbr_unsigned(unsigned long nb);
int	ft_print_pointer(void *ptr);

#endif
