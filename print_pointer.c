/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 22:14:07 by tsimonis          #+#    #+#             */
/*   Updated: 2019/02/02 16:41:15 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		is_minus(int flags[11], int len, char *prev)
{
	int		i;
	int		ret;

	ret = 0;
	ret += write(1, "0x", 2);
	i = -1;
	while (++i < flags[8] - len)
		ret += write(1, "0", 1);
	if (!(flags[10] && !flags[8] && !ft_strcmp(prev, "0")))
		ret += write(1, prev, len);
	else if (flags[7])
		ret += write(1, " ", 1);
	if (flags[7] > len + 2 + (flags[8] - len)
			* (flags[8] > len))
	{
		i = -1;
		while (++i < flags[7] - 2 - len
				- (flags[8] - len) * (flags[8] > len))
			ret += write(1, " ", 1);
	}
	return (ret);
}

static int		is_dot(int flags[11], int len, char *prev)
{
	char	fill;
	int		i;
	int		ret;

	ret = 0;
	fill = ' ';
	i = -1;
	while (++i < flags[7] - 2 - len *
	(!(!ft_strcmp(prev, "0") && flags[10] && !flags[8]))
			- (flags[8] - len) * (flags[8] > len))
		ret += write(1, &fill, 1);
	ret += write(1, "0x", 2);
	i = -1;
	while (++i < flags[8] - len)
		ret += write(1, "0", 1);
	return (ret);
}

static int		no_dot(int flags[11], int len, char *prev)
{
	char	fill;
	int		ret;
	int		i;

	ret = 0;
	if (flags[6])
		fill = '0';
	else
		fill = ' ';
	i = -1;
	if (fill == ' ')
		while (++i < flags[7] - 2 - len
				* (!(!ft_strcmp(prev, "0") && flags[10] && !flags[8])))
			ret += write(1, &fill, 1);
	ret += write(1, "0x", 2);
	if (fill == '0')
		while (++i < flags[7] - len - 2)
			ret += write(1, &fill, 1);
	return (ret);
}

int				print_pointer(va_list ap, int flags[11])
{
	char	*prev;
	int		ret;
	int		len;
	char	*str;

	ret = 0;
	str = ft_itoa_unsigned_long(va_arg(ap, unsigned long long));
	prev = change_base(str, 10, 16, 1);
	len = ft_strlen(prev);
	if (flags[2])
		ret += is_minus(flags, len, prev);
	else
	{
		if (flags[10])
			ret += is_dot(flags, len, prev);
		else
			ret += no_dot(flags, len, prev);
		if (!(!ft_strcmp(prev, "0") && flags[10] && !flags[8]))
			ret += write(1, prev, len);
	}
	ft_strdel(&prev);
	ft_strdel(&str);
	return (ret);
}
