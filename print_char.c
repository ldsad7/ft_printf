/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 22:11:42 by tsimonis          #+#    #+#             */
/*   Updated: 2019/02/02 02:23:29 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		is_minus(char ls[3], int flags[11], long long int c)
{
	int		ret;
	int		i;
	int		len;

	ret = 0;
	if ((ls[0] == 'l' && !ls[1]) || (ls[2] == 'C'))
		ret += ft_putchar_unicode(c);
	else
		ret += write(1, &c, 1);
	len = ret;
	if (flags[7] > len)
	{
		i = -1;
		while (++i < flags[7] - len)
			ret += write(1, " ", 1);
	}
	return (ret);
}

static int		no_minus(char ls[3], int flags[11], long long int c)
{
	int		ret;
	int		i;
	char	fill;
	int		len;

	ret = 0;
	if (flags[6])
		fill = '0';
	else
		fill = ' ';
	len = num_of_bytes(c);
	if (flags[7] > len)
	{
		i = -1;
		while (++i < flags[7] - len)
			ret += write(1, &fill, 1);
	}
	if ((ls[0] == 'l' && !ls[1]) || (ls[2] == 'C'))
		ret += ft_putchar_unicode(c);
	else
		ret += write(1, &c, 1);
	return (ret);
}

int				print_char(va_list ap, char ls[3], int flags[11])
{
	int		ret;
	wchar_t	c;

	c = va_arg(ap, long long int);
	if (flags[2])
		ret = is_minus(ls, flags, c);
	else
		ret = no_minus(ls, flags, c);
	return (ret);
}
