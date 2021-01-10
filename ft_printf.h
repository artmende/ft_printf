/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:09:06 by artmende          #+#    #+#             */
/*   Updated: 2021/01/06 11:44:48 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include "libft/libft.h"

/*
**	t_meta.zero default value is '\0', if active value is '1'
**	t_meta.nbr default value is 0
**	t_meta.dot default value is -1
*/

typedef struct	s_meta
{
	char	type;
	char	zero;
	int		nbr;
	int		dot;
	void	*content;
}				t_meta;

int				ft_printf(const char *str, ...);
int				fill_dec(int nbr, char *result, char type, int dot);
int				fill_hexa(unsigned long nbr, char *result, char type, int dot);
void			case_p(t_meta *mdata, va_list args, int *nc);
void			case_xx(t_meta *mdata, va_list args, int *nc);
void			case_c_percent(t_meta *mdata, va_list args, int *nc);
void			case_s(t_meta *mdata, va_list args, int *nc);
void			case_diu(t_meta *mdata, va_list args, int *nc, int count);
char			*select_action(char *str, va_list args, int *nc);
t_meta			*build_meta(char *from, char *to, char minus, va_list args);

#endif
