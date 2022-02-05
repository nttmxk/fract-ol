#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
//#include <unistd.h>
#include "mms/mlx.h"
#include "opengl/mlx.h"

void		ft_error(void);
int			ft_check_input(char *s);
static int	_strcmp(char *s1, char *s2);


int main(int argc, char **argv)
{
	if (argc != 2 || ft_check_input(argv[1]))
		ft_error();

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
