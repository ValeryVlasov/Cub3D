#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <mlx.h>

# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53

typedef struct s_flags
{
	int	NO_f;
	int	SO_f;
	int	WE_f;
	int	EA_f;
	int	C_f;
	int	F_f;
}			t_flags;

typedef struct s_tex
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		width;
	int		height;
	int		endian;
}	t_tex;

typedef struct	s_coord
{
	int x;
	int y;
	char direction;
}			t_coord;

typedef struct s_map
{
	int		player_set;
	t_coord	player_pos;//структура с координатами игрока и направлением взгляда
	char 	**map;//карта в виде массива(массив выровнен по ширине)
	t_list	*map_list;//карта в односвязном списке(не трогать)
}			t_map;

typedef struct s_cub
{
	int 	is_pressed;//нажата ли кнопка(для отключения залипания)
	char	*NO_path;//путь к файлу
	char	*SO_path;//путь к файлу
	char	*WE_path;//путь к файлу
	char	*EA_path;//путь к файлу
	t_tex	*NO_tex;//непосредственно текстура
	t_tex	*SO_tex;//непосредственно текстура
	t_tex	*WE_tex;//непосредственно текстура
	t_tex	*EA_tex;//непосредственно текстура
	t_tex	*background;//for test
	int 	F_color[3];//массив цветов пола
	int 	C_color[3];//массив цветов потолка
	t_map	*s_map;
	t_flags	flags;//for parser
	void		*mlx;
	void		*mlx_win;
}			t_cub;

void	draw_map(t_cub *cub);

//graphics_init.c
void	render_init(t_cub *cub);
void	textures_init(t_cub *cub);

//parser/parser.c
int	parser(t_cub *cub, char *file_name);

//parser_dims.c
int		parse_dimensions(t_cub *cub, char *line, int map_beg);

//parser_utils.c
int 	print_err(char *msg);
int		valid_color(char **colors);
char	*check_type(t_cub *cub, char *line);

//event_handl.c
int		cub_destroy(t_cub *cub);
int		key_press(int keycode, t_cub *cub);
int		key_release(int keycode, t_cub *cub);
int		end_game(t_cub *cub, char *msg);

//file.c
int		file_handl(t_cub *cub, char *file_name);

//gnl/get_next_line.c
int		get_next_line(int fd, char **line);

//delete_memory,c
void	*free_strarr(char **arr);
void	*delete_mem(void *ptr);


//validation/map.c
int 	fill_map(t_cub *cub);
void	fill_map_list(t_cub *cub, char *line);
int		matrix_size(char **map);
int		set_player_pos(t_cub *cub, char **map);

//validation/map_valid.c
int		is_map_invalid(t_cub *cub);
#endif
//исправить (x == y || x1 == y...) на ft_strchr()
//сделать проверку на пробелы внутри карты