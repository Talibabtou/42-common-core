/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:01:22 by gdumas            #+#    #+#             */
/*   Updated: 2024/09/12 19:04:08 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* Includes */
# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>

/* Config Parameters */
# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 1640
# endif
# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 950
# endif
# define MAX_WIDTH 2000
# define MAX_HEIGHT 1600
# define FOV 90
# define PLAYER_STEP_SIZE 0.04
# define PLAYER_ROT_SPEED 0.01
# define PI 3.1415926535

/* Colors Definitions */
# define RED		"\x1b[31;1m"
# define RESET		"\x1b[0m"

/* Messages Definitions */
# define E_NB_ARGS "Invalid number of arguments: usage: <exe> <map_file>\n"
# define E_PREPROCESS_MACRO "Invalid values for preprocess macros\n"
# define FILE_EXTENSION "Error\nWrong file extension. Cub3d need <*.cub>\n"
# define FILE_PATH "Error\nCannot open file.\n"
# define READ_ERROR "Error\nCannot read file.\n"
# define SYNTAX_LINE "Error\nInvalid syntax in configuration.\n"
# define TEXT_PATH "Error\nInvalid path for texture.\n"
# define COLOR_FORMAT_ERROR "Error\nInvalid color format.\n"
# define WRONG_CHR "Error\nInvalid character in map.\n"
# define MAP_ERROR "Error\nInvalid map format\n"
# define MAP_LINE_BREAK "Error\nMap cannot be separated by line breaks\n"
# define COLOR_DOUBLE_E "Error\nDuplicate color code\n"
# define EMPTY_START "Error\nNo starting position in map.\n"
# define MULT_START "Error\nMultiple starting positions in map.\n"
# define MALLOC_ERR_MSG "Malloc error\n"
# define SIZE_ERROR_GRID "Error\nMax size grid -> 100*100\n"
# define MLX_IMG_ERROR "Error\nMLX image creation failed\n"
# define MLX_PTR_ERROR "Error\nMLX pointer creation failed\n"
# define MLX_SPRITE_ERROR "Error\nMLX xpm image creation failed\n"
# define OVERLAY_ERROR "Error\nFailed to load overlay image\n"
# define CONFIG_ERROR "Error\nConfiguration file\nCub3d needs two colors and \
four textures without duplicates\n"
# define ID_TEXT_E "Error\nUnknown texture or colors identifier\n"

/* Enum Definition */
enum e_texture_index
{
	NORTH = 0,
	SOUTH,
	EAST,
	WEST,
	F,
	C
};

/* Structures Definitions */
typedef struct s_key_handl
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;

}	t_key_handl;

typedef struct s_fvector
{
	float	x;
	float	y;
}	t_fvector;

typedef struct s_dvector
{
	double	x;
	double	y;
}	t_dvector;

typedef struct s_ivector
{
	int	x;
	int	y;
}	t_ivector;

typedef struct s_player
{
	double		dir_angle;
	t_dvector	pos;
	t_dvector	dir;
	t_dvector	plane;
	t_dvector	movement;
	double		aspect_ratio;
	double		plane_fov;
	float		step_size;
	float		rot_speed;
}	t_player;

typedef struct t_dda
{
	double	dist;
	char	orientation;
}	t_dda;

typedef struct s_ray
{
	t_ivector	grid_pos;
	t_ivector	step_direction;
	t_dvector	true_pos;
	t_dvector	dir;
	t_dvector	delta_dist;
	t_dvector	side_dist;
}	t_ray;

typedef struct s_raycast
{
	double	camera_x;
	double	perp_wall_dist;
	t_ray	ray;
}	t_raycast;

typedef struct s_colors
{
	int		floor_color;
	int		ceiling_color;
	bool	floor;
	bool	ceiling;
}	t_colors;

typedef struct s_grid
{
	char	**content;
	int		width;
	int		height;
}	t_grid;

typedef struct s_image
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

typedef struct s_pixel_column
{
	int		tex_x;
	int		tex_y;
	int		y_start;
	int		y_end;
	int		height;
	int		color;
}	t_pixel_column;

typedef struct s_text_file
{
	char	**text;
	bool	no;
	bool	so;
	bool	we;
	bool	ea;
}	t_text_file;

typedef struct s_texture
{
	void			*reference;
	unsigned char	*pixels;
	int				x;
	int				y;
	int				bits_per_pixel;
	int				line_len;
	int				endian;
}	t_texture;

typedef struct s_overlay
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_overlay;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		width;
	int		height;
}	t_mlx;

typedef struct s_cub3d
{
	t_mlx			mlx;
	t_grid			grid;
	t_player		player;
	t_text_file		text_path;
	t_texture		text_img[4];
	t_colors		colors;
	t_image			framebuffer;
	t_key_handl		key;
	t_overlay		overlay;
}	t_cub3d;

/* Functions Definitions */
/** Error_handling **/
void	print_and_exit_error(char *msg);
void	free_and_exit_error(char *msg);
void	close_program(t_cub3d *cub3d, char *msg, int exit_code);

/** Init_structures **/
t_cub3d	*init_struct(void);
void	init_mlx(t_mlx *mlx);
void	init_image(t_cub3d *data);
void	init_sprites(t_cub3d *data);
void	init_overlay(t_cub3d *data);

/** Game_loop **/
void	game_event_loop(t_cub3d *data);

/** Controller/Keys_management **/
int		key_press_hook(int key, t_cub3d *data);
int		key_release_hook(int key, t_cub3d *data);
int		exit_button(t_cub3d *cub3d);

/** Frame/print_frame **/
void	put_pixel(t_image *img, int col, int line, int color);
void	draw_floor_ceil(t_cub3d *data, t_image *img);
void	add_pixels_col_to_img_txt(t_cub3d *data, int pixel_x,
			t_dda *wall_config, t_ray *ray);
void	draw_overlay_column(t_cub3d *data, int x);

/** Player **/
void	init_player(t_grid *grid, t_player *player);
int		modif_player(t_cub3d *data);
bool	try_move(t_grid *grid, t_dvector *pos, double dx, double dy);
bool	is_player(char c);
double	to_rad(int degrees);
void	process_player_movement(t_player *player);
void	process_player_dir(t_player *player);
void	process_player_plane(t_player *player);

/** Ray-casting/DDA **/
void	get_ray_config_dda(t_ray *ray);
void	init_ray(const double camera_x, t_player *player, t_ray *ray);
void	get_wall_config_dda(const t_grid *grid, t_ray *ray, t_dda *wall_config);

/** Parsing **/
void	process_config_and_map(t_cub3d *data, char *file);
void	extract_grid(t_grid *grid, char **grid_in_file);
bool	is_space_line(const char *str);
int		get_height_grid(char **grid);
int		get_max_width_grid(char **grid);
bool	is_valid_map(char **grid, int height);
bool	is_map_charset_valid(char **map);
bool	extrem_lines_are_valid(const char *line);
bool	is_map_enclosed_by_walls(char **grid, unsigned int height);
bool	is_char_adjacent_to_space(char **map, int x, int y);
void	extract_texture_path(t_text_file *text_path,
			char *line, int index_text);
int		get_texture_index_from_line(char *line);
void	check_double_text(int index, t_text_file *text);
void	save_text_path(t_text_file *text_path, int index, char *path);
char	**extract_file(char *file);
void	test_and_open_file(char *file);
int		find_start_map(char *str_file);
void	extract_color(t_colors *colors, char *line, int index_color);
void	check_double_color(t_colors *colors, int index);
void	save_color(t_colors *colors, int *rgb, int index_color);

#endif
