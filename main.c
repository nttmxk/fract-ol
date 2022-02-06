#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "mlx.h"
#include <math.h>
//#include "mms/mlx.h"
//#include "opengl/mlx.h"

typedef struct  s_data
{
	void	*img;
	char	*addr;
	int	    bpp;
	int	    line_length;
	int	    endian;
}               t_data;


void		ft_error(void);
int			ft_check_input(char *s);
static int	_strcmp(char *s1, char *s2);
void        ft_mandelbrot(void);
int         iter_mandelbrot(double i, double j);
void	    my_mlx_pixel_put(t_data *img, int x, int y, int color);

int	press_esc_key(int key, void *p)
{
	if (key == 53)
		exit(0);
	return (0);
}

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

void ft_mandelbrot(void)
{
	void	*mlx;
	void	*win_ptr;
	int     x;
	int     y;
	t_data  img;

	mlx = mlx_init();
	if (!mlx)
		exit(1);
	win_ptr = mlx_new_window(mlx, 800, 600, "fractal");
	if (!win_ptr)
		exit(1);
	img.img = mlx_new_image(mlx, 800, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);

	x = -1;
	int iter;
	while (++x <= 800)
	{
		y = -1;
		while (++y <= 600)
		{
			iter = iter_mandelbrot((double)x, (double)y);
			if (iter != 100)
//				my_mlx_pixel_put(&img, x, y, 265 * iter);
				mlx_pixel_put(mlx, win_ptr, x, y, 265 * iter);
			else
				my_mlx_pixel_put(&img, x, y, 0x000000);
//			my_mlx_pixel_put(&img, x, y, get_color(iter_mandelbrot((double)x, (double)y)));
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
	i = (i - 400) / 200;
	j = (300 - j) / 150;
	iter = 1;
	x = i;
	y = j;
//	printf("|| i:%f, j:%f", i, j);
	while (iter < 100 && pow(x, 2.0) + pow(y, 2.0) <= 4)
	{
		x_n = x;
		x = pow(x, 2) - pow(y, 2) + i;
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
