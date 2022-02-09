#include "fract-ol.h"

void	ft_julia(double a, double b)
{
	t_data	data;

	data_init(&data);
	data.type = 1;
	data.a = a;
	data.b = b;
	mlx_key_hook(data.win, press_key, &data);
	mlx_mouse_hook(data.win, mouse_button, &data);
	mlx_loop_hook(data.mlx, main_loop, &data);
	mlx_loop(data.mlx);
}

void	ft_draw_julia(t_data *data)
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
			iter = iter_julia((double)(x + dx), (double)(y + dy), data);
			if (iter != ITER_MAX)
				my_mlx_pixel_put(data, x, y, get_color(iter, data->color));
			else
				my_mlx_pixel_put(data, x, y, 0x000000);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}


int	iter_julia(double x, double y, t_data *data)
{
	int		iter;
	double	x_old;
	double	i;
	double	j;
	double	k;

	k = data->zoom_rate;
	x = (x - WIN_WIDTH * k / 2) * 4.0 / WIN_WIDTH * k;
	y = (WIN_HEIGHT * k / 2 - y) * 4.0 / WIN_HEIGHT * k;
	i = data->a;
	j = data->b;
	iter = 1;
	while (iter < ITER_MAX && x * x + y * y <= 4)
	{
		x_old = x;
		x = x * x - y * y + i;
		y = 2 * x_old * y + j;
		++iter;
	}
	return (iter);
}