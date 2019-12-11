/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:17:06 by lshellie          #+#    #+#             */
/*   Updated: 2019/11/04 14:17:07 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void		exit_with_usage(t_fractol *f)
{
	(void)f;
	ft_putendl("Usage:");
	ft_putendl("\tMandelbrot set:\t\t1");
	ft_putendl("\tJulia:\t\t\t2");
	ft_putendl("\tMy_1:\t\t\t3");
	ft_putendl("\tMy_2:\t\t\t4");
	ft_putendl("\tBurning ship:\t\t5");
	ft_putendl("\tCeltic Mandelbrot:\t6");
	ft_putendl("\tCeltic Mandelbar:\t7");
	ft_putendl("\tCeltic Perpendicular:\t8");
	ft_putendl("\tSpider:\t\t\t9");
	exit(0);
}

void		hooks(t_fractol *f)
{
	mlx_hook(f->win, 6, 0, mouse_move, f);
	mlx_hook(f->win, 17, 0, ft_close, f);
	mlx_hook(f->win, 5, 0, mouse_release, f);
	mlx_hook(f->win, 4, 0, mouse_press, f);
	mlx_hook(f->win, 2, 0, keyboard, f);
	mlx_loop(f->mlx);
}

void		manage_input(int argc, char **argv, t_fractol *f)
{
	if (argc == 2)
	{
		if (ft_atoi(argv[1]) == MAND)
			f->type = MAND;
		else if (ft_atoi(argv[1]) == JUL)
			f->type = JUL;
		else if (ft_atoi(argv[1]) == MY_1)
			f->type = MY_1;
		else if (ft_atoi(argv[1]) == MY_2)
			f->type = MY_2;
		else if (ft_atoi(argv[1]) == BRN_SP)
			f->type = BRN_SP;
		else if (ft_atoi(argv[1]) == CEL_MAN)
			f->type = CEL_MAN;
		else if (ft_atoi(argv[1]) == CEL_MANBAR)
			f->type = CEL_MANBAR;
		else if (ft_atoi(argv[1]) == CEL_PER)
			f->type = CEL_PER;
		else if (ft_atoi(argv[1]) == SPIDER)
			f->type = SPIDER;
		else
			exit_with_usage(f);
	}
	else
		exit_with_usage(f);
}

t_fractol	*init(int argc, char **argv)
{
	t_fractol		*f;

	if (!(f = ft_memalloc(sizeof(t_fractol))))
		return (0);
	manage_input(argc, argv, f);
	if (!(f->mlx = mlx_init()))
		return (0);
	if (!(f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "Fractol")))
		return (0);
	if (!(f->img = ft_memalloc(sizeof(t_img))))
		return (0);
	if (!(f->img->id = mlx_new_image(f->mlx, WIDTH, HEIGHT)))
		return (0);
	if (!(f->img->data = mlx_get_data_addr(f->img->id,
			&f->img->bpp, &f->img->size_line, &f->img->endian)))
		return (0);
	if (!(f->opcl = ft_memalloc(sizeof(t_opcl))))
		return (0);
	return (f);
}

int			main(int argc, char **argv)
{
	t_fractol		*f;

	if (!(f = init(argc, argv)))
		return (0);
	reset(f);
	init_cl(f->opcl);
	draw(f);
	hooks(f);
	return (0);
}
