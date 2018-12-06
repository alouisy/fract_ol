/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 16:18:42 by alouisy-          #+#    #+#             */
/*   Updated: 2017/02/21 16:18:44 by alouisy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	make_re(t_params *prm)
{
	prm->redraw = 0;
	mlx_destroy_image(prm->mlx, prm->img);
	ft_select_fractal(prm);
}

void	ft_select_fractal(t_params *prm)
{
	if (prm->mode == 1)
		julia_mouse(0, 0, prm);
	else if (prm->mode == 2)
		mandel_mouse(prm);
	else
		julia_cube_mouse(0, 0, prm);
}

int		julia_mouse(double x, double y, t_params *prm)
{
	prm->fractal->re = prm->mouse_x * 4.0 / prm->win_width - 2;
	prm->fractal->im = prm->mouse_y * 4.0 / prm->win_height - 2;
//	printf("re = %f | im = %f\n", prm->fractal->re, prm->fractal->im);
	return (ft_julia(x, y, prm));
}

int		julia_cube_mouse(double x, double y, t_params *prm)
{
	prm->fractal->re = prm->mouse_x * 4.0 / prm->win_width - 2;
	prm->fractal->im = prm->mouse_y * 4.0 / prm->win_height - 2;
//	printf("re = %f | im = %f\n", prm->fractal->re, prm->fractal->im);
	return (ft_julia_cube(x, y, prm));
}

int		mandel_mouse(t_params *prm)
{
	return (ft_mandel(0, 0, prm));
}

int	ft_julia(double x, double y, t_params *prm)
{
	int				i;
	double		temp;
	unsigned long	color = 0xFF33FF;

	prm->img = mlx_new_image(prm->mlx, prm->win_width, prm->win_height);
	prm->data = mlx_get_data_addr(prm->img, &prm->bpp, &prm->size_line, &prm->endian);
	while (y < prm->win_height)
	{
		while (x < prm->win_width)
		{
			prm->fractal->new_re = ((4.0 * x / prm->win_width - 2.0) / prm->zoom) + (prm->move_x / prm->win_width);
			prm->fractal->new_im = ((4.0 * y / prm->win_height - 2.0) / prm->zoom) + (-prm->move_y / prm->win_height);
			i = 0;
			while (prm->fractal->new_re * prm->fractal->new_re + prm->fractal->new_im * prm->fractal->new_im < 4.0 && i < prm->max_iter)
			{
				temp = prm->fractal->new_re * prm->fractal->new_re - prm->fractal->new_im * prm->fractal->new_im + prm->fractal->re;
				prm->fractal->new_im = 2 * prm->fractal->new_re * prm->fractal->new_im + prm->fractal->im;
				prm->fractal->new_re = temp;
				i++;
			}
			color = 0x0000FF * i;
			color = (i == prm->max_iter) ? 0 : color * i;
		//	color = createRGB(i % prm->r, prm->g, prm->b * (i < prm->max_iter));
			mlx_put_pixel_to_image(x, y, color, prm);
			x++;
		}
		x = 0;
		y++;
	}
    mlx_put_image_to_window(prm->mlx, prm->win, prm->img, 0, 0);
    return (1);
}

int	ft_julia_cube(double x, double y, t_params *prm)
{
	int				i;
	double		temp;
	unsigned long	color;

	prm->img = mlx_new_image(prm->mlx, prm->win_width, prm->win_height);
	prm->data = mlx_get_data_addr(prm->img, &prm->bpp, &prm->size_line, &prm->endian);
	while (y < prm->win_height)
	{
		while (x < prm->win_width)
		{
			prm->fractal->new_re = ((4.0 * x / prm->win_width - 2.0) / prm->zoom) + (prm->move_x / prm->win_width);
			prm->fractal->new_im = ((4.0 * y / prm->win_height - 2.0) / prm->zoom) + (-prm->move_y / prm->win_height);
			i = 0;
			while (prm->fractal->new_re * prm->fractal->new_re + prm->fractal->new_im * prm->fractal->new_im < 4.0 && i < prm->max_iter)
			{
				temp = prm->fractal->new_re * prm->fractal->new_re * prm->fractal->new_re - prm->fractal->new_im * prm->fractal->new_im * prm->fractal->new_re - (2 * prm->fractal->new_re * prm->fractal->new_im * prm->fractal->new_im) + prm->fractal->re;
				prm->fractal->new_im = 2 * prm->fractal->new_re * prm->fractal->new_re * prm->fractal->new_im - prm->fractal->new_im * prm->fractal->new_im * prm->fractal->new_im + prm->fractal->im;
				prm->fractal->new_re = temp;
				i++;
			}
			color = (i == prm->max_iter) ? 0 : i * 0xFF33FF;
			//color = createRGB(i % prm->r, prm->g, prm->b * (i < prm->max_iter));
			mlx_put_pixel_to_image(x, y, color, prm);
			x++;
		}
		x = 0;
		y++;
	}
    mlx_put_image_to_window(prm->mlx, prm->win, prm->img, 0, 0);
    return (1);
}

int	ft_mandel(double x, double y, t_params *prm)
{
	int				i;
	unsigned long	color;
	double			old_re;
	double			old_im;

	prm->img = mlx_new_image(prm->mlx, prm->win_width, prm->win_height);
	prm->data = mlx_get_data_addr(prm->img, &prm->bpp, &prm->size_line, &prm->endian);
	while (y < prm->win_height)
	{
		while (x < prm->win_width)
		{
			prm->fractal->pr = ((4.0 * x / prm->win_width - 2.0) / prm->zoom) + (prm->move_x / prm->win_width);
			prm->fractal->pi = ((4.0 * y / prm->win_height - 2.0) / prm->zoom) + (-prm->move_y / prm->win_height);
			prm->fractal->new_re = prm->fractal->new_im = old_re = old_im = 0;
			i = 0;
			while (prm->fractal->new_re * prm->fractal->new_re + prm->fractal->new_im * prm->fractal->new_im < 4.0 && i < prm->max_iter)
			{
				old_re = prm->fractal->new_re;
				old_im = prm->fractal->new_im;
				prm->fractal->new_re = old_re * old_re - old_im * old_im + prm->fractal->pr;
				prm->fractal->new_im = 2 * old_re * old_im + prm->fractal->pi;
				i++;
			}
			color = (i == prm->max_iter) ? 0 : i * 0xFF33FF;
		//	color = createRGB(i % prm->r, prm->g, prm->b * (i < prm->max_iter));
			mlx_put_pixel_to_image(x, y, color, prm);
			x++;
		}
		x = 0;
		y++;
	}
    mlx_put_image_to_window(prm->mlx, prm->win, prm->img, 0, 0);
    return (1);
}

void	fractal(t_params *prm)
{
	prm->mlx = mlx_init();
	prm->win = mlx_new_window(prm->mlx, prm->win_width, prm->win_height, "Fractol - 42");
	if (prm->mode == 1)
		ft_julia(0, 0, prm);
	else if (prm->mode == 2)
		ft_mandel(0, 0, prm);
	else if (prm->mode == 3)
		julia_cube_mouse(0, 0, prm);
	set_hooks(prm);
	mlx_mouse_hook(prm->win, mouse_style, prm);
	mlx_key_hook(prm->win, key_style, prm);
	mlx_loop(prm->mlx);
}

t_params	*init_param(void)
{
	t_params	*prm;

	prm = (t_params *)malloc(sizeof(t_params));
	prm->win_width = 800;
	prm->win_height = 800;
	prm->redraw = 0;
	prm->zoom = 1;
	prm->mouse_x = 0;
	prm->mouse_y = 0;
	prm->move_x = 0;
	prm->move_y = 0;
	prm->max_iter = 64;
	prm->fractal = (t_fractal *)malloc(sizeof(t_fractal));
	prm->fractal->re = -0.7;
	prm->fractal->im = 0.27015;
	prm->r = 256;
	prm->g = 5;
	prm->b = 55;
	prm->freeze = 0;
	return (prm);
}

void	ft_error(int code)
{
	if (code == 0)
	{
		ft_putendl("usage: ./fractol fractal_name");
		ft_putendl("   ex: ./fractol julia");
		ft_putendl("   ex: ./fractol mandel");
		ft_putendl("   ex: ./fractol 3th");
		exit(1);
	}
}

int		main(int argc, char const *argv[])
{
	t_params	*prm;

	prm = init_param();
	if (argc == 2 && ft_strcmp(argv[1], "julia") == 0)
		prm->mode = 1;
	else if (argc == 2 && ft_strcmp(argv[1], "mandel") == 0)
		prm->mode = 2;
	else if (argc == 2 && ft_strcmp(argv[1], "3th") == 0)
		prm->mode = 3;
	else
		ft_error(0);
	fractal(prm);
	return 0;
}