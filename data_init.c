
#include "header.h"

int	get_player_position(char c)
{
    int	y;
    int	x;

    y = 0;
    while (y < WIDTH)
    {
        x = 0;
        while (x < HEIGHT)
        {
            if (*map[y][x] == 'N')
            {
                if (c == 'x')
                    return (x);
                else
                    return (y);
            }
            x++;
        }
        y++;
    }
    return (0);
}


t_player	*init_player(t_player *player)
{
    player = (t_player *)malloc(sizeof(t_player));
	if (player == NULL)
		return (NULL);
	player->player_x = get_player_position('x') + 0.3f;
	player->player_y = get_player_position('y') + 0.3f;
	player->player_a = 4.699998f;
	player->f_o_v = 3.14159 / 3;   // PI /3 = 60
	player->depth = 10;
	player->move_speed = 0.08;
	player->turn_speed = 0.05f;
    return(player);
}

void	init_keys(t_keys *keys)
{
	keys->move_forward = 0;
	keys->move_backward = 0;
	keys->move_left = 0;
	keys->move_right = 0;
	keys->turn_left = 0;
	keys->turn_right = 0;
}