/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition_double_hex_second.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 04:37:26 by tsimonis          #+#    #+#             */
/*   Updated: 2019/02/02 02:19:37 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_round_hex(double a)
{
	if (a - (int)a > 0.5)
		return ((int)a + (a != 0.));
	return ((int)a);
}

static int		arr_reverse(char c, int fl)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	return (c - 'A' - fl * 32);
}

void			to_filling(int j, char **to, int vars[9], char **main_str)
{
	while (j != -1)
	{
		if (arr_reverse((*to)[j], vars[8]) == 15)
			(*to)[j] = '0';
		else
		{
			if (arr_reverse((*to)[j], vars[8]) < 9
					|| arr_reverse((*to)[j], vars[8]) > 9)
				(*to)[j] += 1;
			else
				(*to)[j] = 'A' + vars[8] * 32;
			break ;
		}
		j--;
	}
	if (j == -1)
		(*main_str)[0] += 1;
}

static void		to_bzero(char **to)
{
	int		j;
	int		i;

	j = 0;
	while (j < 13)
	{
		i = j;
		while (i < 13)
		{
			if ((*to)[i] != '0')
				break ;
			i++;
		}
		if (i == 13)
		{
			ft_bzero(*to + j, 7);
			break ;
		}
		j++;
	}
}

char			*double_to_hex(double a, int vars[9],
								int flags[11], char **main_str)
{
	int		local_vars[3];
	double	mul;
	char	*to;
	char	all[16];

	local_vars_init(flags, &local_vars, &all, vars);
	if (!(to = (char *)malloc(sizeof(*to) * (local_vars[2] + 1))))
		return (NULL);
	to[local_vars[2]] = '\0';
	local_vars[0] = -1;
	mul = 1. / (double)vars[1];
	while (++local_vars[0] < local_vars[2])
	{
		if (local_vars[0] == local_vars[2] - 1)
			if (ft_round_hex(a / mul) == 16 && (to[local_vars[0]] = '0'))
				to_filling(local_vars[0] - 1, &to, vars, main_str);
			else
				to[local_vars[0]] = all[ft_round_hex(a / mul)];
		else
			to[local_vars[0]] = all[(int)(a / mul)];
		a -= (int)(a / mul) * mul;
		mul *= 1. / (double)vars[1];
	}
	to_bzero(&to);
	return (to);
}
