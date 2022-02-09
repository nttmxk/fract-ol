#include "fract-ol.h"

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
	if (button == 5 || button == 4)
	{
		data->x += (x - WIN_WIDTH / 2) * data->zoom_rate / 2;
		data->y += (WIN_HEIGHT / 2 - y) * data->zoom_rate / 2;
		if (button == 5)
			data->zoom_rate *= 0.9;
		if (button == 4)
			data->zoom_rate *= 1.1;
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
	else if (key == 24)
		p->zoom_rate *= 0.9;
	else if (key == 27)
		p->zoom_rate *= 1.1;
	else if (key == 13) // F
		p->press_f = 1;
	else if (key == 15) // C
	{
		if (shift_color == 2)
			shift_color = -1;
		++shift_color;
	}
}

int	press_key(int key, void *p)
{
	if ((key == A || key == D)
		|| (key >= LEFT && key <= UP)
		|| (key == 24 || key == 27)
		|| (key == 13 || key == 15)) // 13 should be replaced with C. 15 should be replaced with F
		ft_key(key, (t_data *)p);
	else if (key == 53)
		exit(0);
	return (0);
}