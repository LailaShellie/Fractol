/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:30:40 by lshellie          #+#    #+#             */
/*   Updated: 2019/11/11 17:30:42 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void		zoom(int key, int x, int y, t_fractol *f)
{
	double		tmp;

	tmp = f->zoom;
	if (key == SCROLL_D)
		f->zoom /= 1.2;
	else if (key == SCROLL_U)
		f->zoom *= 1.2;
	if (tmp < f->zoom)
	{
		f->dx -= (f->m_x - x) * 1.2 / f->zoom;
		f->dy -= (f->m_y - y) * 1.2 / f->zoom;
	}
	else
	{
		f->dx -= (f->m_x - x) / 1.2 / f->zoom;
		f->dy -= (f->m_y - y) / 1.2 / f->zoom;
	}
	f->m_x = x;
	f->m_y = y;
	draw(f);
}

int			mouse_release(int key, int x, int y, t_fractol *f)
{
	if (key == MOUSE_LEFT)
	{
		f->in_move = 0;
	}
	draw(f);
	return (0);
}

int			mouse_press(int key, int x, int y, t_fractol *f)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		if (key == SCROLL_D || key == SCROLL_U)
			zoom(key, x, y, f);
		if (key == MOUSE_LEFT)
		{
			f->in_move = 1;
			f->m_xx = x;
			f->m_yy = y;
		}
	}
	return (0);
}

int			mouse_move(int x, int y, t_fractol *f)
{
	if ((f->type == JUL && !f->pause) || f->in_move)
	{
		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		{
			if (f->type == JUL && !f->pause)
			{
				f->ms_x = ((double)x - (double)WIDTH / 2) * 0.0008;
				f->ms_y = ((double)y + (double)HEIGHT / 2) * 0.0008;
			}
			else if (f->in_move)
			{
				f->dx -= (x - f->m_xx) / f->zoom;
				f->dy += (f->m_yy - y) / f->zoom;
				f->m_xx = x;
				f->m_yy = y;
			}
		}
		draw(f);
	}
	return (0);
}
