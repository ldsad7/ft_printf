/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 20:39:09 by tsimonis          #+#    #+#             */
/*   Updated: 2019/02/02 12:54:33 by sdurgan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	percent_parsing(const char **str, va_list ap, int printed)
{
	int		len;
	int		ret;

	ret = 0;
	if (**str == '%' && (*str)++)
	{
		if (**str == '%' && (*str)++)
			ret += write(1, "%", 1);
		else
		{
			len = print(ap, (char **)str, printed);
			if (len == -1)
				len = 0;
			ret += len;
			if (**str)
				(*str)++;
		}
	}
	return (ret);
}

static int	put_colour(char *colour)
{
	if (!ft_strcmp("{red}", colour))
		return (write(1, "\033[0;31m", 7));
	else if (!ft_strcmp("{grn}", colour))
		return (write(1, "\033[0;32m", 7));
	else if (!ft_strcmp("{yel}", colour))
		return (write(1, "\033[0;33m", 7));
	else if (!ft_strcmp("{blu}", colour))
		return (write(1, "\033[0;34m", 7));
	else if (!ft_strcmp("{mag}", colour))
		return (write(1, "\033[0;35m", 7));
	else if (!ft_strcmp("{cya}", colour))
		return (write(1, "\033[0;36m", 7));
	else if (!ft_strcmp("{eoc}", colour))
		return (write(1, "\033[0m", 4));
	else
		return (0);
}

static int	check_colour(const char **s, int ret, char *colour)
{
	if (put_colour(colour))
	{
		*s += ret + 5;
		if (!(ft_strcmp("{eoc}", colour)))
			ret += 4;
		else
			ret += 7;
	}
	else
	{
		ret += write(1, &((*s)[ret]), 1);
		*s += ret;
	}
	ft_strdel(&colour);
	return (ret);
}

static int	put_color_tag(const char **s)
{
	int		ret;
	char	*colour;

	ret = 0;
	while ((*s)[ret] != '{')
	{
		if ((*s)[ret] == '%')
		{
			*s += ret;
			return (ret);
		}
		ret += write(1, &((*s)[ret]), 1);
	}
	colour = ft_strlen(*s) >= 5 ? ft_strsub(*s, ret, 5) : NULL;
	if (colour)
		return (check_colour(s, ret, colour));
	else
	{
		*s += ret + 1;
		return (write(1, "{", 1));
	}
}

int			ft_printf(const char *str, ...)
{
	va_list	ap;
	int		len;
	int		ret;
	char	*tmp;

	va_start(ap, str);
	ret = 0;
	while (*str)
	{
		while (ft_strchr(str, '{') && ft_strchr(str, '}') && *str != '%')
			ret += put_color_tag(&str);
		if (!(tmp = ft_strchr(str, '%')))
			tmp = "";
		ret += write(1, str, ft_strlen(str) - ft_strlen(tmp));
		str = tmp;
		len = percent_parsing(&str, ap, ret);
		if (len == -1)
			return (-1);
		ret += len;
	}
	va_end(ap);
	return (ret);
}
