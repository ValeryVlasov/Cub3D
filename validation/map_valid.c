#include "../cub3d.h"

int check_valid_sym(char **map)
{
	int i;
	int j;

	if (!map)
		return (1);
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!(map[i][j] == ' ' || map[i][j] == 'W' || map[i][j] == 'S' || map[i][j] == 'E'
				  || map[i][j] == 'N' || map[i][j] == '0' || map[i][j] == '1'))
			{
//				printf("sym = %c, i = %d, j = %d\n", map[i][j], i, j);
				return (1);
			}
		}
	}
	return (0);
}

int check_left_right(char **map, int height)
{
	int i;
	int j;
	int k;

	i = -1;
	while (++i < height)
	{
		j = 0;
		k = ft_strlen(map[i]) - 1;
		while (j < k && map[i][j] == ' ')
			j++;
		while (k > 0 && map[i][k] == ' ')
			k--;
		if (ft_strchr("0NSEW", map[i][k]) || ft_strchr("ONSEW", map[i][j]))
			return (1);
	}
	return (0);
}

int check_bot_top(char **map, int height)
{
	int i;
	int j;
	int k;

	j = -1;
	while (++j < ft_strlen(map[0]))
	{
		i = 0;
		while (i < height && map[i][j] == ' ')
			i++;
		k = height - 1;
		while (k > 0 && map[k][j] == ' ')
			k--;
		if (i >= height || k <= 0)
			return (1);
		if (map[i][j] && (map[i][j] != '1' || map[k][j] != '1'))
		{
//			printf("map[i][j] = %c, map[k][j] = %c, i = %d, j = %d, k = %d\n", map[i][j], map[k][j], i, j, k);
			return (1);
		}
	}
	return (0);
}

int not_surrounded(char **map)
{
	int i;
	int j;
	int height;

	i = 0;
	height = matrix_size(map);
	if (check_bot_top(map, height) || check_left_right(map, height))
	{
//		printf("bottop = %d, left right = %d\n", check_bot_top(map, height), check_left_right(map, height));
		return (1);
	}
	while (++i < height - 1)
	{
		j = 0;
		while (++j < ft_strlen(map[i]) - 1)
		{
			if (ft_strchr("0WNSE", map[i][j]))
			{
				if (map[i][j + 1] == ' ' || map[i][j - 1] == ' '
					|| map[i + 1][j] == ' ' || map[i - 1][j] == ' ')
				{
					printf("ij = %c\n", map[i][j]);
					printf("j+1 = %c, j-1= %c, i+1 = %d, i-1 = %c\n", map[i][j+1], map[i][j-1], map[i+1][j], map[i-1][j]);
					return (1);
				}
			}
		}
	}
	return (0);
}

int	is_map_invalid(t_cub *cub)
{
//	printf("11\n");
	if (check_valid_sym(cub->s_map->map))
		return (1);
//	printf("12\n");
	if (set_player_pos(cub, cub->s_map->map))
		return (1);
//	printf("13\n");
	if (not_surrounded(cub->s_map->map))
		return (1);
//	printf("14\n");
	if (cub->s_map->player_set == 0)
		return (1);
	return (0);
}