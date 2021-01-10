/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 18:00:30 by artmende          #+#    #+#             */
/*   Updated: 2021/01/06 13:30:06 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	case_diu(t_meta *mdata, va_list args, int *nc, int count)
{
	int		i;
	int		minus;
	char	esp;
	char	result[10];

	esp = (mdata->zero == '1' && mdata->dot < 0) ? '0' : ' ';
	minus = va_arg(args, int);
	i = fill_dec(minus, result, mdata->type, mdata->dot);
	minus = (minus < 0 && mdata->type != 'u') ? 1 : 0;
	if (minus == 1 && esp == '0')
		count = count + write(1, "-", 1);
	while (mdata->nbr - mdata->dot > minus
				&& mdata->nbr > (i + minus) && mdata->nbr--)
		count = count + write(1, &esp, 1);
	if (minus == 1 && esp == ' ')
		count = count + write(1, "-", 1);
	while (mdata->dot-- > i)
		count = count + write(1, "0", 1);
	while (i--)
		count = count + write(1, &result[i], 1);
	while (-1 * mdata->nbr > count)
		count = count + write(1, " ", 1);
	*nc = *nc + count;
}

void	case_s(t_meta *mdata, va_list args, int *nc)
{
	int		i;
	int		len;
	char	esp;

	i = 0;
	len = 0;
	if (mdata->zero == 0)
		esp = ' ';
	else
		esp = '0';
	if ((mdata->content = va_arg(args, char *)))
		len = (int)ft_strlen(mdata->content);
	else
	{
		mdata->content = "(null)";
		len = 6;
	}
	if (mdata->dot >= 0 && len > mdata->dot)
		len = mdata->dot;
	while (mdata->nbr > 0 && i + len < mdata->nbr)
		i = i + write(1, &esp, 1);
	*nc = *nc + write(1, mdata->content, len);
	while (mdata->nbr < 0 && i + len < -1 * (mdata->nbr))
		i = i + write(1, " ", 1);
	*nc = *nc + i;
}

void	case_c_percent(t_meta *mdata, va_list args, int *nc)
{
	int		i;
	int		c;
	char	esp;

	if (mdata->zero == 0)
		esp = ' ';
	else
		esp = '0';
	i = 0;
	if (mdata->type == 'c')
		c = va_arg(args, int);
	else
		c = '%';
	while (++i < mdata->nbr)
		*nc = *nc + write(1, &esp, 1);
	*nc = *nc + write(1, &c, 1);
	i = 0;
	while (--i > mdata->nbr)
		*nc = *nc + write(1, " ", 1);
}

void	case_xx(t_meta *mdata, va_list args, int *nc)
{
	int		i;
	int		count;
	char	esp;
	char	result[8];

	count = 0;
	if (mdata->zero == '1' && mdata->dot < 0)
		esp = '0';
	else
		esp = ' ';
	i = fill_hexa((unsigned long)va_arg(args, unsigned int), result,
		mdata->type, mdata->dot);
	while (mdata->nbr - mdata->dot > 0 && mdata->nbr > i && mdata->nbr--)
		count = count + write(1, &esp, 1);
	while (mdata->dot-- > i)
		count = count + write(1, "0", 1);
	while (i--)
		count = count + write(1, &result[i], 1);
	while (-1 * mdata->nbr > count)
		count = count + write(1, " ", 1);
	*nc = *nc + count;
}

void	case_p(t_meta *mdata, va_list args, int *nc)
{
	int		i;
	int		count;
	char	esp;
	char	result[16];

	count = 0;
	if (mdata->zero == '1' && mdata->dot < 0 && (esp = '0'))
		count = count + write(1, "0x", 2);
	else
		esp = ' ';
	i = fill_hexa(va_arg(args, unsigned long), result, 'x', mdata->dot);
	while (mdata->nbr - mdata->dot > 2 && mdata->nbr > (i + 2) && mdata->nbr--)
		count = count + write(1, &esp, 1);
	if (esp == ' ')
		count = count + write(1, "0x", 2);
	while (mdata->dot-- > i)
		count = count + write(1, "0", 1);
	while (i--)
		count = count + write(1, &result[i], 1);
	while (-1 * mdata->nbr > count)
		count = count + write(1, " ", 1);
	*nc = *nc + count;
}
