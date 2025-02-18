/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:48:20 by dcampas-          #+#    #+#             */
/*   Updated: 2025/02/18 14:20:55 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	i = 0;
	while ((s1[i] || s2[i]) && (s1[i] == s2[i]))
	{
		i++;
	}
	return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	while (*s)
	{
		write (fd, s, 1);
		s++;
	}
}

static void	skip_spaces(char **s, int *sign)
{
	while (**s == ' ' || (**s >= 9 && **s <= 13))
		++*s;
	while (**s == '+' || **s == '-')
		if (*(*s)++ == '-')
			*sign = -1;
}

double	atodbl(char *s)
{
	long	integer_part;
	double	fractional_part;
	double	divisor;
	int		sign;

	integer_part = 0;
	fractional_part = 0;
	divisor = 1;
	sign = 1;
	skip_spaces(&s, &sign);
	while (*s >= '0' && *s <= '9')
		integer_part = (integer_part * 10) + (*s++ - '0');
	if (*s == '.')
		++s;
	while (*s >= '0' && *s <= '9')
	{
		divisor /= 10;
		fractional_part = fractional_part + (*s++ - '0') * divisor;
	}
	if (*s != '\0')
	{
		ft_putstr_fd("Error: Invalid number\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (sign * (integer_part + fractional_part));
}
