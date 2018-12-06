#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx_macos/mlx.h"
# include <math.h>
# include "libft/includes/libft.h"
# include <stdio.h> //WAAAAAAAAAAAARRRRRRRRRRRRRRNNNNNNNNNNNNNNNIIIIIIIIIIIIIIIIIIIINNNNNNNNNNNNNNNNNNNGGGGGGGGGGGGGGGGGGGGGGG

# define WIN_WIDTH 750
# define WIN_HEIGHT 750
# define ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_PLUS 69
# define KEY_LESS 78
# define KEY_SPACE 49
# define RANGE_CHANGE(x,a,b,min,max) (((b)-(a))*((x)-(min))/((max)-(min)))+(a)

# define KEY_E 14
# define KEY_R 15
# define KEY_F 3
# define KEY_G 5
# define KEY_V 9
# define KEY_B 11

typedef struct	s_fractal
{
	double		re;
	double		im;
	double		new_re;
	double		new_im;
	double		pr;
	double		pi;
}				t_fractal;

typedef struct	s_params
{
	int			win_width;
	int			win_height;
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	int			mode;
	int			redraw;
	double		zoom;
	double		mouse_x;
	double		mouse_y;
	double		move_x;
	double		move_y;
	int			max_iter;
	t_fractal	*fractal;
	int			r;
	int			g;
	int			b;
	int			freeze;
}				t_params;

int				key_style(int keycode, t_params *prm);
int				mouse_style(int button, int	x, int y, t_params *prm);
int				motion_hook(int x, int y, t_params *prm);
int				expose_hook(t_params *prm);

void			mlx_put_pixel_to_image(int x, int y, unsigned int color, t_params *prm);
unsigned long	createRGB(int r, int g, int b);

void			fractal(t_params *prm);
void			make_re(t_params *prm);

t_params		*init_param(void);
void			ft_error(int code);
void			set_hooks(t_params *prm);

void			ft_select_fractal(t_params *prm);

int				ft_julia(double x, double y, t_params *prm);
int				julia_mouse(double x, double y, t_params *prm);

int				ft_mandel(double x, double y, t_params *prm);
int				mandel_mouse(t_params *prm);

int				ft_julia_cube(double x, double y, t_params *prm);
int				julia_cube_mouse(double x, double y, t_params *prm);

#endif