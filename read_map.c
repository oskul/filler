/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oskulska <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 18:49:24 by oskulska          #+#    #+#             */
/*   Updated: 2018/05/11 18:49:27 by oskulska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		get_map_size(t_filler *filler)
{
	char	*str;
	char	*line;

	if (get_next_line(STDIN_FILENO, &line) < 1)
		exit(0);
	str = line;
	while (!ft_isdigit(*line))
		line++;
	filler->height = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	filler->width = ft_atoi(line);
	filler->min_dist = filler->height + filler->width;
	ft_strdel(&str);
	get_next_line(STDIN_FILENO, &line);
	ft_strdel(&line);
}

void		init_map(t_filler *filler)
{
	int		i;

	i = -1;
	if (filler->old_map == NULL && filler->map != NULL)
	{
		filler->old_map = (char **)malloc(sizeof(char *) * filler->height + 1);
		filler->old_map[filler->height] = NULL;
		while (++i < filler->height)
			filler->old_map[i] = NULL;
	}
	i = 0;
	if (filler->map == NULL)
	{
		filler->map = (char **)malloc(sizeof(char *) * filler->height + 1);
		filler->map[filler->height] = NULL;
		while (i < filler->height)
		{
			filler->map[i] = NULL;
			i++;
		}
	}
}

void		read_map(t_filler *filler)
{
	char	*line;
	int		i;

	i = -1;
	init_map(filler);
	if (filler->map)
		while (++i < filler->height)
			if (filler->map[i])
				filler->old_map[i] = ft_strdup(filler->map[i]);
	i = -1;
	ft_clear(filler->map);
	filler->map = NULL;
	init_map(filler);
	while (++i < filler->height)
	{
		if (get_next_line(STDIN_FILENO, &line) < 1)
			exit(0);
		filler->map[i] = ft_strdup(line + 4);
		ft_strdel(&line);
	}
	if (filler->first_read == 1)
		find_first_move(filler);
	else
		find_last_move(filler);
}
