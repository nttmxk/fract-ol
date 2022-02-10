/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinoh <jinoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:48:25 by jinoh             #+#    #+#             */
/*   Updated: 2022/02/10 15:48:26 by jinoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>

# define	WIN_WIDTH	800
# define	WIN_HEIGHT	600
# define	ITER_MAX	100
# define	A			0
# define	D			2
# define	F			3
# define	C			8
# define	LEFT		123
# define	RIGHT		124
# define	DOWN		125
# define	UP			126
# define	PLUS        24
# define	MINUS       27
# define	ZOOM_IN     5
# define	ZOOM_OUT	4

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		type;
	int		x;
	int		y;
	int		press_f;
	int		color;
	int		bpp;
	int		line_length;
	int		endian;
	double	a;
	double	b;
	double	zoom_rate;
}	t_data;

/*
 * fractol.c
 */
void		ft_error(void);
int			ft_check_input(char *s);
/*
 * mandelbrot.c
 */
void		ft_mandelbrot(void);
void		ft_draw_mandelbrot(t_data *img);
int			iter_mandelbrot(double i, double j, double k);
/*
 * julia.c
 */
void		ft_julia(double a, double b);
void		ft_draw_julia(t_data *data);
int			iter_julia(double x, double y, t_data *data);
/*
 * burning_ship.c
 */
void		ft_ship(double a, double b);
void		ft_draw_ship(t_data *data);
int			iter_ship(double x, double y, t_data *data);
/*
 * fractol_utils.c
 */
int			get_color(int iter, int shift_color);
void		my_mlx_pixel_put(t_data *img, int x, int y, int color);
void		data_init(t_data *data);
double		ft_atof(const char *str);
/*
 * fractol_loop.c
 */
int			main_loop(t_data *img);
int			mouse_button(int button, int x, int y, void *p);
int			press_key(int key, void *p);
void		ft_zoom(double zoom_rate, int x, int y, t_data *p);
#endif
