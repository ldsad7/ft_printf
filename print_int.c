/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 22:16:17 by tsimonis          #+#    #+#             */
/*   Updated: 2019/02/02 02:24:49 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		positive_order(int big_num, char *tmp, int flags[11], int num)
{
	int		i;
	int		ret;

	i = -1;
	ret = 0;
	while (flags[10] && ++i < big_num)
		ret += write(1, " ", 1);
	if (tmp[0] == '-')
		ret += write(1, "-", 1);
	else if (flags[1])
		ret += write(1, "+", 1);
	else if (flags[0])
		ret += write(1, " ", 1);
	if ((i = -1) && !flags[10])
		while (++i < big_num)
			ret += write(1, "0", 1);
	if (flags[8] > num - (tmp[0] == '-') && (i = -1))
		while (++i < flags[8] - (num - (tmp[0] == '-')))
			ret += write(1, "0", 1);
	if (!(flags[10] && !ft_strcmp(tmp, "0") && !flags[8]))
		ret += write(1, tmp + (tmp[0] == '-'),
				ft_strlen(tmp + (tmp[0] == '-')));
	else if (flags[7] || ft_strcmp(tmp, "0"))
		ret += write(1, " ", 1);
	return (ret);
}

static int		negative_order(int big_num, char *tmp, int flags[11], int num)
{
	int		i;
	int		ret;

	i = -1;
	ret = 0;
	if (tmp[0] == '-')
		ret += write(1, "-", 1);
	else if (flags[1])
		ret += write(1, "+", 1);
	else if (flags[0])
		ret += write(1, " ", 1);
	i = -1;
	if (flags[8] > num - (tmp[0] == '-'))
		while (++i < flags[8] - (num - (tmp[0] == '-')))
			ret += write(1, "0", 1);
	if (!(flags[10] && !ft_strcmp(tmp, "0") && !flags[8]))
		ret += write(1, tmp + (tmp[0] == '-'),
				ft_strlen(tmp + (tmp[0] == '-')));
	else if (flags[7] || ft_strcmp(tmp, "0"))
		ret += write(1, " ", 1);
	i = -1;
	while (++i < big_num)
		ret += write(1, " ", 1);
	return (ret);
}

static int		null_left_space(char *tmp, int flags[11], int num, int order)
{
	int		ret;
	int		i;
	int		fl;
	int		big_num;

	ret = 0;
	fl = (tmp[0] == '-' || flags[1] || flags[0]);
	i = -1;
	big_num = num + fl - (tmp[0] == '-') + (flags[8] > num - (tmp[0] == '-'))
		* (flags[8] - (num - (tmp[0] == '-')));
	big_num = flags[7] - big_num;
	if (order > 0)
		ret += positive_order(big_num, tmp, flags, num);
	else
		ret += negative_order(big_num, tmp, flags, num);
	return (ret);
}

static int		right_space(char *tmp, int flags[11], int num)
{
	int		ret;
	int		i;
	int		fl;
	int		big_num;
	char	sign;

	ret = 0;
	if ((fl = 1) && !(flags[0] && !(flags[8] > num - (tmp[0] == '-'))))
		fl--;
	if (!(sign = 0) && tmp[0] == '-')
		sign = '-';
	else if (flags[1])
		sign = '+';
	else if (flags[0])
		sign += ' ';
	big_num = num + fl * (!sign) - (tmp[0] == '-') + (sign > 0) +
	(flags[8] > num - (tmp[0] == '-')) * (flags[8] - (num - (tmp[0] == '-')));
	big_num = flags[7] - big_num;
	if (flags[10] && !flags[8] && tmp[0] == '0')
		big_num++;
	i = -1;
	while (++i < big_num)
		ret += write(1, " ", 1);
	return (ret + print_end(sign, num, tmp, flags));
}

int				print_int(va_list ap, char ls[3], int flags[11])
{
	long long int	c;
	int				ret;
	int				num;
	char			*tmp;

	if (ls[2] == 'D' || ls[0] == 'l' || ls[0] == 'j'
			|| ls[0] == 'z' || ls[0] == 't')
		c = va_arg(ap, long long int);
	else if (ls[0] == 'h' && ls[1] == 'h')
		c = (char)va_arg(ap, int);
	else if (ls[0] == 'h')
		c = (short int)va_arg(ap, int);
	else
		c = va_arg(ap, int);
	tmp = ft_itoa_long(c);
	num = ft_strlen(tmp);
	if (flags[6])
		ret = null_left_space(tmp, flags, num, 1);
	else if (flags[2])
		ret = null_left_space(tmp, flags, num, -1);
	else
		ret = right_space(tmp, flags, num);
	ft_strdel(&tmp);
	return (ret);
}
