/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesci <fmesci@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 10:38:40 by fmesci            #+#    #+#             */
/*   Updated: 2026/10/13 12:31:39 by fmesci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(char const *format, ...);
void	ft_putchar(char c);
int		ft_print_char(char c);
int		ft_print_str(char *s);
int		ft_print_nbr(int n);
int		ft_print_unsigned(unsigned int n);
int		ft_print_hex(unsigned int n, char specifier);
int		ft_print_ptr(void *ptr);
int		check_format(char specifier, va_list *args);

#endif
