#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>

# include "./minilibx-linux/mlx.h"

# define S_W 1920
# define S_H 1080 
# define WIDTH 10
# define HEIGHT 10 
# define FOV_ANGLE (M_PI / 3)

//---------keys----------
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363



extern char *map[10][10];

typedef struct s_player
{
	float player_x;
	float player_y;
	float player_a;
	float f_o_v;
	float depth;
    float move_speed;
    float turn_speed;
}	t_player;

typedef struct s_keys
{
    int move_forward;
    int move_backward;
    int move_left;
    int move_right;
    int turn_left;
    int turn_right;
} t_keys;

typedef	struct s_data
{
	void		*img;
	char		*img_data;
	void		*wall_img; // test
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	float		wall_x;
	int			img_width;
	int			img_height;
	int			wall_color;
	char		*wall_data;
	void		*wall;

}	t_data;

typedef struct s_mlx	
{
	void			*img;	// the image
	void			*window; // mlx window
	void			*mlx_p;	// the mlx pointer
	t_player		*player; // pointer to player struct

}	t_mlx;

typedef struct s_rays
{
	int		step_x;
	int		step_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	ray_dir_x;
	float	ray_dir_y;
	int		map_x;
	int		map_y;
	float	*wall_x;
	int		hit_side;

}	t_rays;

typedef struct s_game
{
	t_mlx		*mlx;
	t_player	*player;
	t_data		*data;
	t_keys		*keys;
}	t_game;


// void	init_player(t_player *player);
t_player	*init_player(t_player *player);

void	init_keys(t_keys *keys);

void	redraw_image(t_game *game);
float	cast_rays(int x, t_player *player, t_data *data, float *wall_x);

int	key_press(int keysym, t_game *game);
int	key_release(int keysym, t_game *game);
void	update_player_position(t_player *player, t_keys *keys);

int	close_window(t_game *game);




#endif