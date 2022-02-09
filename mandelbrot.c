#include "fractol.h"

void	ft_mandelbrot(void)
{
	t_data	data;

	data_init(&data);
	data.type = 0;
	mlx_key_hook(data.win, press_key, &data);
	mlx_mouse_hook(data.win, mouse_button, &data);
	mlx_loop_hook(data.mlx, main_loop, &data);
	mlx_loop(data.mlx);
}

void	ft_draw_mandelbrot(t_data *data)
{
	int	dx;
	int	dy;
	int	x;
	int	y;
	int	iter;

	dx = data->x;
	dy = data->y;
	x = -1;
	while (++x < WIN_WIDTH)
	{
		y = -1;
		while (++y < WIN_HEIGHT)
		{
			iter = iter_mandelbrot((double)(x + dx), (double)(y + dy)
								   , data->zoom_rate);
			if (iter != ITER_MAX)
				my_mlx_pixel_put(data, x, y, get_color(iter, data->color));
			else
				my_mlx_pixel_put(data, x, y, 0x000000);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int	iter_mandelbrot(double i, double j, double zoom_rate)
{
	int		iter;
	double	x_old;
	double	x;
	double	y;

	i = (i - WIN_WIDTH * zoom_rate / 2) * 4.0 / WIN_WIDTH * zoom_rate - 0.5;
	j = (WIN_HEIGHT * zoom_rate / 2 - j) * 4.0 / WIN_HEIGHT * zoom_rate;
	iter = 1;
	x = i;
	y = j;
	while (iter < ITER_MAX && x * x + y * y <= 4)
	{
		x_old = x;
		x = x * x - y * y + i;
		y = 2 * x_old * y + j;
		++iter;
	}
	return (iter);
}
