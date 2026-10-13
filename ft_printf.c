/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesci <fmesci@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 10:40:21 by fmesci            #+#    #+#             */
/*   Updated: 2026/10/13 12:35:54 by fmesci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(char const *format, ...)
{
	int		i;
	int		count;
	va_list	args;

	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i] != '\0')
	{
		if (format[i] != '%')
		{
			write (1, &format[i], 1);
			count++;
		}
		else if (format[i + 1] != '\0')
		{
			count += check_format(format[i + 1], &args);
			i++;
		}
		i++;
	}
	va_end(args);
	return (count);
}

int	check_format(char specifier, va_list *args)
{
	if (specifier == 'c')
		return (ft_print_char(va_arg(*args, int)));
	else if (specifier == 's')
		return (ft_print_str(va_arg(*args, char *)));
	else if (specifier == 'p')
		return (ft_print_ptr(va_arg(*args, void *)));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_print_nbr(va_arg(*args, int)));
	else if (specifier == 'u')
		return (ft_print_unsigned(va_arg(*args, unsigned int)));
	else if (specifier == 'x' || specifier == 'X')
		return (ft_print_hex(va_arg(*args, unsigned int), specifier));
	else if (specifier == '%')
		return (ft_print_char('%'));
	return (0);
}
