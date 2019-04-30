/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 01:27:08 by tsimonis          #+#    #+#             */
/*   Updated: 2019/02/02 02:19:54 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void							int_bzero(int (*flags)[11], int *dots,
												int *nul, char (*ls)[3])
{
	int		i;

	*dots = 0;
	*nul = 0;
	i = 0;
	while (i < 3)
		(*ls)[i++] = '\0';
	i = 0;
	while (i < 11)
		(*flags)[i++] = 0;
}

int								print_arg(va_list ap, char ls[3],
											int flags[11], int print_)
{
	if (ls[2] == 'c' || ls[2] == 'C')
		return (print_char(ap, ls, flags));
	else if (ls[2] == 'S' || ls[2] == 's')
		return (print_str(ap, ls, flags));
	else if (ls[2] == 'd' || ls[2] == 'D' || ls[2] == 'i')
		return (print_int(ap, ls, flags));
	else if (ls[2] == 'p')
		return (print_pointer(ap, flags));
	else if (ls[2] == 'x' || ls[2] == 'X')
		return (print_int_hex(ap, ls, flags));
	else if (ls[2] == 'U' || ls[2] == 'u')
		return (print_unsigned(ap, ls, flags));
	else if (ls[2] == 'a' || ls[2] == 'A')
		return (print_double_hex(ap, ls, flags));
	else if (ls[2] == 'o' || ls[2] == 'O')
		return (print_octal(ap, ls, flags));
	else if (ls[2] == 'n')
		print_n(ap, ls, print_);
	else if (ls[2] == 'F' || ls[2] == 'f' || ls[2] == 'e' || ls[2] == 'E' ||
			ls[2] == 'G' || ls[2] == 'g')
		return (print_double(ap, ls, flags));
	else
		return (print_percent(flags, ls[2]));
	return (0);
}

static void						all_filling(int (*flags)[11], char **str)
{
	if ((*flags)[7])
		(*flags)[7] = 0;
	while (**str >= '0' && **str <= '9' && **str)
	{
		(*flags)[7] = 10 * (*flags)[7] + **str - '0';
		(*str)++;
	}
	(*str)--;
}

static void						precision_filling(int (*flags)[11],
													char **str)
{
	if ((*flags)[8])
		(*flags)[8] = 0;
	while (**str >= '0' && **str <= '9' && **str)
	{
		(*flags)[8] = 10 * (*flags)[8] + **str - '0';
		(*str)++;
	}
	(*str)--;
}

int								flags_filling(int (*flags)[11], char **str,
												int *dots, int *nul)
{
	if (**str == ' ')
		(*flags)[0] = 1;
	else if (**str == '+')
		(*flags)[1] = 1;
	else if (**str == '-')
		(*flags)[2] = 1;
	else if (**str == '#')
		(*flags)[3] = 1;
	else if (**str == '\'')
		(*flags)[4] = 1;
	else if (**str == 'I')
		(*flags)[5] = 1;
	else if (**str == '.' && (*dots = 1))
		(*flags)[10] = 1;
	else if (!(*flags)[10] && *nul == 0 && **str == '0' && (*nul = 1))
		(*flags)[6] = 1;
	else if (*dots == 0 && **str >= '0' && **str <= '9' && (*nul = 1))
		all_filling(flags, str);
	else if (*dots == 1 && **str >= '0' && **str <= '9' && (*nul = 1))
		precision_filling(flags, str);
	else
		return (0);
	return (1);
}
