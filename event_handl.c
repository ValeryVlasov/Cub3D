#include "cub3d.h"

int	cub_destroy(t_cub *cub)
{
	(void)cub;
	exit(0);
}

static void	clear_tex(t_cub *cub, t_tex *texture)
{
	if (texture->img != 0)
		mlx_destroy_image(cub->mlx, texture->img);
	delete_mem(texture);
}

//static void	clear_game(t_gamedata *game)
//{
//	int	i;
//
//	i = -1;
//	if (game != 0)
//	{
//		if (game->collect != 0)
//			delete_mem(game->collect);
//		if (game->exit != 0)
//			my_free(game->exit);
//		if (game->map != 0)
//		{
//			while (++i < game->height)
//			{
//				if (game->map[i] != 0)
//					my_free(game->map[i]);
//			}
//			my_free(game->map);
//		}
//		my_free(game);
//	}
//}

int	end_game(t_cub *cub, char *msg)//закомментить тело, если мешает в работе программы
{
	if (cub != 0)
	{
		if (cub->NO_path != 0)
			clear_tex(cub, cub->NO_tex);
		if (cub->SO_path != 0)
			clear_tex(cub, cub->SO_tex);
		if (cub->WE_path != 0)
			clear_tex(cub, cub->WE_tex);
		if (cub->EA_path != 0)
			clear_tex(cub, cub->EA_tex);
//		if (cub->background != 0)
//			clear_tex(cub, cub->background);
//		clear_game(cub->game);
		if (cub->mlx_win != 0)
			mlx_destroy_window(cub->mlx, cub->mlx_win);
	}
	if (msg)
		write(1, msg, ft_strlen(msg));
	exit(0);
}


int	key_press(int keycode, t_cub *cub)//залипание невозможно
{
	if (cub->is_pressed)//чтобы можно было удерживать клавишу - удалить это условие
		return (0);
	cub->is_pressed = 1;
	if (keycode == KEY_UP || keycode == KEY_W)
		;
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		;
	else if (keycode == KEY_LEFT || keycode == KEY_A)
		;
	else if (keycode == KEY_RIGHT || keycode == KEY_D)
		;
	else if (keycode == KEY_ESC)
		end_game(cub, NULL);
	else
		return (0);
//	if (moved)
//		cub->game->movecount++;
//	else
//		return (0);
//	printf("Current movecount is %d\n", cub->game->movecount);
	return (0);
}

int	key_release(int keycode, t_cub *cub)
{
	(void)keycode;
	cub->is_pressed = 0;
	mlx_clear_window(cub->mlx, cub->mlx_win);
	draw_map(cub);//заново отрисовывать всю карту
	return (0);
}