/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdurgan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 17:19:34 by sdurgan           #+#    #+#             */
/*   Updated: 2019/02/02 14:42:19 by sdurgan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				put_lost_nul(int length, char *tail)
{
	int	nuls;
	int	ret;

	ret = 0;
	if (ft_strlen(tail) == 1 && length == 1)
		return (0);
	if (length + 1 > (int)(ft_strlen(tail) && ft_strcmp(tail, "0")))
	{
		nuls = length + 1 - ft_strlen(tail);
		while (nuls)
		{
			ret += write(1, "0", 1);
			nuls--;
		}
	}
	return (ret);
}

int				put_spaces(double num, int flags[11])
{
	int		ret;

	ret = 0;
	if (flags[6] && flags[7] > 0)
	{
		ret += flags[1] && num >= 0 ? write(1, "+", 1) : 0;
		ret += num < 0 ? write(1, "-", 1) : 0;
		while (--flags[7] != -1)
			ret += write(1, "0", 1);
	}
	else if (flags[7] > 0)
	{
		while (--flags[7] != -1)
			ret += write(1, " ", 1);
		ret += flags[1] && num >= 0 ? write(1, "+", 1) : 0;
		ret += num < 0 ? write(1, "-", 1) : 0;
	}
	return (ret);
}

static int		print_e(double num, char up, int nul_l[2], int flags[11])
{
	int		i;
	double	sign;
	int		ret;

	if (!(i = 0) && nan_inf(num, up))
		return (write(1, nan_inf(num, up), ft_strlen(nan_inf(num, up))));
	sign = num < 0 ? -1 : 1;
	num = num < 0 ? -num : num;
	if ((unsigned long long)num > 0 || nul_l[1] == 0)
	{
		while ((unsigned long long)num / 10 != 0 && ++i)
			num /= 10;
	}
	else
	{
		while ((unsigned long long)num % 10 == 0
				&& (unsigned long long)(num * 10) != 9 && --i)
			num *= 10;
	}
	ret = print_float(num * sign, nul_l, up, flags);
	return (ret += convert_e(up, i, nul_l, flags));
}

static int		print_g(double num, char up, int l, int flags[11])
{
	char	*head;
	double	copy;
	int		len;
	int		nul_l[2];

	if (nan_inf(num, up))
		return (write(1, nan_inf(num, up), ft_strlen(nan_inf(num, up))));
	copy = num;
	num = num < 0 ? -num : num;
	head = ft_itoa_unsigned_long((unsigned long long)num);
	nul_l[0] = 1;
	len = ft_strlen(head);
	ft_strdel(&head);
	if (flags[10] && l - 1 < 0 && !(nul_l[1] = 0))
		return (up == 'g') ? print_e(copy, 'e', nul_l, flags) : print_e(copy,
				'E', nul_l, flags);
	else if (len > 6 && (nul_l[1] == l - 1))
		return (up == 'g') ? print_e(copy, 'e', nul_l, flags) : print_e(copy,
				'E', nul_l, flags);
	else
	{
		nul_l[1] = l - len;
		return (print_float(copy, nul_l, up, flags));
	}
}

int				print_double(va_list ap, char ls[3], int flags[11])
{
	double	num;
	int		ret;
	int		nul_l[2];

	num = (ls[0] == 'L' && !ls[1]) ? va_arg(ap, long double)
		: va_arg(ap, double);
	if (nan_inf(num, ls[2]))
		return (write(1, nan_inf(num, ls[2]), ft_strlen(nan_inf(num, ls[2]))));
	nul_l[1] = flags[10] ? flags[8] : 6;
	nul_l[0] = 0;
	if (ls[2] == 'F' || ls[2] == 'f')
		ret = print_float(num, nul_l, ls[2], flags);
	else if (ls[2] == 'e' || ls[2] == 'E')
		ret = print_e(num, ls[2], nul_l, flags);
	else if (ls[2] == 'g' || ls[2] == 'G')
		ret = print_g(num, ls[2], nul_l[1], flags);
	else
		ret = -1;
	if (flags[2] && flags[7] > ret && (flags[7] -= ret))
	{
		while (--flags[7] != -1)
			ret += write(1, " ", 1);
	}
	return (ret);
}
