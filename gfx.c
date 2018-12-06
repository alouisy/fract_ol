#include "fractol.h"

void		mlx_put_pixel_to_image(int x, int y, unsigned int color, t_params *prm)
{
	int		pos;

	pos = (x * prm->bpp / 8) + (y * prm->size_line);
	if ((x > 0 && x < prm->win_width) && (y > 0 && y < prm->win_height))
	{
		prm->data[pos] = color;
		prm->data[pos + 1] = color >> 8;
		prm->data[pos + 2] = color >> 16;
	}
}

unsigned long createRGB(int r, int g, int b)
{   
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}