#include "../cub3d.h"

static int	is_empty_line(char *line)
{
	if (!line)
		return (0);
	if (*line == '\n')
		return (1);
	while (*line)
	{
		if (*line != ' ' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

static int	parse_file_conf(t_cub *cub, char *line, int *map_begins, int *map_ends)
{
	if (ft_strnstr(line, "NO", ft_strlen(line))
		|| ft_strnstr(line, "SO", ft_strlen(line))
		|| ft_strnstr(line, "WE", ft_strlen(line))
		|| ft_strnstr(line, "EA", ft_strlen(line))
		|| ft_strnstr(line, "F", ft_strlen(line))
		|| ft_strnstr(line, "C", ft_strlen(line)))
		return (parse_dimensions(cub, line, *map_begins));
//	printf("6\n");
//printf("beg = %d, end = %d, line = %s\n", *map_begins, *map_ends, line);
	if (!is_empty_line(line) && *map_ends)
	{
		ft_lstclear(&cub->s_map->map_list, free);
		return (1);
	}
	else if (is_empty_line(line) && *map_begins)
	{
		*map_ends = 1;
		return (0);
	}
	else if (is_empty_line(line))
		return (0);
//	printf("7\n");
	*map_begins = 1;
	fill_map_list(cub, line);
//	printf("8\n");
	return (0);
}

int	init_map(t_cub *cub)
{
	cub->s_map = (t_map *)malloc(sizeof(t_map));
	if (!cub->s_map)
		return (1);
	cub->s_map->player_set = 0;
	cub->s_map->player_pos.direction = 0;
	cub->s_map->player_pos.x = -1;
	cub->s_map->player_pos.y = -1;
	cub->s_map->map = NULL;
	cub->s_map->map_list = NULL;
	return (0);
}

int	start_gnl(t_cub *cub, int fd, int *map_begins, int *map_ends)
{
	int 	gnl_flag;
	char	*line;

	line = NULL;
	gnl_flag = 1;
	while (gnl_flag)
	{
		gnl_flag = get_next_line(fd, &line);
		if (parse_file_conf(cub, line, map_begins, map_ends))
		{
			delete_mem(line);
			close(fd);
			return (print_err("Error. File misconfiguration\n"));
		}
		delete_mem(line);
	}
	return (0);
}

int	file_handl(t_cub *cub, char *file_name)
{
	int		fd;
	int 	map_begins;
	int 	map_ends;

	if (!file_name || !file_name[0])
		return (1);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (print_err("Error. Can not open file\n"));
	map_begins = 0;
	map_ends = 0;
	if (init_map(cub))
		return (print_err("Malloc failed\n"));
	if (start_gnl(cub, fd, &map_begins, &map_ends))
		return (print_err("Error. File misconfiguration\n"));
	close(fd);
	fill_map(cub);
	if (is_map_invalid(cub))
		return (print_err("Error. Invalid map\n"));
	return (0);
}