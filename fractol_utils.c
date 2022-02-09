#include "fract-ol.h"

void	data_init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit(1);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "fractal");
	if (!data->win)
		exit(1);
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img)
		exit(1);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_length, &data->endian);
	if (!data->addr)
		exit(1);
	data->x = 0;
	data->y = 0;
	data->press_f = 0;
	data->color = 0;
	data->zoom_rate = 1;
}

int	get_color(int iter, int shift_color)
{
	int		color;
	double	r;

	r = (double)iter / ITER_MAX;
	color = 0;
	color += (int)(8.5 * pow(1 - r, 3) * 255 * r) << 16;
	color += (int)(15 * pow(1 - r, 2) * pow(r, 2) * 255) << 8;
	color += (int)(9 * (1 - r) *pow(r, 3) * 255);
	if (shift_color == 1)
		color = ((color & 0xFF0000) >> 16) +
				((color & 0x00FF00) << 8) +
				((color & 0x0000FF) << 8);
	else if (shift_color == 2)
		color = ((color & 0xFF0000) >> 8) +
				((color & 0x00FF00) >> 8) +
				((color & 0x0000FF) << 16);
	return (color);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (x * (data->bpp / 8)) + (y * data->line_length);
	*(unsigned int *)dst = color;
}

double	ft_atof(const char *str)
{
	int	i;
	int	sign;
	int	dot;
	int	ret;

	i = 0;
	sign = 1;
	ret = 0;
	if (str[i] == '-')
	{
		++i;
		sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
		ret = ret * 10 + sign * (str[i++] - '0');
	if (str[i] == '.')
	{
		++i;
		dot = i;
	}
	while (str[i] >= '0' && str[i] <= '9')
		ret = ret * 10 + sign * (str[i++] - '0');
	return ((double)ret / pow(10, i - dot));
}