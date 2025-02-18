/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:20:04 by dcampas-          #+#    #+#             */
/*   Updated: 2025/02/18 16:05:18 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

static void	init_ship(t_init_params *params)
{
	params->z->x = params->fractal->shift_x + (params->x - WIDTH / 2)
		* (4.0 / WIDTH) * params->fractal->zoom;
	params->z->y = params->fractal->shift_y + (params->y - HEIGHT / 2)
		* (4.0 / HEIGHT) * params->fractal->zoom;
	params->c->x = params->z->x;
	params->c->y = params->z->y;
}

static int	calculate_ship(t_fractal *fractal, t_complex *z,
	t_complex *c)
{
	int		i;
	double	temp_x;
	t_scale	params;
	int		color;

	i = 0;
	while (i < fractal->iterations_definition)
	{
		temp_x = z->x * z->x - z->y * z->y + c->x;
		z->y = fabs(2 * z->x * z->y) + c->y;
		z->x = fabs(temp_x);
		if ((z->x * z->x) + (z->y * z->y) > fractal->escape_value)
		{
			params = (t_scale){i, COLOR_BLACK, COLOR_WHITE, 0,
				fractal->iterations_definition};
			color = fractal_map(&params);
			return (color);
		}
		++i;
	}
	return (COLOR_RAINBOW);
}

void	render_burning_ship(t_fractal *fractal, int x, int y)
{
	t_complex	z;
	t_complex	c;
	int			color;

	init_ship(&(t_init_params){fractal, &z, &c, x, y});
	color = calculate_ship(fractal, &z, &c);
	my_pixel_put(x, y, &fractal->img, color);
}
