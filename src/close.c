/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 19:05:42 by lshellie          #+#    #+#             */
/*   Updated: 2019/11/10 19:05:43 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void		free_cl(t_opcl *opcl)
{
	clReleaseContext(opcl->context);
	clReleaseCommandQueue(opcl->queue);
	clReleaseProgram(opcl->program);
	clReleaseKernel(opcl->kernel);
	clReleaseMemObject(opcl->buf);
}

void		reset(t_fractol *f)
{
	f->iter = 40;
	f->zoom = 150;
	f->dy = 0;
	f->dx = 0;
	f->ms_y = 0;
	f->ms_x = 0;
	f->pause = 1;
	f->m_y = (double)WIDTH / 2;
	f->m_x = (double)WIDTH / 2;
}

int			ft_close(t_fractol *f)
{
	free_cl(f->opcl);
	exit(0);
}

void		terminate(t_opcl *opcl, int flag)
{
	if (flag == CL_ERROR)
		ft_putendl("OpenCL Error");
	else if (flag == STD_ERROR)
		ft_putendl("File read Error");
	free_cl(opcl);
	exit(0);
}
