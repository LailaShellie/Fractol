/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:36:40 by lshellie          #+#    #+#             */
/*   Updated: 2019/11/08 16:39:47 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void		iter(int key, t_fractol *f)
{
	if (key == PLUS)
		f->iter += 1;
	else if (MINUS)
		f->iter -= 1;
	draw(f);
}

void		move(int key, t_fractol *f)
{
	if (key == UP)
		f->dy -= 10 / f->zoom;
	else if (key == DOWN)
		f->dy += 10 / f->zoom;
	else if (key == LEFT)
		f->dx -= 10 / f->zoom;
	else if (key == RIGHT)
		f->dx += 10 / f->zoom;
	draw(f);
}

void		change_fractol(int key, t_fractol *f)
{
	if (key == RIGHT_ARR)
	{
		if (f->type == SPIDER)
			f->type = MAND;
		else
			++f->type;
	}
	else if (key == LEFT_ARR)
	{
		if (f->type == MAND)
			f->type = SPIDER;
		else
			--f->type;
	}
	reset(f);
	draw(f);
}

void		change_color(int key, t_fractol *f)
{
	if (f->color == 3)
		f->color = 0;
	else
		++f->color;
	draw(f);
}

int			keyboard(int key, t_fractol *f)
{
	if (key == PLUS || key == MINUS)
		iter(key, f);
	if (key >= LEFT && key <= UP)
		move(key, f);
	if (key == SPACE)
		f->pause = f->pause ? 0 : 1;
	if (key == LEFT_ARR || key == RIGHT_ARR)
		change_fractol(key, f);
	if (key == COLOR)
		change_color(key, f);
	if (key == RESET)
	{
		reset(f);
		draw(f);
	}
	if (key == ESC)
		ft_close(f);
	return (0);
}
