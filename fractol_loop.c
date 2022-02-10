#include "fractol.h"

int	main_loop(t_data *data)
{
	if (data->type == 0)
		ft_draw_mandelbrot(data);
	else if (data->type == 1)
		ft_draw_julia(data);
	return (0);
}

int	mouse_button(int button, int x, int y, void *p)
{
	t_data	*data;

	data = (t_data *)p;
	if (data->press_f && data->type != 0)
	{
		data->a = (x - WIN_WIDTH / 2) * 4.0 / WIN_WIDTH;
		data->b = (WIN_HEIGHT / 2 - y) * 4.0 / WIN_HEIGHT;
		data->press_f = 0;
	}
	if (button == ZOOM_IN || button == ZOOM_OUT)
	{
		data->x += (x - WIN_WIDTH / 2) * data->zoom_rate / 2;
		data->y += (WIN_HEIGHT / 2 - y) * data->zoom_rate / 2;
		if (button == ZOOM_IN)
			data->zoom_rate *= 0.9;
		if (button == ZOOM_OUT)
			data->zoom_rate *= 1.1;
	}
	return (0);
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
		p->zoom_rate *= 0.9;
	else if (key == MINUS)
		p->zoom_rate *= 1.1;
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
		ft_key(key, (t_data *)p);
	else if (key == 53)
		exit(0);
	return (0);
}
