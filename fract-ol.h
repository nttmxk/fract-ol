#ifndef FRACT_OL_H
# define FRACT_OL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <mlx.h>
# include <math.h>

# define	WIN_WIDTH	800
# define 	WIN_HEIGHT	600
# define 	ITER_MAX	100
# define    LEFT        123
# define    RIGHT       124
# define    DOWN        125
# define    UP          126
# define    SHIFT_C       0
 // Julia -0.8 -0.27
 // Mandelbrot
typedef struct  s_data
{
	void    *mlx;
	void    *win;
	void	*img;
	char	*addr;
	double  a;
	double  b;
	int     type;
	int     x;
	int     y;
	int	    bpp;
	int	    line_length;
	int	    endian;
	double  zoom_rate;
}               t_data;

void		ft_error(void);
int			ft_check_input(char *s);
void        ft_mandelbrot(void);
int         iter_mandelbrot(double i, double j, double k);
void        ft_draw_mandelbrot(t_data *img);

void        ft_julia(double a, double b);
int         iter_julia(double x, double y, t_data *data);
void        ft_draw_julia(t_data *data);

int			get_color(int iter);
void	    my_mlx_pixel_put(t_data *img, int x, int y, int color);

void data_init(t_data *data);
int main_loop(t_data *img);

#endif
