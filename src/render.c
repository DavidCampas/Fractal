/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:58:58 by dcampas-          #+#    #+#             */
/*   Updated: 2025/02/18 17:04:31 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	my_pixel_put(int x, int y, t_image *img, int color)
{
	int	offset;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

int	init_z(t_complex *z, t_fractal *fractal, int x, int y)
{
	if (!ft_strcmp(fractal->name, "burning_ship"))
		return (1);
	z->x = fractal->shift_x + (x - WIDTH / 2)
		* (4.0 / WIDTH) * fractal->zoom;
	z->y = fractal->shift_y + (y - HEIGHT / 2)
		* (4.0 / HEIGHT) * fractal->zoom;
	return (0);
}

static void	mandel_vs_julia(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if (!ft_strcmp(fractal->name, "julia"))
	{
		c->x = fractal->julia_x;
		c->y = fractal->julia_y;
	}
	else
	{
		c->x = z->x;
		c->y = z->y;
	}
}

static void	handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;
	t_scale		params;

	i = 0;
	if (init_z(&z, fractal, x, y))
		return (render_burning_ship(fractal, x, y));
	mandel_vs_julia(&z, &c, fractal);
	while (i < fractal->iterations_definition)
	{
		z = fractal_sum_complex(square_complex(z), c);
		if ((z.x * z.x) + (z.y * z.y) > fractal->escape_value)
		{
			params = (t_scale){i, COLOR_BLACK, COLOR_LIME_GREEN, 0,
				fractal->iterations_definition};
			color = fractal_map(&params);
			my_pixel_put(x, y, &fractal->img, color);
			return ;
		}
		++i;
	}
	my_pixel_put(x, y, &fractal->img, COLOR_RAINBOW);
}

void	fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			handle_pixel(x, y, fractal);
		}
	}
	mlx_put_image_to_window(fractal->mlx_connection,
		fractal->mlx_window,
		fractal->img.img_ptr,
		0, 0);
}
