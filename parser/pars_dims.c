#include "../cub3d.h"

int	check_img(t_cub *cub, char *path, char *type)
{
	char	*needle;
	int 	fd_img;

	needle = ft_strnstr(path, ".xpm", ft_strlen(path));
	if (!needle || ft_strlen(needle) != 4)
		return (1);
	fd_img = open(path, O_RDONLY);
	if (fd_img < 0/* && access(path, R_OK)*/)
		return (1);
	if (!ft_strcmp(type, "NO"))
	{
		cub->flags.NO_f = 1;
		cub->NO_path = ft_strdup(path);
	}
	else if (!ft_strcmp(type, "SO"))
	{
		cub->flags.SO_f = 1;
		cub->SO_path = ft_strdup(path);
	}
	else if (!ft_strcmp(type, "WE"))
	{
		cub->flags.WE_f = 1;
		cub->WE_path = ft_strdup(path);
	}
	else if (!ft_strcmp(type, "EA"))
	{
		cub->flags.EA_f = 1;
		cub->EA_path = ft_strdup(path);
	}
	return (0);
}

int	handl_direction(t_cub *cub, char **line_in_strs, char *type)
{
	if (ft_strcmp(type, "NO") && ft_strcmp(type, "SO")
		&& ft_strcmp(type, "WE") && ft_strcmp(type, "EA"))
		return (2);
	if (line_in_strs[2] != NULL)
		return (1);
	if (ft_strcmp(line_in_strs[0], "NO") && ft_strcmp(line_in_strs[0], "SO")
		&& ft_strcmp(line_in_strs[0], "WE") && ft_strcmp(line_in_strs[0], "EA"))
		return (1);
	return (check_img(cub, line_in_strs[1], type));
}

int	parse_f_c(t_cub *cub, char **colors, char *type)
{
	int 	i;

	i = -1;
	while (colors[++i])
	{
		if (!ft_strcmp(type, "C"))
		{
			cub->flags.C_f = 1;
			cub->C_color[i] = ft_atoi(colors[i]);
		}
		else if (!ft_strcmp(type, "F"))
		{
			cub->flags.F_f = 1;
			cub->F_color[i] = ft_atoi(colors[i]);
		}
	}
	free_strarr(colors);
	return (0);
}

int	handl_floor_ceil(t_cub *cub, char **line_in_strs, char *type)
{
	char	**colors;

	if (line_in_strs[2] != NULL)
		return (1);
	if (ft_strcmp(type, "F") && ft_strcmp(type, "C"))
		return (2);
	if (ft_strcmp(line_in_strs[0], type))
		return (1);
	colors = ft_split(line_in_strs[1], ',');
	if (matrix_size(colors) != 3)
	{
		free_strarr(colors);
		return (1);
	}
	if (valid_color(colors))
	{
		free_strarr(colors);
		return (1);
	}
	return (parse_f_c(cub, colors, type));
}

int	check_order(t_cub *cub, char *type)
{
	if (!ft_strcmp(type, "NO") && (!cub->flags.F_f && !cub->flags.C_f
		&& !cub->flags.EA_f && !cub->flags.SO_f && !cub->flags.WE_f))
		return (0);
	if (!ft_strcmp(type, "SO") && (!cub->flags.F_f && !cub->flags.C_f
		&& !cub->flags.EA_f && cub->flags.NO_f && !cub->flags.WE_f))
		return (0);
	if (!ft_strcmp(type, "WE") && (!cub->flags.F_f && !cub->flags.C_f
		&& !cub->flags.EA_f && cub->flags.SO_f && cub->flags.NO_f))
		return (0);
	if (!ft_strcmp(type, "EA") && (!cub->flags.F_f && !cub->flags.C_f
		&& cub->flags.NO_f && cub->flags.SO_f && cub->flags.WE_f))
		return (0);
	if (!ft_strcmp(type, "F") && (cub->flags.NO_f && !cub->flags.C_f
		&& cub->flags.EA_f && cub->flags.SO_f && cub->flags.WE_f))
		return (0);
	if (!ft_strcmp(type, "C") && (cub->flags.F_f && cub->flags.NO_f
		&& cub->flags.EA_f && cub->flags.SO_f && cub->flags.WE_f))
		return (0);
	return (1);
}

int	parse_dimensions(t_cub *cub, char *line, int map_beg)
{
	char	**line_in_strs;
	char	*type;

	if (!line || !line[0] || map_beg)
		return (1);
	line_in_strs = ft_split(line, ' ');
	if (!line_in_strs)
		return (1);
	type = check_type(cub, line);
	if (!type)
		return (1);
	if (check_order(cub, type))
		return (1);
	if (handl_direction(cub, line_in_strs, type) == 1)
	{
		free_strarr(line_in_strs);
		delete_mem(type);
		return (1);
	}
	if (handl_floor_ceil(cub, line_in_strs, type) == 1)
	{
		free_strarr(line_in_strs);
		delete_mem(type);
		return (1);
	}
	free_strarr(line_in_strs);
	delete_mem(type);
	return (0);
}