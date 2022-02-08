#include "fract-ol.h"

void ft_move(int key, t_data *p)
{
	if (key == 0)
		p->x -= 100;
	else if (key == 2)
		p->x += 100;
	else if (key == LEFT)
		p->x -= 25;
	else if (key == RIGHT)
		p->x += 25;
	else if (key == DOWN)
		p->y += 25;
	else if (key == UP)
		p->y -= 25;
	else if (key == 24)
		p->zoom_rate *= 0.9;
	else if (key == 27)
		p->zoom_rate *= 1.1;
}

int	press_key(int key, void *p)
{
	if ((key == 0 || key == 2) || key >= LEFT && key <= UP || (key == 24 || key == 27))
		ft_move(key, (t_data *)p);
	else if (key == 53)
		exit(0);
	return (0);
}

static int	_strcmp(char *s1, char *s2);

int main(int argc, char **argv)
{
	if (argc < 2 || ft_check_input(argv[1]))
		ft_error();
	if (!_strcmp(argv[1], "Mandelbrot"))
		ft_mandelbrot();
	else if (argc == 4 && !_strcmp(argv[1], "Julia"))
		ft_julia(atof(argv[2]), atof(argv[3]));
	//	else if ()
	//		ft_bonus();
	//	else
	//		ft_error();
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (x * (data->bpp / 8)) + (y * data->line_length);
	*(unsigned int *)dst = color;
}

int get_color(int iter)
{
	int	color;
	double r;

	r = (double)iter / ITER_MAX;
	color = 0;
	color += (int)(8.5 * pow(1 - r, 3) * 255 * r) << 16;
	color += (int)(15 * pow(1 - r, 2) * pow(r, 2) * 255) << 8;
	color += (int)(9 * (1 - r) *pow(r, 3) * 255);
	if (SHIFT_C == 1)
	{
		color = ((color & 0xFF0000) >> 16) +
			((color & 0x00FF00) << 8) +
			((color & 0x0000FF) << 8);
	}
	else if (SHIFT_C == 2)
	{
		color = ((color & 0xFF0000) >> 8) +
			((color & 0x00FF00) >> 8) +
			((color & 0x0000FF) << 16);
	}
	return (color);
}

void data_init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit(1);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "fractal");
	if (!data->win)
		exit(1);
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_length, &data->endian);
	data->x = 0;
	data->y = 0;
	data->zoom_rate = 1;
}

int mouse_button(int button, int x, int y, void *p)
{
	t_data *data;

	data = (t_data *)p;
	if (button == 5 || button == 4)
	{
		//		data->x *= data->zoom_rate;
		//		data->y *= data->zoom_rate;
		data->x += (x - WIN_WIDTH / 2) * data->zoom_rate / 2;
		data->y += (WIN_HEIGHT / 2 - y) * data->zoom_rate / 2;
		if (button == 5)
			data->zoom_rate *= 0.9;
		if (button == 4)
			data->zoom_rate *= 1.1;
	}
}

void ft_julia(double a, double b)
{
	t_data data;

	data_init(&data);
	data.type = 1;
	data.a = a;
	data.b = b;
	mlx_key_hook(data.win, press_key, &data);
	mlx_mouse_hook(data.win, mouse_button, &data);
	mlx_loop_hook(data.mlx, main_loop, &data);
	mlx_loop(data.mlx);
}

void ft_mandelbrot(void)
{
	t_data  data;

	data_init(&data);
	data.type = 0;
	mlx_key_hook(data.win, press_key, &data);
	mlx_mouse_hook(data.win, mouse_button, &data);
	mlx_loop_hook(data.mlx, main_loop, &data);
	mlx_loop(data.mlx);
}

int main_loop(t_data *data)
{
	if (data->type == 0)
		ft_draw_mandelbrot(data);
	else if (data->type == 1)
		ft_draw_julia(data);
	return (0);
}

void ft_draw_mandelbrot(t_data *data)
{
	int x;
	int y;
	int iter;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		y = -1;
		while (++y < WIN_HEIGHT)
		{
			iter = iter_mandelbrot((double)(x + data->x), (double)(y + data->y), data->zoom_rate);
			if (iter != ITER_MAX)
				my_mlx_pixel_put(data, x, y, get_color(iter));
			else
				my_mlx_pixel_put(data, x, y, 0x000000);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int iter_mandelbrot(double i, double j, double k)
{
	int iter;
	double x_old;
	double x;
	double y;

	i = (i - WIN_WIDTH * k / 2) * 4.0 / WIN_WIDTH * k - 0.5;
	j = (WIN_HEIGHT * k / 2 - j) * 4.0 / WIN_HEIGHT * k;
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

void ft_draw_julia(t_data *data)
{
	int x;
	int y;
	int iter;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		y = -1;
		while (++y < WIN_HEIGHT)
		{
			iter = iter_julia((double)(x + data->x), (double)(y + data->y), data);
			if (iter != ITER_MAX)
				my_mlx_pixel_put(data, x, y, get_color(iter));
			else
				my_mlx_pixel_put(data, x, y, 0x000000);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int iter_julia(double x, double y, t_data *data)
{
	int iter;
	double x_old;
	double i;
	double j;
	double k = data->zoom_rate;

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

void	ft_error(void)
{
	//ft_putstr_fd("usage : fractol [fractals]\n fractals :\n --> Mandelbrot\n --> Julia\n --> (Bonus)\n", 2);
	printf("usage: \"./fractal [fractals]\"\n fractals :\n --> Mandelbrot\n --> Julia\n --> (Bonus)\n");
	exit(1);
}

int	ft_check_input(char *s)
{
	if (!s)
		return (1);
	if (s[0] == 'M')
		return (_strcmp(s, "Mandelbrot"));
	else if (s[0] == 'J')
		return (_strcmp(s, "Julia"));
	else if (s[0] == 'S')
		return (_strcmp(s, "Snowflake"));
	else
		return (1);
}

int _strcmp(char *s1, char *s2)
{
	int i;

	i = -1;
	while (s1[++i] && s2[i])
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	return (s1[i] - s2[i]);
}

