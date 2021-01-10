/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 17:59:02 by artmende          #+#    #+#             */
/*   Updated: 2021/01/06 15:03:19 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		fill_dec(int nbr, char *result, char type, int dot)
{
	int				i;
	int				sav_nbr;
	unsigned int	unbr;

	i = 0;
	sav_nbr = nbr;
	if (type == 'u' && !(nbr = 0))
		unbr = (unsigned int)sav_nbr;
	while (nbr || unbr)
	{
		if (type == 'i' || type == 'd')
		{
			if (nbr > 0)
				result[i++] = (nbr % 10) + '0';
			if (nbr < 0)
				result[i++] = -(nbr % 10) + '0';
		}
		if (type == 'u')
			result[i++] = (unbr % 10) + '0';
		nbr = nbr / 10;
		unbr = unbr / 10;
	}
	if (!sav_nbr && dot)
		result[i++] = '0';
	return (i);
}

int		fill_hexa(unsigned long nbr, char *result, char type, int dot)
{
	int		i;
	char	*base;

	if (type == 'x')
		base = "0123456789abcdef";
	if (type == 'X')
		base = "0123456789ABCDEF";
	i = 0;
	if (!nbr && dot)
	{
		result[0] = '0';
		return (1);
	}
	while (nbr)
	{
		result[i] = base[nbr % 16];
		nbr = nbr / 16;
		i++;
	}
	return (i);
}

t_meta	*build_meta(char *from, char *to, char minus, va_list args)
{
	t_meta	*new;

	if (!(new = ft_calloc(1, sizeof(t_meta))))
		return (0);
	new->type = *to;
	new->dot = -1;
	while (ft_strchr("-0", *from))
	{
		(void)(*from == '0' && from++ && (new->zero = '1'));
		(void)(*from == '-' && from++ && (minus = '-'));
	}
	if (*from == '*' && from++)
		new->nbr = va_arg(args, int);
	if (ft_strchr("0123456789", *from))
		new->nbr = ft_atoi(from);
	while (ft_strchr("0123456789", *from))
		from++;
	if (minus == '-' && new->nbr > 0)
		new->nbr = new->nbr * -1;
	(void)(*from == '.' && from++ && (new->dot = 0));
	if (*from == '*')
		new->dot = va_arg(args, int);
	if (ft_strchr("0123456789", *from))
		new->dot = ft_atoi(from);
	return (new);
}

char	*select_action(char *str, va_list args, int *nc)
{
	char	*ptr_origin;
	t_meta	*mdata;

	ptr_origin = str;
	while (!ft_strchr("discpuxX%", *str))
		str++;
	if (!(mdata = build_meta(ptr_origin, str, '+', args)))
		return (0);
	if (*str == 'd' || *str == 'i' || *str == 'u')
		case_diu(mdata, args, nc, 0);
	else if (*str == 's')
		case_s(mdata, args, nc);
	else if (*str == 'c' || *str == '%')
		case_c_percent(mdata, args, nc);
	else if (*str == 'x' || *str == 'X')
		case_xx(mdata, args, nc);
	else if (*str == 'p')
		case_p(mdata, args, nc);
	free(mdata);
	return (str + 1);
}

int		ft_printf(const char *str, ...)
{
	int		nc;
	va_list	args;

	if (!str && write(1, "Error !! First arg cannot be null pointer !!\n", 45))
		return (-1);
	nc = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			if (!(str = select_action((char *)str + 1, args, &nc)))
			{
				write(1, "!! Parsing error !!\n", 20);
				va_end(args);
				return (-1);
			}
		}
		else
			nc = nc + write(1, str++, 1);
	}
	va_end(args);
	return (nc);
}
