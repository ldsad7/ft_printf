/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_n.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 22:26:38 by tsimonis          #+#    #+#             */
/*   Updated: 2019/02/02 02:25:29 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_n(va_list ap, char ls[3], unsigned long long printed)
{
	unsigned long long int	*ulli;
	unsigned int			*ui;
	unsigned char			*uc;
	unsigned short int		*usi;

	if (ls[0] == 'l' || ls[0] == 'j' || ls[0] == 'z' || ls[0] == 't')
	{
		ulli = va_arg(ap, unsigned long long int *);
		*ulli = printed;
	}
	else if (ls[0] == 'h' && ls[1] == 'h')
	{
		uc = va_arg(ap, unsigned char *);
		*uc = printed;
	}
	else if (ls[0] == 'h')
	{
		usi = va_arg(ap, unsigned short int *);
		*usi = printed;
	}
	else
	{
		ui = va_arg(ap, unsigned int *);
		*ui = printed;
	}
}
