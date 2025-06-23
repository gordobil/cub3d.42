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

// SIZES
# define SQ				32
# define HE				720
# define WD				1280
# define MINI_SCALE     0.2
# define MINI_TILE      (int)(SQ * MINI_SCALE)

// KEYS
# define W 				119
# define S 				115
# define D				100
# define A 				97
# define UP				65362
# define DOWN			65364
# define RIGHT			65363
# define LEFT			65361
# define ESC			65307
# define Q 				113

// ERRORS
# define ERROR_FATAL	1
# define ERROR_ARGS		2
# define ERROR_ELEMS	3
# define ERROR_MAP		4
# define ERROR_MLX		5

# define M_PI 3.14159265358979323846
# define DEG_TO_RAD(angle) ((angle) * M_PI / 180)

// COLORS
# define BLUE			"\033[1;34m"
# define YELLOW			"\033[0;32m"
# define WHITE			"\033[0m"

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
	int			start_x;
	int			start_y;
//         GAME         //
	void		*mlx;
	void		*window;
	t_player	*player;
}				t_cub3d;

/********************************* GAME **********************************/
// MLX
void 		draw_minimap(t_cub3d *cub3d);
int		mlx_management(t_cub3d cub3d);

/******************************** PARSING ********************************/
// FILE
int		get_path(char *path, t_cub3d *cub3d);
int		check_file(t_cub3d *cub3d);

// MAP_CHECK
int		map_check(t_cub3d *cub3d);

// MAP
int		tab_replace(t_cub3d *cub3d);
int		get_map(t_cub3d *cub3d, char *line);

// RAY_CAST
int render_frame(t_cub3d *cub3d);

// PARSING_UTILS
int		jump_empty(char *line, int i);
int		get_elem_length(int i, char *line);

// EXIT
int		free_matrix(char **matrix);
int		free_cub3d(t_cub3d *cub3d);
int		error(int code);

#endif
