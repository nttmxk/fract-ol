#ifndef FRACT_OL_H
# define FRACT_OL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "mlx.h"
# include <math.h>

# define	WIN_WIDTH	800
# define 	WIN_HEIGHT	600
# define 	ITER_MAX	100

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
void        ft_mandelbrot(void);
void        ft_julia(void);
int			get_color(int iter);
int         iter_mandelbrot(double i, double j);
void	    my_mlx_pixel_put(t_data *img, int x, int y, int color);





#endif
