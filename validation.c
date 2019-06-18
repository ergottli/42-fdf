/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmills <kmills@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 04:28:07 by kmills            #+#    #+#             */
/*   Updated: 2019/04/13 15:41:49 by ergottli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			is_hex(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int			val_char(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != ' ' && !is_hex(*str) && *str != ',')
			return (0);
		str++;
	}
	return (1);
}

t_point		valid(int fd, int flag)
{
	t_point	point;
	char	*line;
	int		ret;
	int		len;

	len = 0;
	point.y = 0;
	point.x = 0;
	ret = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		len = ft_num_counter(line);
		if (flag == 0)
		{
			point.x = len;
			flag = 1;
		}
		if (len != point.x || !val_char(line))
			flag = 3;
		++point.y;
	}
	free(line);
	if (flag == 3 || ret == -1)
		point.y = 0;
	return (point);
}

void		validation(t_fdf *fdf, char *str)
{
	int		fd;
	t_point	hi_wi;

	if ((fd = open(str, O_RDONLY)) <= 0)
		err_map();
	hi_wi = valid(fd, 0);
	close(fd);
	if (hi_wi.y == 0)
		err_map();
	map_maker(str, fdf, hi_wi.y);
}
