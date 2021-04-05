/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftprintf_read_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 15:49:10 by eniini            #+#    #+#             */
/*   Updated: 2021/04/03 23:41:35 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const char	*check_modifiers(const char *s, t_printf *f)
{
	if (*s == 'l' && s++)
	{
		if (*s == 'l' && s++)
			f->info.is_llong = 1;
		else
			f->info.is_long = 1;
	}
	if (*s == 'h' && s++)
	{
		if (*s == 'h' && s++)
			f->info.is_char = 1;
		else
			f->info.is_short = 1;
	}
	if (*s == 'L' && s++)
		f->info.is_double = 1;
	return (s);
}

/*
**	Check for a radix character, then atoi digits following it.
**	Radix char alone or with a negative value is taken as 0 precision.
**	if no precision is given, float conversion defaults to 6 digits.
**
**	Negative precision argument for (*) is handled as if it was omitted.
*/

static void			get_p_val(t_printf *f, int i, t_bool p)
{
	if (!p)
	{
		if (i >= 0)
		{
			f->info.f_prec = i;
			f->info.i_prec = i;
		}
		else
			f->info.f_prec = 6;
		if (i == 0)
			f->info.zero_prec = 1;
		return ;
	}
	if (i > 0)
	{
		f->info.i_prec = i;
		f->info.f_prec = i;
	}
	else
		f->info.zero_prec = 1;
}

static const char	*check_precision(const char *s, t_printf *f)
{
	int			i;
	const char	*p;

	i = 0;
	p = ++s;
	if (*s == '*')
	{
		i = va_arg(f->args, int);
		get_p_val(f, i, FALSE);
		return (++s);
	}
	while (*s >= '0' && *s <= '9')
	{
		i++;
		s++;
	}
	if (!i)
	{
		f->info.zero_prec = 1;
		return (s);
	}
	i = ft_atoi(p);
	get_p_val(f, i, TRUE);
	return (s);
}

/*
**	Negative value for (*) argument is taken as (-) flag + positive value.
*/

static const char	*check_width(const char *s, t_printf *f)
{
	size_t		i;
	const char	*p;
	char		*str;
	int			asterisk;

	if (*s >= '0' && *s <= '9')
	{
		i = 0;
		p = s;
		while ((*s >= '0' && *s <= '9') && s++)
			i++;
		if (!(str = ft_strndup(p, i)))
			ft_getout(MEMERR);
		f->info.width = ft_atoi(str);
		free(str);
	}
	else if (*s == '*' && s++)
	{
		asterisk = va_arg(f->args, int);
		f->info.width = (asterisk < 0) ? -asterisk : asterisk;
		if (asterisk < 0)
			f->info.left = 1;
	}
	return (s);
}

const char			*ftprintf_read_args(const char *s, t_printf *f)
{
	const char	*ret_s;

	while (*s == '#' || *s == '0' || *s == '-' || *s == '+' || *s == ' ')
	{
		if (*s == '#')
			f->info.alt = 1;
		else if (*s == '0')
			f->info.zeroed = 1;
		else if (*s == '-')
			f->info.left = 1;
		else if (*s == '+')
			f->info.showsign = 1;
		else if (*s == ' ')
			f->info.space = 1;
		s++;
	}
	ret_s = check_width(s, f);
	if (*ret_s == '.')
		ret_s = check_precision(ret_s, f);
	else
		f->info.f_prec = 6;
	return (check_modifiers(ret_s, f));
}
