#include "cub3d.h"



void	cub_init(t_cub *cub)
{
	cub->is_pressed = 0;
	cub->NO_tex = NULL;
	cub->SO_tex = NULL;
	cub->WE_tex = NULL;
	cub->EA_tex = NULL;
	cub->background = NULL;
}

int	main(int argc, char **argv)//игру можно закрыть на ESC или на крестик, чистка памяти за мной(когда ты все сделаешь)
{
	t_cub cub;

	if (argc != 2)
		return (print_err("Wrong number of arguments.\nusage: ./cub3d <map_name>\n"));
	if (parser(&cub, argv[1]))
		return (1);
	cub_init(&cub);
	printf("NO = %s\nSO = %s\nWE = %s\nEA = %s\n", cub.NO_path, cub.SO_path, cub.WE_path, cub.EA_path);
	printf("F = %d,%d,%d\nC = %d,%d,%d\n", cub.F_color[0], cub.F_color[1], cub.F_color[2], cub.C_color[0], cub.C_color[1], cub.C_color[2]);
	for (int i = 0; cub.s_map->map[i]; i++)
	{
		printf("%s\t\ti = %d\n", cub.s_map->map[i], i);
	}
	render_init(&cub);
	textures_init(&cub);
	draw_map(&cub);
	mlx_hook(cub.mlx_win, 2, 1L << 0, key_press, &cub);
	mlx_hook(cub.mlx_win, 3, 1L << 1, key_release, &cub);
	mlx_hook(cub.mlx_win, 17, 1L << 17, cub_destroy, &cub);
	mlx_loop(cub.mlx);
	return (0);
}