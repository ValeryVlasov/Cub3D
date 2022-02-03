#include "../cub3d.h"

int	print_err(char *msg)
{
	write(1, msg, ft_strlen(msg));
	return (1);
}

int	valid_color(char **colors)
{
	int i;
	int j;

	i = -1;
	while (colors[++i])
	{
		j = -1;
		while (colors[i][++j])
		{
			if (ft_isdigit(colors[i][j]) == 0)
				return (1);
		}
		if (ft_atoi(colors[i]) > 255 || ft_atoi(colors[i]) < 0)
			return (1);
	}
	return (0);
}

char	*check_type(t_cub *cub, char *line)
{
	if (!ft_strncmp(line, "NO", 2) && !cub->flags.NO_f)
		return (ft_strdup("NO"));
	if (!ft_strncmp(line, "SO", 2) && !cub->flags.SO_f)
		return (ft_strdup("SO"));
	if (!ft_strncmp(line, "WE", 2) && !cub->flags.WE_f)
		return (ft_strdup("WE"));
	if (!ft_strncmp(line, "EA", 2) && !cub->flags.EA_f)
		return (ft_strdup("EA"));
	if (!ft_strncmp(line, "F", 1) && !cub->flags.F_f)
		return (ft_strdup("F"));
	if (!ft_strncmp(line, "C", 1) && !cub->flags.C_f)
		return (ft_strdup("C"));
	return (NULL);
}