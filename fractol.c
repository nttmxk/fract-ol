#include "fractol.h"

static int	_strcmp(char *s1, char *s2);

int	main(int argc, char **argv)
{
	if (argc < 2 || ft_check_input(argv[1]))
		ft_error();
	if (argc == 2 && !_strcmp(argv[1], "Mandelbrot"))
		ft_mandelbrot();
	else if (argc == 4 && !_strcmp(argv[1], "Julia"))
		ft_julia(ft_atof(argv[2]), ft_atof(argv[3]));
	else if (argc == 4 && !_strcmp(argv[1], "Burning ship"))
		ft_ship(ft_atof(argv[2]), ft_atof(argv[3]));
	else
		ft_error();
	return (0);
}

void	ft_error(void)
{
	printf("usage: \"./fractal [fractals]\"\n fractals :\n"
		   " --> Mandelbrot\n"
		   " --> Julia 'a' 'b'\n"
		   " --> Burning ship 'a' 'b'\n");
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

static int	_strcmp(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s1[++i] && s2[i])
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	return (s1[i] - s2[i]);
}
