/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double_hex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 22:27:49 by tsimonis          #+#    #+#             */
/*   Updated: 2019/02/02 17:07:41 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		print_ending(int vars[9], char *power_str, int flags[11],
							char *str)
{
	int		ret;
	int		i;

	ft_strdel(&str);
	ret = 0;
	if (vars[8])
		ret += write(1, "p", 1);
	else
		ret += write(1, "P", 1);
	if (vars[4])
		ret += write(1, "+", 1);
	else
		ret += write(1, "-", 1);
	ret += write(1, power_str, ft_strlen(power_str));
	ft_strdel(&power_str);
	i = -1;
	vars[6] += ret;
	while (flags[2] && ++i < flags[7] - vars[6])
		ret += write(1, " ", 1);
	return (ret);
}

static int		print_middle(int minus, int flags[11], char ls[3])
{
	int		ret;

	ret = 0;
	if (minus)
		ret += write(1, "-", 1);
	else if (flags[1])
		ret += write(1, "+", 1);
	else if (flags[0])
		ret += write(1, " ", 1);
	if (ls[2] == 'a')
		ret += write(1, "0x", 2);
	else
		ret += write(1, "0X", 2);
	return (ret);
}

static void		print_after_middle(int (*vars)[9], int flags[11],
								char *main_str, char *double_str)
{
	while (flags[6] && ++(*vars)[5] < (*vars)[7])
		(*vars)[6] += write(1, "0", 1);
	(*vars)[6] += write(1, main_str, ft_strlen(main_str));
	(*vars)[6] += (flags[8] && flags[10]) ||
		(!flags[10] && ft_strcmp(double_str, "")) ? write(1, ".", 1) : 0;
	(*vars)[6] += write(1, double_str, ft_strlen(double_str));
	(*vars)[5] = -1;
	while (++(*vars)[5] < flags[8] - (int)ft_strlen(double_str))
		(*vars)[6] += write(1, "0", 1);
	ft_strdel(&double_str);
}

static void		vars_and_c_init(int (*vars)[9], char ls[3],
								double *c, va_list ap)
{
	(*vars)[6] = 0;
	if (ls[0] == 'L' && ((*vars)[1] = 16))
		*c = va_arg(ap, long double);
	else if (((*vars)[1] = 2))
		*c = va_arg(ap, double);
	(*vars)[3] = 0;
	if (*c < 0 && ((*vars)[3] = 1))
		*c = -(*c);
	(*vars)[4] = 1;
	if (!((*vars)[2] = 0) && *c >= (*vars)[1])
		while (*c >= (*vars)[1] && ++(*vars)[2])
			*c /= 2;
	else if (*c < ((*vars)[1] / 2) && *c != 0)
		while (*c < ((*vars)[1] / 2) && !((*vars)[4] = 0) && ++(*vars)[2])
			*c *= 2;
	(*vars)[1] = 16;
	(*vars)[5] = -1;
	(*vars)[8] = (ls[2] == 'a');
}

int				print_double_hex(va_list ap, char ls[3], int flags[11])
{
	int		vars[9];
	double	c;
	char	*str;
	char	*double_str;
	char	*power;

	vars_and_c_init(&vars, ls, &c, ap);
	power = ft_itoa_long(vars[2]);
	str = double_to_str(c, ls);
	double_str = double_to_hex(c - (int)c, vars, flags, &str);
	if (!(vars[0] = 0) && (vars[3] || flags[1] || flags[0]))
		vars[0] = 1;
	vars[7] = flags[7] - (vars[0] + 2 + (int)ft_strlen(str));
	vars[7] -= ((c != (int)c || c == 0) && !(flags[8] == 0 && flags[10])) *
	(ft_max(ft_strlen(double_str), flags[8]) + 1) + 2 + (int)ft_strlen(power);
	while (!flags[6] && ++vars[5] < vars[7] && !flags[2])
		vars[6] += write(1, " ", 1);
	vars[6] += print_middle(vars[3], flags, ls);
	if (!flags[8] && flags[10])
		str[0] = '2' * (c != 0) + '0' * (c == 0);
	if ((c != (int)c || !c) && (vars[5] = -1))
		print_after_middle(&vars, flags, str, double_str);
	else
		vars[6] += write(1, str, ft_strlen(str)) + free_double_str(double_str);
	return (vars[6] + print_ending(vars, power, flags, str));
}
