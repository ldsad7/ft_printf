/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition_double_hex_first.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 04:37:14 by tsimonis          #+#    #+#             */
/*   Updated: 2019/02/02 02:18:59 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		local_vars_init(int flags[11], int (*local_vars)[3],
						char (*all)[16], int vars[9])
{
	if (flags[10])
		(*local_vars)[2] = flags[8];
	else
		(*local_vars)[2] = 13;
	all_filling_hex(all, vars[8]);
}

char		*double_to_str(double c, char ls[3])
{
	char	all[16];
	char	*str;
	char	sym;

	all_filling_hex(&all, (ls[2] == 'a'));
	sym = all[(int)c];
	str = (char *)malloc(sizeof(*str) * 2);
	str[1] = '\0';
	str[0] = sym;
	return (str);
}

int			ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void		all_filling_hex(char (*all)[16], int fl)
{
	int		i;

	i = 0;
	while (i < 10)
	{
		(*all)[i] = '0' + i;
		i++;
	}
	while (i < 16)
	{
		(*all)[i] = 'A' + fl * 32 + i - 10;
		i++;
	}
}

int			free_double_str(char *double_str)
{
	ft_strdel(&double_str);
	return (0);
}
