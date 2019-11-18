/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:48:10 by lshellie          #+#    #+#             */
/*   Updated: 2019/11/08 15:48:14 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void		print_name(t_fractol *f)
{
	if (f->type == MAND)
		mlx_string_put(f->mlx, f->win, 800, 0, 0xffffff, "Mandelbrot set");
	else if (f->type == JUL)
		mlx_string_put(f->mlx, f->win, 800, 0, 0xffffff, "Julia");
	else if (f->type == MY_1)
		mlx_string_put(f->mlx, f->win, 800, 0, 0xffffff, "My_1");
	else if (f->type == MY_2)
		mlx_string_put(f->mlx, f->win, 800, 0, 0xffffff, "My_2");
	else if (f->type == BRN_SP)
		mlx_string_put(f->mlx, f->win, 800, 0, 0xffffff, "Burning ship");
	else if (f->type == CEL_MAN)
		mlx_string_put(f->mlx, f->win, 800, 0, 0xffffff, "Celtic Mandelbrot");
	else if (f->type == CEL_MANBAR)
		mlx_string_put(f->mlx, f->win, 800, 0, 0xffffff, "Celtic Mandelbar");
	else if (f->type == CEL_PER)
		mlx_string_put(f->mlx, f->win, 800, 0, 0xffffff,
				"Celtic Perpendicular");
}

void		set_args(t_opcl *opcl, t_fractol *f)
{
	cl_int		ret;

	ret = clSetKernelArg(opcl->kernel,
			0, sizeof(cl_mem), &opcl->buf);
	ret |= clSetKernelArg(opcl->kernel,
			1, sizeof(double), &f->m_x);
	ret |= clSetKernelArg(opcl->kernel,
			2, sizeof(double), &f->m_y);
	ret |= clSetKernelArg(opcl->kernel,
			3, sizeof(double), &f->zoom);
	ret |= clSetKernelArg(opcl->kernel,
			4, sizeof(double), &f->dx);
	ret |= clSetKernelArg(opcl->kernel,
			5, sizeof(double), &f->dy);
	ret |= clSetKernelArg(opcl->kernel,
			6, sizeof(int), &f->iter);
	ret |= clSetKernelArg(opcl->kernel, 7, sizeof(int), &f->type);
	ret |= clSetKernelArg(opcl->kernel, 8, sizeof(double), &f->ms_x);
	ret |= clSetKernelArg(opcl->kernel, 9, sizeof(double), &f->ms_y);
	ret |= clSetKernelArg(opcl->kernel, 10, sizeof(double), &f->color);
	if (ret != CL_SUCCESS)
		terminate(opcl, CL_ERROR);
}

void		execute_kernel(t_opcl *opcl, t_fractol *f)
{
	int		ret;

	opcl->total_s = WIDTH * HEIGHT;
	opcl->local_s = 250;
	set_args(opcl, f);
	ret = clEnqueueNDRangeKernel(f->opcl->queue, f->opcl->kernel, 1,
			NULL, &f->opcl->total_s, &f->opcl->local_s, 0, NULL, NULL);
	if (ret != CL_SUCCESS)
		terminate(opcl, CL_ERROR);
}

void		print_info(t_fractol *f)
{
	mlx_string_put(f->mlx, f->win, 0,
			0, 0xffffff, "Controls:");
	mlx_string_put(f->mlx, f->win, 0,
			15, 0xffffff, "Arrows to move");
	mlx_string_put(f->mlx, f->win, 0,
			30, 0xffffff,
			"'+' and '-' to change iterations");
	mlx_string_put(f->mlx, f->win, 0,
			45, 0xffffff, "Mouse wheel to zoom");
	mlx_string_put(f->mlx, f->win, 0,
			60, 0xffffff, "'>' or '<' to change Fractal");
	mlx_string_put(f->mlx, f->win, 0,
			75, 0xffffff,
			"Space to change constant in Julia");
	mlx_string_put(f->mlx, f->win, 0, 90, 0xffffff,
				   "'C' to change color");
	mlx_string_put(f->mlx, f->win, 0,
			105, 0xffffff, "Esc - exit");
	print_name(f);
}

void		draw(t_fractol *f)
{
	ft_bzero(f->img->data, WIDTH * HEIGHT * 4);
	mlx_clear_window(f->mlx, f->win);
	execute_kernel(f->opcl, f);
	clEnqueueReadBuffer(f->opcl->queue, f->opcl->buf, CL_TRUE, 0,
			WIDTH * HEIGHT * 4, f->img->data, 0, NULL, NULL);
	mlx_put_image_to_window(f->mlx, f->win, f->img->id, 0, 0);
	print_info(f);
	mlx_do_sync(f->mlx);
}
