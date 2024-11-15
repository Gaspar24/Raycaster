
#include "header.h"


void	move_forward_and_backwards(t_player *player, t_keys *keys)
{
	float	move_step;
	float	new_player_x;
	float	new_player_y;

	move_step = 0;
	if (keys->move_forward)
		move_step = player->move_speed;
	else if (keys->move_backward)
		move_step = -player->move_speed;
	new_player_x = player->player_x + cosf(player->player_a) * move_step;
	new_player_y = player->player_y + sinf(player->player_a) * move_step;
	if (*map[(int)(new_player_y)][(int)(new_player_x)] != '1')
	{
		player->player_x = new_player_x ;
		player->player_y = new_player_y;
	}
}

void	move_left_and_right(t_player *player, t_keys *keys)
{
	float	move_step;
	float	new_player_x;
	float	new_player_y;

	move_step = 0;
	if (keys->move_right)
		move_step = player->move_speed;
	else if (keys->move_left)
		move_step = -player->move_speed;
	new_player_x = player->player_x - sinf(player->player_a) * move_step;
	new_player_y = player->player_y + cosf(player->player_a) * move_step;
	if (*map[(int)(new_player_y)][(int)(new_player_x)] != '1')
	{
		player->player_x = new_player_x;
		player->player_y = new_player_y;
	}
}

void	rotate_player(t_player *player, t_keys *keys)
{
	if (keys->turn_left)
	{
		player->player_a -= player->turn_speed;
		if (player->player_a < 0)
			player->player_a += 2 * M_PI;
	}
	if (keys->turn_right)
	{
		player->player_a += player->turn_speed;
		if (player->player_a > 2 * M_PI)
			player->player_a -= 2 * M_PI;
	}
}

void	update_player_position(t_player *player, t_keys *keys)
{
	move_forward_and_backwards(player, keys);
	move_left_and_right(player, keys);
	rotate_player(player, keys);
}



int	key_press(int keysym, t_game *game)
{
	t_keys	*keys;

	keys = (game->keys);
	if (keysym == KEY_W)
		keys->move_forward = 1;
	else if (keysym == KEY_S)
		keys->move_backward = 1;
	else if (keysym == KEY_A)
		keys->move_left = 1;
	else if (keysym == KEY_D)
		keys->move_right = 1;
	else if (keysym == KEY_LEFT)
		keys->turn_left = 1;
	else if (keysym == KEY_RIGHT)
		keys->turn_right = 1;
	else if (keysym == KEY_ESC)
	{
		close_window(game);
	}
	return (0);
}

int	key_release(int keysym, t_game *game)
{
	t_keys	*keys;

	keys = (game->keys);
	if (keysym == KEY_W)
		keys->move_forward = 0;
	else if (keysym == KEY_S)
		keys->move_backward = 0;
	else if (keysym == KEY_A)
		keys->move_left = 0;
	else if (keysym == KEY_D)
		keys->move_right = 0;
	else if (keysym == KEY_LEFT)
		keys->turn_left = 0;
	else if (keysym == KEY_RIGHT)
		keys->turn_right = 0;
	return (0);
}

void	exit_error(t_game *game, char *str)
{
	printf("%s/n", str);
	mlx_destroy_display(game->mlx->mlx_p);
	free(game->mlx->mlx_p);
	exit(EXIT_FAILURE);
}

int	close_window(t_game *game)
{
	if (game->mlx->window)
		mlx_destroy_window(game->mlx->mlx_p, game->mlx->window);
	if (game->mlx->mlx_p)
	{
		mlx_destroy_display(game->mlx->mlx_p);
		free(game->mlx->mlx_p);
	}
	printf("GAME OVER!\n");
	free(game->player);
	exit(EXIT_SUCCESS);
	return (0);
}