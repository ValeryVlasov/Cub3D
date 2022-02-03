#include "../cub3d.h"

int	set_player_pos(t_cub *cub, char **map)
{
	int	i;
	int j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'W' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'N')
			{
				if (cub->s_map->player_set)
					return (1);
				cub->s_map->player_set = 1;
				cub->s_map->player_pos.direction = map[i][j];
				cub->s_map->player_pos.x = j;
				cub->s_map->player_pos.y = i;
			}
		}
	}
	return (0);
}

int matrix_size(char **map)
{
	int i;

	i = 0;
	if (!map)
		return (0);
	while (map[i])
		i++;
	return (i);
}

char	**add_spaces(char **map)
{
	char	*temp;
	char	*save;
	int 	max_len;
	int 	i;

	i = -1;
	max_len = 0;
	while (map[++i])
	{
		if (ft_strlen(map[i]) > max_len)
			max_len = ft_strlen(map[i]);
	}
	i = -1;
	while (map[++i])
	{
		if (ft_strlen(map[i]) < max_len)
		{
			save = map[i];
			temp = ft_calloc(max_len - ft_strlen(map[i]) + 1, sizeof(char));
			temp = ft_memset(temp, ' ', max_len - ft_strlen(map[i]));
			map[i] = ft_strjoin(map[i], temp);
			delete_mem(save);
		}
	}
	return (map);
}

int	fill_map(t_cub *cub)
{
	int 	size;
	int 	i;
	t_list	*temp;

	temp = cub->s_map->map_list;
	size = 0;
	while (temp)
	{
		size++;
		temp = temp->next;
	}
	temp = cub->s_map->map_list;
	cub->s_map->map = (char **)malloc(sizeof(char *) * (size + 1));
	if (!cub->s_map->map)
		return (print_err("Malloc failed\n"));
	cub->s_map->map[size] = NULL;
	i = 0;
	while (temp)
	{
		cub->s_map->map[i++] = ft_strdup(temp->content);
		temp = temp->next;
	}
	ft_lstclear(&cub->s_map->map_list, free);
	cub->s_map->map = add_spaces(cub->s_map->map);
	return (0);
}

void	fill_map_list(t_cub *cub, char *line)
{
	t_list	*temp;

//	printf("99\n");
	if (!cub->s_map->map_list)
		cub->s_map->map_list = ft_lstnew(ft_strdup(line));
	else
	{
//		printf("900\n");
		temp = ft_lstlast(cub->s_map->map_list);
		temp->next = ft_lstnew(ft_strdup(line));
	}
//	printf("999\n");
}