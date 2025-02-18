/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:28:33 by dcampas-          #+#    #+#             */
/*   Updated: 2025/02/04 13:28:33 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int	close_handler(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_connection,
		fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_connection,
		fractal->mlx_window);
	mlx_destroy_display(fractal->mlx_connection);
	free(fractal->mlx_connection);
	exit(EXIT_SUCCESS);
}

int	key_handler(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		close_handler(fractal);
	if (keysym == XK_Left)
		fractal->shift_x += (0.5 * fractal->zoom);
	else if (keysym == XK_Right)
		fractal->shift_x -= (0.5 * fractal->zoom);
	else if (keysym == XK_Up)
		fractal->shift_y += (0.5 * fractal->zoom);
	else if (keysym == XK_Down)
	{
		fractal->shift_y -= (0.5 * fractal->zoom);
	}
	else if (keysym == XK_plus)
	{
		fractal->iterations_definition += 10;
	}
	else if (keysym == XK_minus)
	{
		fractal->iterations_definition -= 10;
	}
	fractal_render(fractal);
	return (0);
}

int	mouse_handler(int button, int x, int y, t_fractal *fractal)
{
	(void)x;
	(void)y;
	if (button == Button5)
	{
		fractal->zoom *= 1.05;
	}
	else if (button == Button4)
	{
		fractal->zoom *= 0.95;
	}
	fractal_render(fractal);
	return (0);
}

int	julia_track(int x, int y, t_fractal *fractal)
{
	static int	last_x = 0;
	static int	last_y = 0;
	double		julia_x_scaled;
	double		julia_y_scaled;

	julia_x_scaled = (double)x / WIDTH * 4.0 - 2.0;
	julia_y_scaled = (double)y / HEIGHT * 4.0 - 2.0;
	if (abs(x - last_x) > 5 || abs(y - last_y) > 5)
	{
		last_x = x;
		last_y = y;
		if (!ft_strcmp(fractal->name, "julia"))
		{
			fractal->julia_x = (julia_x_scaled * fractal->zoom)
				+ fractal->shift_x;
			fractal->julia_y = (julia_y_scaled * fractal->zoom)
				+ fractal->shift_y;
			fractal_render(fractal);
		}
	}
	return (0);
}
