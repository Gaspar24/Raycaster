
#include "header.h"

// This function is responsible for initializing the ray s step and side distances
// Rays move trough the grid step by step in the x or y direction, alos this fct 
// determinates the direcion for the ray and prepares the ray for stepping trough the grid
void	initialize_ray(t_player *player, t_rays *rays)
{
	// rays->ray_dir_x/y store the ray direction
	// a negative value means it s pointing left or down, a positive means right or up
	if(rays->ray_dir_x < 0)
	{
		rays->step_x = -1; // set based on the ray_dir, if negative direction is left
		// side_dist_x/y these determinates the distance from the player current 
		// to the first x or y grid line that will cross
		// it helps to decide which side x or y the ray will hit first
		rays->side_dist_x = (player->player_x
			- (int)player->player_x) * rays->delta_dist_x;
	}
	else
	{
		rays->step_x = 1;
		rays->side_dist_x = ((int)player->player_x
				+ 1.0 - player->player_x) * rays->delta_dist_x;
	}
	if (rays->ray_dir_y < 0)
	{
		rays->step_y = -1;
		rays->side_dist_y = (player->player_y
				- (int)player->player_y) * rays->delta_dist_y;
	}
	else
	{
		rays->step_y = 1;
		rays->side_dist_y = ((int)player->player_y
				+ 1.0 - player->player_y) * rays->delta_dist_y;
	}

}

// this function performs DDA which is a line-drawing algorithm that steps the ray 
// trough the grid one cell at the time untill it hits a wall
void	perform_dda(t_rays *rays, t_data *data, bool *hit_wall)
{
	(void)data;
	*hit_wall = false;
	while (!*hit_wall)
	{
		// by comaring the side_dist_x/y  it checks if 
		// the wall that was hit is vertical or  horizontal
		if (rays->side_dist_x < rays->side_dist_y)
		{
			rays->side_dist_x += rays->delta_dist_x;
			rays->map_x += rays->step_x;
			rays->hit_side = 0;
		}
		else
		{
			rays->side_dist_y += rays->delta_dist_y;
			rays->map_y += rays->step_y;
			rays->hit_side = 1;
		}
		if (*map[rays->map_y][rays->map_x] == '1')
			*hit_wall = true;
	}
}


// after the wall was hit this function calculates the perpendicular distance to the wall 
// and determinates the exatc hit location on the wall used for texture mapping
float	calculate_perpendicular_distance(t_rays *rays, t_player *player,
	float *wall_x)
{
	float	perp_wall_dist;

	if (rays->hit_side == 0)
	{
		perp_wall_dist = (rays->map_x - player->player_x
				+ (1 - rays->step_x) / 2) / rays->ray_dir_x;
		// wall_x stores the fractional x coordinate on the wall where the ray_hit
		*wall_x = player->player_y + perp_wall_dist * rays->ray_dir_y;
	}
	else
	{
		perp_wall_dist = (rays->map_y - player->player_y
				+ (1 - rays->step_y) / 2) / rays->ray_dir_y;
		*wall_x = player->player_x + perp_wall_dist * rays->ray_dir_x;
	}
	*wall_x -= floor(*wall_x);
	return (perp_wall_dist);
}

float	cast_rays(int x, t_player *player, t_data *data, float *wall_x)
{
	t_rays rays;

	float prep_wall_dsitance = 0;
	float ray_angle;
	bool hit_wall = false;
	//rays initial possition
	rays.map_x = (int)player->player_x;
	rays.map_y = (int)player->player_y;
	//ray angle determinates the angle from the current ray , adjusted by the fov
	ray_angle = (player->player_a - player->f_o_v / 2.0f)
		+ ((float)x / (float)S_W) * player->f_o_v;
	// day_dyr_x/y the X and Y directional components of the ray based on ray angle
	rays.ray_dir_x = cosf(ray_angle);
	rays.ray_dir_y = sinf(ray_angle);
	// the distances that ray must travel along X and Y to move from one grid line to the next
	rays.delta_dist_x = fabsf(1 / rays.ray_dir_x);
	rays.delta_dist_y = fabsf(1 / rays.ray_dir_y);
	initialize_ray(player, &rays);
	perform_dda(&rays, data, &hit_wall);
	prep_wall_dsitance = calculate_perpendicular_distance(&rays, player, wall_x);
	return (prep_wall_dsitance * cosf(ray_angle - player->player_a));
}