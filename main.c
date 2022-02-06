#include "fract-ol.h"

int	press_esc_key(int key, void *p)
{
	if (key == 53)
		exit(0);
	return (0);
}
static int	_strcmp(char *s1, char *s2);
int main(int argc, char **argv)
{
	if (argc != 2 || ft_check_input(argv[1]))
		ft_error();
	if (!_strcmp(argv[1], "Mandelbrot"))
		ft_mandelbrot();
//	else if (!_strcmp(argv[1], "Julia")))
//		ft_julia();
//	else
//		ft_();
	return (0);
}

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (x * img->bpp / 8) + (y * img->line_length);
	*(unsigned int *)dst = color;
}

int get_color(int iter)
{
	int	color;
	double r;

	r = (double)iter / ITER_MAX;
	color = (int)(8.5 * pow(1 - r, 3) * 255 * r) << 16;
	color += (int)(15 * pow(1 - r, 2) * pow(r, 2) * 255) << 8;
	color += (int)(9 * (1 - r) *pow(r, 3) * 255);
}

void ft_mandelbrot(void)
{
	void	*mlx;
	void	*win_ptr;
	int		iter;
	int     x;
	int     y;
	t_data  img;

	mlx = mlx_init();
	if (!mlx)
		exit(1);
	win_ptr = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "fractal");
	if (!win_ptr)
		exit(1);
	img.img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);

	x = -1;
	while (++x <= WIN_WIDTH)
	{
		y = -1;
		while (++y <= WIN_HEIGHT)
		{
			iter = iter_mandelbrot((double)x, (double)y);
			if (iter != ITER_MAX)
//				my_mlx_pixel_put(&img, x, y, get_color(iter));
				mlx_pixel_put(mlx, win_ptr, x, y, 265 * iter);
			else
				my_mlx_pixel_put(&img, x, y, 0x000000);
//			my_mlx_pixel_put(&img, x, y, get_color(iter));
		}
	}
	mlx_key_hook(win_ptr, press_esc_key, 0);
	mlx_loop(mlx);
}



int iter_mandelbrot(double i, double j)
{
	int iter;
	int x_n;
	double x;
	double y;

//	printf("%f %f ", i , j);
	i = (i - WIN_WIDTH / 2) * 4.0 / WIN_WIDTH;
	j = (WIN_HEIGHT / 2 - j) * 4.0 / WIN_HEIGHT;
	iter = 1;
	x = i;
	y = j;
//	printf("|| i:%f, j:%f", i, j);
	while (iter < ITER_MAX && pow(x, 2.0) + pow(y, 2.0) <= 4)
	{
		x_n = x;
		x = pow(x, 2.0) - pow(y, 2.0) + i;
		y = 2 * x_n * y + j;
		++iter;
	}
//	printf("|| %d \n", iter);
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
