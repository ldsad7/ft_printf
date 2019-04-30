/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdurgan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 11:55:06 by sdurgan           #+#    #+#             */
/*   Updated: 2019/02/02 14:55:53 by sdurgan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

double				double_abs(double num)
{
	return (num > 0 ? num : -num);
}

unsigned long long	power(unsigned long long num, int power)
{
	unsigned long long	ret;

	if (power == 0)
		return (1);
	ret = num;
	while (power-- != 1)
		ret *= num;
	return (ret);
}

int					ft_round(char **head, char **tail, int nul_l[2], char up)
{
	int	i;

	if (!ft_strcmp((*tail), "0"))
		return (0);
	i = ft_strlen(*tail);
	if (!nul_l[0])
		return (round_f(head, tail, nul_l[1], i));
	else
		return (round_g(head, tail, nul_l[1], up));
}

int					convert_e(char up, int i, int nul_l[2], int flags[11])
{
	char	*ex;
	int		ret;

	ret = 0;
	if (nul_l[0] && flags[10] && !flags[8])
		return (ret);
	ret += i >= 0 && up == 'e' ? write(1, "e+", 2) : 0;
	ret += i >= 0 && up == 'E' ? write(1, "E+", 2) : 0;
	ret += i < 0 && (i = -i) && up == 'e' ? write(1, "e-", 2) : 0;
	ret += i < 0 && (i = -i) && up == 'E' ? write(1, "E-", 2) : 0;
	ex = ft_itoa_unsigned_long(i);
	ret += ft_strlen(ex) == 1 ? write(1, "0", 1) + write(1, ex, ft_strlen(ex)) :
		write(1, ex, ft_strlen(ex));
	ft_strdel(&ex);
	return (ret);
}
