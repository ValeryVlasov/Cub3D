#include "cub3d.h"

static void	textures_load(t_cub *cub, t_tex **img, char *path)
{
	int	width;
	int	height;

	width = 0;
	height = 0;
	*img = (t_tex *)malloc(sizeof(t_tex));
	if (!(*img))
		end_game(cub, "Error: can't malloc\n");
	(*img)->img = mlx_xpm_file_to_image(cub->mlx,
										path, &width, &height);
	if ((*img)->img == 0)
		end_game(cub, "Error: can't load xpm file\n");
	(*img)->height = height;
	(*img)->width = width;
	(*img)->addr = mlx_get_data_addr((*img),
									 &(*img)->bits_per_pixel,
									 &(*img)->line_length, &(*img)->endian);
}

void	textures_init(t_cub *cub)
{
	textures_load(cub, &cub->NO_tex, cub->NO_path);
	textures_load(cub, &cub->SO_tex, cub->SO_path);
	textures_load(cub, &cub->WE_tex, cub->WE_path);
	textures_load(cub, &cub->EA_tex, cub->EA_path);
	textures_load(cub, &cub->background, "./textures/background.xpm");
}

void	render_init(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (cub->mlx == 0)
		end_game(cub, "Error: mlx_init() failed\n");
	cub->mlx_win = mlx_new_window(cub->mlx,
								  ft_strlen(cub->s_map->map[0]) * 32,/*width*/
								  matrix_size(cub->s_map->map) * 32, "Cub3D");//height
}

static void	put_tex_to_window(t_cub *cub, void *img, int x, int y)
{
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, img, x * 32, y * 32);
}

void	draw_map(t_cub *cub)//короче тут надо будет чуть по-другому отрисовывать, это уже с твоей части, можешь полностью переписать
{
	int	i;
	int	j;

	i = -1;
	while (++i < matrix_size(cub->s_map->map))
	{
		j = -1;
		while (++j < ft_strlen(cub->s_map->map[0]))
		{
			put_tex_to_window(cub, cub->background->img, j, i);
			if (cub->s_map->map[i][j] == '1')
			{
//				put_tex_to_window(cub, cub->walls->img, j, i);
				put_tex_to_window(cub, cub->NO_tex->img, j, i);

			}
			else if (cub->s_map->map[i][j] == 'S')
			{
//				put_tex_to_window(cub, cub->collect->img, j, i);
				put_tex_to_window(cub, cub->SO_tex->img, j, i);

			}
			else if (cub->s_map->map[i][j] == 'W')
			{
//				put_tex_to_window(cub, cub->exit->img, j, i);
				put_tex_to_window(cub, cub->WE_tex->img, j, i);

			}
			else if (cub->s_map->map[i][j] == 'E')
			{
//				put_tex_to_window(cub, cub->player->img, j, i);
				put_tex_to_window(cub, cub->EA_tex->img, j, i);

			}
		}
	}
}