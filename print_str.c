/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 22:15:00 by tsimonis          #+#    #+#             */
/*   Updated: 2019/02/02 15:45:23 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		wstr_rigth(wchar_t *wstr, int f[11], int ret)
{
	char	fill;
	int		i;
	int		tmp;

	fill = f[6] ? '0' : ' ';
	if (f[7] > (int)(ft_min(ft_strlen_wstr(wstr, f), f[8]) * f[10]
			+ ft_strlen_wstr(wstr, f) * (!(f[10]))))
	{
		i = -1;
		while (++i < (int)(f[7] - (ft_min(ft_strlen_wstr(wstr, f), f[8])
			* f[10] + ft_strlen_wstr(wstr, f) * (!(f[10])))))
			ret += write(1, &fill, 1);
	}
	i = 0;
	tmp = 0;
	if (f[10])
		while (wstr[i] && tmp + num_of_bytes(wstr[i]) <= f[8])
		{
			tmp += num_of_bytes(wstr[i]);
			ret += ft_putchar_unicode(wstr[i++]);
		}
	else
		while (wstr[i])
			ret += ft_putchar_unicode(wstr[i++]);
	return (ret);
}

static int		wstr_left(wchar_t *wstr, int f[11], int ret)
{
	int		i;

	i = 0;
	if (f[10])
		while (wstr[i] && ret + num_of_bytes(wstr[i]) <= f[8])
			ret += ft_putchar_unicode(wstr[i++]);
	else
		while (wstr[i])
			ret += ft_putchar_unicode(wstr[i++]);
	if (f[7] > (int)(ft_min(ft_strlen_wstr(wstr, f), f[8]) * f[10]
				+ ft_strlen_wstr(wstr, f) * (!(f[10]))))
	{
		i = -1;
		while (++i < (int)(f[7] - (ft_min(ft_strlen_wstr(wstr, f), f[8])
			* f[10] + ft_strlen_wstr(wstr, f) * (!(f[10])))))
			ret += write(1, " ", 1);
	}
	return (ret);
}

static int		str_rigth(char *str, int flags[11], int ret)
{
	char	fill;
	int		i;

	fill = (flags[6]) ? '0' : ' ';
	if (flags[7] > (int)(ft_min(ft_strlen(str), flags[8]) * flags[10]
			+ ft_strlen(str) * (!(flags[10]))))
	{
		i = -1;
		while (++i < (int)(flags[7] - (ft_min(ft_strlen(str), flags[8])
					* flags[10] + ft_strlen(str) * (!(flags[10])))))
			ret += write(1, &fill, 1);
	}
	i = 0;
	if (flags[10])
		while (str[i] && i < flags[8])
			ret += ft_putchar_unicode(str[i++]);
	else
		while (str[i])
			ret += ft_putchar_unicode(str[i++]);
	return (ret);
}

static int		str_left(char *str, int flags[11], int ret)
{
	int		i;

	i = 0;
	if (flags[10])
		while (str[i] && i < flags[8])
			ret += ft_putchar_unicode(str[i++]);
	else
		while (str[i])
			ret += ft_putchar_unicode(str[i++]);
	if (flags[7] > (int)(ft_min(ft_strlen(str), flags[8]) * flags[10]
			+ ft_strlen(str) * (!(flags[10]))))
	{
		i = -1;
		while (++i < (int)(flags[7] - (ft_min(ft_strlen(str), flags[8])
			* flags[10] + ft_strlen(str) * (!(flags[10])))))
			ret += write(1, " ", 1);
	}
	return (ret);
}

int				print_str(va_list ap, char ls[3], int f[11])
{
	char		*str;
	wchar_t		*wstr;

	if ((ls[0] == 'l' && !ls[1]) || ls[2] == 'S')
	{
		wstr = va_arg(ap, wchar_t *);
		if (!wstr && f[10] && !f[8])
			str = "";
		else if (!wstr)
			str = "(null)";
		if (!wstr)
			return (f[2]) ? str_left(str, f, 0) : str_rigth(str, f, 0);
		else
			return (f[2]) ? wstr_left(wstr, f, 0) : wstr_rigth(wstr, f, 0);
	}
	else
	{
		str = va_arg(ap, char *);
		if (!str && f[10] && !f[8])
			str = "";
		else if (!str)
			str = "(null)";
		return (f[2]) ? str_left(str, f, 0) : str_rigth(str, f, 0);
	}
}
