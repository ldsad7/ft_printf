/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 22:18:34 by tsimonis          #+#    #+#             */
/*   Updated: 2019/02/02 17:58:44 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		is_minus(int flags[11], char ls[3], char *res)
{
	int		ret;
	int		i;
	int		len;

	len = ft_strlen(res);
	ret = 0;
	ret += add_0x(flags, ls, res);
	i = -1;
	while (++i < flags[8] - len)
		ret += write(1, "0", 1);
	if (!(flags[10] && !ft_strcmp(res, "0") && !flags[8]))
		ret += write(1, res, len);
	else if (flags[7] || ft_strcmp(res, "0"))
		ret += write(1, " ", 1);
	i = -1;
	while (++i < flags[7] - (2 * flags[3] * (flags[3] && ft_strcmp(res, "0"))
			+ len + (flags[8] - len) * (flags[8] > len)
			* (!(flags[10] && !flags[8] && !ft_strcmp(res, "0")))))
		ret += write(1, " ", 1);
	return (ret);
}

static int		is_dot(int flags[11], char ls[3], char *res)
{
	int		i;
	int		len;
	int		ret;

	ret = 0;
	len = ft_strlen(res);
	i = -1;
	while (++i < flags[7] - (2 * flags[3] * (flags[3] && ft_strcmp(res, "0"))
			+ len + (flags[8] - len) * (flags[8] > len))
			* (!(flags[10] && !flags[8] && !ft_strcmp(res, "0"))))
		ret += write(1, " ", 1);
	ret += add_0x(flags, ls, res);
	i = -1;
	while (++i < flags[8] - len)
		ret += write(1, "0", 1);
	return (ret);
}

static int		no_dot(int flags[11], char ls[3], char *res)
{
	int		ret;
	int		i;
	int		len;
	char	fill;

	len = ft_strlen(res);
	ret = 0;
	if (flags[6])
		fill = '0';
	else
		fill = ' ';
	if (fill == '0')
		ret += add_0x(flags, ls, res);
	i = -1;
	while (++i < flags[7] - (len + 2 * flags[3]
			* (flags[3] && ft_strcmp(res, "0")))
			* (!(flags[10] && !flags[8] && !ft_strcmp(res, "0"))))
		ret += write(1, &fill, 1);
	if (fill == ' ')
		ret += add_0x(flags, ls, res);
	return (ret);
}

static int		no_minus(int flags[11], char ls[3], char *res)
{
	int		ret;

	ret = 0;
	if (flags[10])
		ret += is_dot(flags, ls, res);
	else
		ret += no_dot(flags, ls, res);
	if (!(flags[10] && !flags[8] && !ft_strcmp(res, "0")))
		ret += write(1, res, ft_strlen(res));
	return (ret);
}

int				print_int_hex(va_list ap, char ls[3], int flags[11])
{
	unsigned long long int	c;
	char					*res;
	int						ret;
	char					*str;

	if (ls[0] == 'l' || ls[0] == 'j' || ls[0] == 'z' || ls[0] == 't')
		c = va_arg(ap, unsigned long long int);
	else if (ls[0] == 'h' && ls[1] == 'h')
		c = (unsigned char)va_arg(ap, int);
	else if (ls[0] == 'h')
		c = (unsigned short int)va_arg(ap, int);
	else
		c = va_arg(ap, unsigned int);
	str = ft_itoa_unsigned_long(c);
	res = change_base(str, 10, 16, (ls[2] == 'x'));
	if (!(ret = 0) && flags[2])
		ret += is_minus(flags, ls, res);
	else
		ret += no_minus(flags, ls, res);
	ft_strdel(&str);
	ft_strdel(&res);
	return (ret);
}
