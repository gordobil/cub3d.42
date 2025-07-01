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
# define MINI_SCALE			0.2
# define MINI_TILE      	(int)(SQ * MINI_SCALE)
# define M_PI 				3.14159265358979323846
# define DEG_TO_RAD(angle)	((angle) * M_PI / 180)

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

// COLORS
# define WHITE				0x00FFFFFF
# define GREY				0x00666666
# define RED				0x00FF0000
# define BLUE				0x000B5394
# define BLUE2				0x006FA8DC


typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_player
{
	int			x;
	int			y;
	int			ang;
	int			speed;
}				t_player;

typedef struct s_cub3d
{
//         INFO         //
	char		*map_path;
	int			map_fd;
	char		**map;
	char		**elements;
	char		start_pos;
	int			start_y;
	int			start_x;
//         GAME         //
	void		*mlx;
	void		*window;
	t_player	*player;
	t_img		*img;
}				t_cub3d;

/*********************************** GAME ************************************/
// DRAW
//void	my_pixel_put(t_img *img, int x, int y, int color);
void	draw_vertical_line(t_cub3d *cub3d, int x, int start, int end);
void	draw_square(t_cub3d *cub3d, int x, int y, int color);
void 	draw_minimap(t_cub3d *cub3d);
void	draw_pointer(t_cub3d *cub3d);

// MLX
int		mlx_management(t_cub3d cub3d);

// RENDER_FRAME
int		render_frame(t_cub3d *cub3d);

// WALK
int		walk_forwards(t_cub3d *cub3d);
int		walk_backwards(t_cub3d *cub3d);

/********************************** PARSING **********************************/
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

// EXIT
int		free_matrix(char **matrix);
int		free_cub3d(t_cub3d *cub3d);
int		error(int code);

#endif
