#include "raycasting.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_lenght + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	render_frame(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		cast_ray(game, x);  // Cast one ray per screen column
		x++;
	}
}
