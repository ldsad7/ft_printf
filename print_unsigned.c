/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 01:28:13 by tsimonis          #+#    #+#             */
/*   Updated: 2019/02/02 16:59:58 by tsimonis         ###   ########.fr       */
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
	if ((i = -1) && !flags[10])
		while (++i < big_num)
			ret += write(1, "0", 1);
	if (flags[8] > num && (i = -1))
		while (++i < flags[8] - num)
			ret += write(1, "0", 1);
	if (!(flags[10] && !ft_strcmp(tmp, "0") && !flags[8]))
		ret += write(1, tmp, ft_strlen(tmp));
	else if (flags[7] || ft_strcmp(tmp, "0"))
		ret += write(1, " ", 1);
	return (ret);
}

static int		negative_order(int big_num, char *tmp, int flags[11], int num)
{
	int		i;
	int		ret;

	ret = 0;
	i = -1;
	while (++i < flags[8] - num)
		ret += write(1, "0", 1);
	if (!(flags[10] && !ft_strcmp(tmp, "0") && !flags[8]))
		ret += write(1, tmp, ft_strlen(tmp));
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
	int		big_num;

	ret = 0;
	i = -1;
	big_num = flags[7] - (num + (flags[8] > num) * (flags[8] - num));
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
	int		big_num;

	ret = 0;
	big_num = flags[7] - (num + (flags[8] > num) * (flags[8] - num));
	if (flags[10] && !flags[8] && !ft_strcmp(tmp, "0"))
		big_num++;
	i = -1;
	while (++i < big_num)
		ret += write(1, " ", 1);
	i = -1;
	while (++i < flags[8] - num)
		ret += write(1, "0", 1);
	if (!(flags[10] && !flags[8] && !ft_strcmp(tmp, "0")))
		ret += write(1, tmp, ft_strlen(tmp));
	return (ret);
}

int				print_unsigned(va_list ap, char ls[3], int flags[11])
{
	unsigned long long int	c;
	int						ret;
	int						num;
	char					*tmp;

	if (ls[2] == 'U' || ls[0] == 'l' || ls[0] == 'j'
			|| ls[0] == 'z' || ls[0] == 't')
		c = va_arg(ap, unsigned long long int);
	else if (ls[0] == 'h' && ls[1] == 'h')
		c = (unsigned char)va_arg(ap, unsigned long long int);
	else if (ls[0] == 'h')
		c = (unsigned short int)va_arg(ap, unsigned long long int);
	else
		c = va_arg(ap, unsigned int);
	tmp = ft_itoa_unsigned_long(c);
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
