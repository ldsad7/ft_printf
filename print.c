/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 23:05:48 by tsimonis          #+#    #+#             */
/*   Updated: 2019/02/02 02:22:50 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void							ls_filling(int (*flags)[11], char (*ls)[3],
												char **str)
{
	if ((*flags)[6] && (*flags)[2])
		(*flags)[6] = 0;
	if ((*flags)[0] && (*flags)[1])
		(*flags)[0] = 0;
	(*ls)[2] = **str;
}

static void							ls_filling_beginning(char **str,
											char (*ls)[3])
{
	if (**str == 'h')
		if ((*ls)[0])
			(*ls)[1] = 'h';
		else
			(*ls)[0] = 'h';
	else if (**str == 'l')
		if ((*ls)[0])
			(*ls)[1] = 'l';
		else
			(*ls)[0] = 'l';
	else
		(*ls)[0] = **str;
}

static void							stars_filling(int dots, int (*flags)[11],
													va_list ap)
{
	if (dots)
	{
		(*flags)[8] = va_arg(ap, int);
		if ((*flags)[8] < 0)
		{
			(*flags)[8] = 0;
			(*flags)[10] = 0;
		}
	}
	else
	{
		(*flags)[7] = va_arg(ap, int);
		if ((*flags)[7] < 0)
		{
			(*flags)[2] = 1;
			(*flags)[7] = -(*flags)[7];
		}
	}
}

int									print(va_list ap, char **str, int ret)
{
	int		flags[11];
	char	ls[3];
	int		dots;
	int		nul;
	int		i;

	int_bzero(&flags, &dots, &nul, &ls);
	while (**str && ft_strchr("# -+'*I.0123456789hljztL", **str))
	{
		if (ft_strchr("hljztL", (int)**str))
			ls_filling_beginning(str, &ls);
		else if (!(i = flags_filling(&flags, str, &dots, &nul)))
		{
			if (**str == '*')
				stars_filling(dots, &flags, ap);
			else
				break ;
		}
		(*str)++;
	}
	ls_filling(&flags, &ls, str);
	if (**str)
		return (print_arg(ap, ls, flags, ret));
	return (-1);
}
