/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmills <kmills@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 23:38:44 by ergottli          #+#    #+#             */
/*   Updated: 2019/04/13 15:55:41 by kmills           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		receive_colour(char *str)
{
	int i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
		++i;
	if (!str[i])
		return (268435455);
	if (str[i] == ',' && str[i + 1] && str[i + 2] &&
			str[i + 1] == '0' && str[i + 2] == 'x')
		return (ft_atoi_base(str + i + 3, 16));
	return (-1);
}

int		ft_num_counter(char *str)
{
	int num;
	int flag;

	num = 0;
	flag = 0;
	while (*str)
	{
		if (ft_isdigit(*str) && flag == 0)
		{
			++num;
			flag = 1;
		}
		else if (*str == 32)
			flag = 0;
		str++;
	}
	return (num);
}

void	first_colour(t_fdf *fdf)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			if (fdf->map.point[y][x].colour == 268435455)
			{
				fdf->map.point[y][x].colour = get_init_colour(fdf->map,
						0x5cc795, 0xe8e56e, fdf->map.point[y][x].z);
			}
			++x;
		}
		++y;
	}
}

void	var_in_map(t_fdf *fdf, char **num, int y)
{
	int x;

	x = 0;
	while (num[x])
	{
		(fdf->map.point)[y][x].x = x;
		(fdf->map.point)[y][x].y = y;
		(fdf->map.point)[y][x].z = ft_atoi(num[x]);
		(fdf->map.point)[y][x].k = (fdf->map.point)[y][x].z;
		(fdf->map.point)[y][x].kz = (fdf->map.point)[y][x].z;
		find_min_max(fdf->map.point[y][x].z, 0);
		fdf->map.point[y][x].colour = receive_colour(num[x]);
		free(num[x]);
		++x;
	}
	fdf->map.width = x;
}

int		map_maker(char *str, t_fdf *fdf, int y_count)
{
	int		fd;
	int		len;
	char	*line;
	char	**num;

	fd = open(str, O_RDONLY);
	fdf->map.point = (t_point**)malloc(sizeof(t_point*) * y_count);
	fdf->map.height = y_count;
	y_count = 0;
	len = 0;
	while (get_next_line(fd, &line) > 0)
	{
		len = ft_num_counter(line);
		(fdf->map.point)[y_count] = (t_point*)malloc(sizeof(t_point) * len);
		num = ft_strsplit(line, ' ');
		var_in_map(fdf, num, y_count);
		y_count++;
		free(line);
		free(num);
	}
	fdf->map.min = find_min_max(fdf->map.point[--y_count][0].z, 1);
	fdf->map.max = find_min_max(fdf->map.point[--y_count][0].z, 2);
	first_colour(fdf);
	return (1);
}
