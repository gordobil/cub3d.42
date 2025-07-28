/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:59:40 by ngordobi          #+#    #+#             */
/*   Updated: 2024/01/28 18:14:19 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <sys/stat.h>
# include <sys/time.h>
# include "../mlx/mlx.h"
# include "./libft.h"

// MATH
# define SQ					32
# define HE					720
# define WD					1280
# define MINI_SCALE			0.4
# define M_PI 				3.14159265358979323846

// KEYS
# define W 					119
# define S 					115
# define D					100
# define A 					97
# define UP					65362
# define DOWN				65364
# define RIGHT				65363
# define LEFT				65361
# define ESC				65307
# define Q 					113

// ERRORS
# define ERROR_FATAL		1
# define ERROR_ARGS			2
# define ERROR_ELEMS		3
# define ERROR_MAP			4
# define ERROR_MLX			5
# define ERROR_TEXTURES		6

// COLORS
# define WHITE				0xFFFFFFFF
# define GREY				0xFF666666
# define RED				0xFFFF0000
# define BLUE				0xFF0B5394
# define BLUE2				0xFF6FA8DC

typedef struct s_ray
{
	double		rx;
	double		ry;
	double		angle;
	char		type;
	float		distance;
}				t_ray;

typedef struct s_img
{
	void		*img;
	char		*addr;
	char		*path;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_texture
{
	t_img		*north;
	t_img		*south;
	t_img		*west;
	t_img		*east;
}				t_texture;

typedef struct s_player
{
	double		x;
	double		y;
	int			ang;
	int			speed;
	int			f_col;
	int			c_col;
}				t_player;

typedef struct s_cub3d
{
//         INFO         //
	int			fd;
	char		**map;
	char		**elements;
	char		start_pos;
	int			start_y;
	int			start_x;
//         KEYS         //
	int			w_key;
	int			s_key;
	int			a_key;
	int			d_key;
	int			r_key;
	int			l_key;
//         GAME         //
	void		*mlx;
	void		*window;
	int			sky_size;
	int			wall_size;
	int			wall_diff;
	t_player	*player;
	t_texture	*texture;
	t_img		*img;
	t_ray		ray[WD];
}				t_cub3d;

/*********************************** GAME ************************************/
// DRAW
void	my_pixel_put(t_img *img, int x, int y, int color);
void	draw_vertical_line(t_cub3d *cub3d, int x, int start, int end);
void	draw_square(t_cub3d *cub3d, int x, int y, int color);
void	draw_pointer(t_cub3d *cub3d);

// INIT_TEXTURES
int		init_textures(t_cub3d *cub3d);
int		load_texture(t_img *t, void *mlx);

// MINIMAP
void	draw_minimap(t_cub3d *cub3d);

// MLX
int		mlx_management(t_cub3d *cub3d);

// RENDER_FRAME
double	deg_to_rad(double ang);
int		render_frame(t_cub3d *cub3d, t_img *img, t_ray *ray);

// RENDER_TEXTURES
void	draw_textures(t_cub3d *cub3d, int x, int y);

// WALK
int		walk_forwards(t_cub3d *cub3d);
int		walk_backwards(t_cub3d *cub3d);
int		walk_right(t_cub3d *cub3d);
int		walk_left(t_cub3d *cub3d);

/********************************** PARSING **********************************/
// COLORS
int		get_colors(char **elems, t_player *player, int i, int j);

// FILE
int		get_path(char *path, t_cub3d *cub3d);
int		check_file(t_cub3d *cub3d);

// MAP_CHECK
int		map_check(t_cub3d *cub3d);

// MAP
int		tab_replace(t_cub3d *cub3d);
int		get_map(t_cub3d *cub3d, char *line);

// PARSING_UTILS
int		jump_empty(char *line, int i);
int		get_elem_length(int i, char *line);
void	close_file(int fd, char *line);

/************************************ SRC ************************************/
// EXIT
int		destroy_textures(t_cub3d *cub3d, int t);
int		free_cub3d(t_cub3d *cub3d, int error);
int		error(int code);

#endif
