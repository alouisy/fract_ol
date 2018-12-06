#include "fractol.h"

int			key_style(int keycode, t_params *prm)
{
	if (keycode == ESC)
		exit(0);
	else if (keycode == KEY_SPACE)
		prm->freeze = (prm->freeze == 0) ? 1 : 0;
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		prm->move_x -= (keycode == KEY_LEFT) ? -30 : 30;
	else if (keycode == KEY_UP || keycode == KEY_DOWN)
		prm->move_y += (keycode == KEY_UP) ? -30 : 30;
	else if (keycode == KEY_PLUS || keycode == KEY_LESS)
		prm->zoom += (keycode == KEY_PLUS) ? 2 : -2;
	else if (keycode == KEY_R || keycode == KEY_E)
		prm->r += (keycode == KEY_R) ? 5 : -5;
	else if (keycode == KEY_G || keycode == KEY_F)
		prm->g += (keycode == KEY_G) ? 5 : -5;
	else if (keycode == KEY_B || keycode == KEY_V)
		prm->b += (keycode == KEY_B) ? 5 : -5;
	else
		return (0);
//	printf("R %d | G %d | B %d\n", prm->r, prm->g, prm->b);
	mlx_destroy_image(prm->mlx, prm->img);
	ft_select_fractal(prm);
	return (0);
}

int			mouse_style(int button, int x, int y, t_params *prm)
{
	if (button == 4 && (x > 0 && x < prm->win_width) && (y > 0 && y < prm->win_height))
	{
		prm->zoom = (prm->zoom + 1) * 1.1;
		prm->move_x += (x - (prm->win_width / 2)) / prm->zoom / 1.5;
		prm->move_y += (y - (prm->win_height / 2)) / prm->zoom / 1.5;
	}
	if (button == 5 && (x > 0 && x < prm->win_width) && (y > 0 && y < prm->win_height))
		prm->zoom = (prm->zoom <= 1) ? 1 : (prm->zoom - 1) / 1.1;;
	if (button == 1 && (x > 0 && x < (prm->win_width / 2)))
		prm->move_x -= 15;
	if (button == 1 && (y > 0 && y < (prm->win_height / 2)))
		prm->move_y -= 15;
	if (button == 1 && (x > (prm->win_width / 2) && x < prm->win_width))
		prm->move_x += 15;
	if (button == 1 && (y > (prm->win_height / 2) && y < prm->win_height))
		prm->move_y += 15;
	if (x < 0 || x > prm->win_width || y < 0 || y > prm->win_height || (button != 4 && button != 5 && button != 1))
		return (0);
	mlx_destroy_image(prm->mlx, prm->img);
	ft_select_fractal(prm);
	return (0);
}

int		motion_hook(int x, int y, t_params *prm)
{
	if ((prm->freeze == 0) && (x > 0 && x < prm->win_width) && (y > 0 && y < prm->win_height))
	{
		prm->mouse_x = x;
		prm->mouse_y = y;
	//	printf("mouse_x = %f | mouse_y = %f\n", prm->mouse_x, prm->mouse_y);
		prm->redraw = 1;
		make_re(prm);
	}
	return (0);
}

int		expose_hook(t_params *prm)
{
	if (prm->redraw == 1)
	{
		printf("expose_hook\n");
		make_re(prm);
	}
	return (0);
}

void	set_hooks(t_params *prm)
{
	mlx_do_key_autorepeatoff(prm->mlx);
	//mlx_hook(prm->win, 2, 0, key_press_hook, prm);
	//mlx_hook(prm->win, 3, 0, key_release_hook, prm);
	//mlx_hook(prm->win, 4, 0, mouse_press_hook, prm);
	//mlx_hook(prm->win, 5, 0, mouse_release_hook, prm);
	mlx_hook(prm->win, 6, 0, motion_hook, prm);
//	mlx_hook(prm->win, 12, 0, expose_hook, prm);
	//mlx_hook(prm->win, 17, 0, exit_hook, prm);
}