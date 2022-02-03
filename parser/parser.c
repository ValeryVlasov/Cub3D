#include "../cub3d.h"

void	flag_init(t_cub *cub)
{
	cub->flags.C_f = 0;
	cub->flags.F_f = 0;
	cub->flags.NO_f = 0;
	cub->flags.SO_f = 0;
	cub->flags.EA_f = 0;
	cub->flags.WE_f = 0;
	cub->NO_path = NULL;
	cub->SO_path = NULL;
	cub->WE_path = NULL;
	cub->EA_path = NULL;
}

int	parser(t_cub *cub, char *file_name)
{
	char	*needle;//dont free
	int		ret;

	flag_init(cub);
	needle = ft_strnstr(file_name, ".cub", ft_strlen(file_name));
	if (needle == NULL || ft_strlen(needle) != 4)
	{
		print_err("Wrong name of map. ");
		return (print_err("Extension of file must me \".cub\"\n"));
	}
	ret = file_handl(cub, file_name);
	return (ret);
}