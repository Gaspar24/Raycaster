
#include "header.h"

char *map[WIDTH][HEIGHT] = {
    {"1", "1", "1", "1", "1", "1", "1", "1", "1", "1"},
    {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
    {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
    {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
    {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
    {"1", "0", "0", "0", "N", "0", "0", "0", "0", "1"},
    {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
    {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
    {"1", "0", "0", "0", "0", "0", "0", "0", "0", "1"},
    {"1", "1", "1", "1", "1", "1", "1", "1", "1", "1"}
};


void load_texture(t_data *data, t_mlx *mlx)
{
	data->wall = mlx_xpm_file_to_image(mlx->mlx_p,"./texture/NO.xpm", &data->img_width, &data->img_height);
	if(!data->wall)
	{
		printf("error wall\n");
		exit(1);
	}
	data->wall_data = mlx_get_data_addr(data->wall, &data->bits_per_pixel, &data->size_line, &data->endian);
	if(!data->wall_data)
	{
		printf("error data_wall\n");
		exit(1);
	}
}

void	startup(t_player **player, t_mlx *mlx, t_keys *keys, t_data *data)
{
	(void)mlx;
	*player = init_player(*player);
	load_texture(data,mlx);
	init_keys(keys);
}

int	update_player(t_game *game)
{
	update_player_position(game->player, (game->keys));
	redraw_image(game);
	return (0);
}
void	game_loop(t_mlx *mlx, t_game *game)
{
	mlx->window = mlx_new_window(mlx->mlx_p, S_W, S_H, "Maze Runner");
	mlx_hook(mlx->window, 2, 1L << 0, key_press, game);
	mlx_hook(mlx->window, 3, 1L << 1, key_release, game);
	mlx_hook(mlx->window, 17, 1L << 17, close_window, game);
	mlx_loop_hook(mlx->mlx_p, update_player, game);
	mlx_loop(mlx->mlx_p);
}

int main(void)
{
	t_mlx		mlx;
	t_player	*player;
	t_keys		keys;
	t_game		game;
	t_data		data;


	mlx.mlx_p = mlx_init();
	startup(&player,&mlx, &keys, &data);
	game.player = player;
	game.mlx = &mlx;
	game.keys = &keys;
	game.data = &data;
	game_loop(&mlx, &game);
	return(0);
}