/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesci <fmesci@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 13:49:03 by fmesci            #+#    #+#             */
/*   Updated: 2026/10/13 12:30:43 by fmesci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex(unsigned int n, char specifier)
{
	int		count;
	char	*base;

	count = 0;
	if (specifier == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (n >= 16)
	{
		count += ft_print_hex(n / 16, specifier);
	}
	ft_putchar(base[n % 16]);
	count++;
	return (count);
}

static int	ft_putptr_hex(unsigned long n)
{
	char	*base;
	int		count;

	count = 0;
	base = "0123456789abcdef";
	if (n >= 16)
	{
		count += ft_putptr_hex(n / 16);
	}
	ft_putchar(base[n % 16]);
	count++;
	return (count);
}

int	ft_print_ptr(void *ptr)
{
	int	count;

	count = 0;
	if (ptr == NULL)
		return (ft_print_str("(nil)"));
	count = ft_print_str("0x");
	count += ft_putptr_hex((unsigned long)ptr);
	return (count);
}
