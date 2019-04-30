/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 05:14:19 by tsimonis          #+#    #+#             */
/*   Updated: 2019/02/02 02:19:45 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_end(char sign, int num, char *tmp, int flags[11])
{
	int		ret;
	int		i;

	ret = 0;
	if (sign)
		ret += write(1, &sign, 1);
	else if (!(num == 1 && tmp[0] == '0') && flags[0])
		ret += write(1, " ", 1);
	if (flags[8] > num - (tmp[0] == '-') && (i = -1))
		while (++i < flags[8] - (num - (tmp[0] == '-')))
			ret += write(1, "0", 1);
	if (!(flags[10] && !flags[8] && tmp[0] == '0'))
		ret += write(1, tmp + (tmp[0] == '-'),
				ft_strlen(tmp + (tmp[0] == '-')));
	return (ret);
}
