#include "header.h"



void	put_pixel_to_image(t_data *data, int x, int y, int color)
{
	int	pixel_position;

	pixel_position = (y * data->size_line) + (x * (data->bits_per_pixel / 8));
	if (pixel_position < 0 || pixel_position >= data->size_line * S_H
		- (data->bits_per_pixel / 8))
	{
		return ;
	}
	data->img_data[pixel_position] = color & 0xFF;
	data->img_data[pixel_position + 1] = (color >> 8) & 0xFF;
	data->img_data[pixel_position + 2] = (color >> 16) & 0xFF;
	if (data->bits_per_pixel == 32)
	{
		data->img_data[pixel_position + 3] = (color >> 24) & 0xFF;
	}
}

void	render_column(int x, int ceiling, int floor, t_data *data)
{
	int		y;
	int		tex_x;
	int		tex_y;
	char	*pixel_addr;

	y = 0;
	while (y < S_H)
	{
		if (y < ceiling)
			put_pixel_to_image(data, x, y, 0x00FF00);
		else if (y >= ceiling && y <= floor)
		{
			tex_x = (int)(data->wall_x * data->img_width);
			tex_y = (y - ceiling) * data->img_height / (floor - ceiling);
			pixel_addr = data->wall_data + (tex_y * data->img_width
					* (data->bits_per_pixel / 8))
				+ (tex_x * (data->bits_per_pixel / 8));
			data->wall_color = *(int *)pixel_addr;
			put_pixel_to_image(data, x, y, data->wall_color);
			// put_pixel_to_image(data, x, y, 0x000000);
		}
		else
			put_pixel_to_image(data, x, y, 0xFF0000);
		y++;
	}
}

void	render_textures(int x, float distance_to_wall, t_data *data, float wall_x)
{
	int	ceiling;
	int	floor;

	ceiling = (float)(S_H / 2.0) - (S_H / (float)distance_to_wall);
	floor = S_H - ceiling;
	data->wall_x = wall_x;
	render_column(x, ceiling, floor,data);

}
void	redraw_image( t_game *game)
{
	int x;
	float distance_to_wall;
	float	wall_x;


	x = 0;
	distance_to_wall = 0;
	wall_x = 0;
	//-creating new immage
	game->data->img = mlx_new_image(game->mlx->mlx_p, S_W, S_H);
	game->data->img_data = mlx_get_data_addr(game->data->img,
			&game->data->bits_per_pixel,
			&game->data->size_line, &game->data->endian);
	while(x < S_W)
	{
		distance_to_wall = cast_rays(x, game->player, game->data, &wall_x);
		render_textures(x, distance_to_wall, game->data,wall_x);
		x += 2;
	}
	//display the immage
	mlx_put_image_to_window(game->mlx->mlx_p, game->mlx->window,
		game->data->img, 0, 0);
	//distroy the immage
	mlx_destroy_image(game->mlx->mlx_p, game->data->img);
}