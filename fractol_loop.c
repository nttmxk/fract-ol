/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinoh <jinoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:48:31 by jinoh             #+#    #+#             */
/*   Updated: 2022/03/07 20:36:50 by jinoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main_loop(t_data *data)
{
	if (data->type == 0)
		ft_draw_mandelbrot(data);
	else if (data->type == 1)
		ft_draw_julia(data);
	else if (data->type == 2)
		ft_draw_ship(data);
	return (0);
}

int	mouse_button(int button, int x, int y, void *p)
{
	t_data	*data;

	data = (t_data *) p;
	if (data->press_f && data->type != 0)
	{
		data->a = (x - WIN_WIDTH / 2) * 4.0 / WIN_WIDTH;
		data->b = (WIN_HEIGHT / 2 - y) * 4.0 / WIN_HEIGHT;
		data->press_f = 0;
	}
	if (button == ZOOM_IN)
		ft_zoom(1.2, x, y, data);
	else if (button == ZOOM_OUT)
		ft_zoom(1 / 1.2, x, y, data);
	return (0);
}

void	ft_zoom(double zoom_rate, int x, int y, t_data *p)
{
	p->zoom_rate *= zoom_rate;
	if (x || y)
	{
		p->x = (int)((x + p->x) * zoom_rate) - WIN_WIDTH / 2;
		p->y = (int)((y + p->y) * zoom_rate) - WIN_HEIGHT / 2;
	}
	else
	{
		p->x = (int)(zoom_rate * (WIN_WIDTH / 2 + p->x)) - WIN_WIDTH / 2;
		p->y = (int)(zoom_rate * (WIN_HEIGHT / 2 + p->y)) - WIN_HEIGHT / 2;
	}
}

static void	ft_key(int key, t_data *p)
{
	if (key == A)
		p->x -= 100;
	else if (key == D)
		p->x += 100;
	else if (key == LEFT)
		p->x -= 25;
	else if (key == RIGHT)
		p->x += 25;
	else if (key == DOWN)
		p->y += 25;
	else if (key == UP)
		p->y -= 25;
	else if (key == PLUS)
		ft_zoom(1.2, 0, 0, p);
	else if (key == MINUS)
		ft_zoom(1 / 1.2, 0, 0, p);
	else if (key == F)
		p->press_f = 1;
	else if (key == C)
	{
		if (p->color == 2)
			p->color = -1;
		++p->color;
	}
}

int	press_key(int key, void *p)
{
	if ((key == A || key == D)
		|| (key >= LEFT && key <= UP)
		|| (key == PLUS || key == MINUS)
		|| (key == C || key == F))
		ft_key(key, (t_data *) p);
	else if (key == 53)
		exit(0);
	return (0);
}
