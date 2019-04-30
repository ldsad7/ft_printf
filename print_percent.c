/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_percent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdurgan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 20:02:21 by sdurgan           #+#    #+#             */
/*   Updated: 2019/02/02 19:55:37 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_percent(int flags[11], char c)
{
	int		ret;

	ret = 0;
	if (flags[0])
		return (write(1, &c, 1));
	else if (flags[7])
	{
		if (flags[2])
		{
			ret += write(1, &c, 1);
			while (--flags[7] != 0)
				ret += flags[6] ? write(1, "0", 1) : write(1, " ", 1);
		}
		else
		{
			while (--flags[7] != 0)
				ret += flags[6] ? write(1, "0", 1) : write(1, " ", 1);
			ret += write(1, &c, 1);
		}
	}
	else
		ret += write(1, &c, 1);
	return (ret);
}
