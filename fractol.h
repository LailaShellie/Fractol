/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:17:31 by lshellie          #+#    #+#             */
/*   Updated: 2019/11/04 14:17:32 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_FRACTOL_H
# define FRACT_OL_FRACTOL_H

# include "mlx.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

# define HEIGHT 1000
# define WIDTH 1000

# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define PLUS 69
# define MINUS 78
# define SCROLL_D 5
# define SCROLL_U 4
# define ESC 53
# define SPACE 49
# define LEFT_ARR 43
# define RIGHT_ARR 47
# define MOUSE_LEFT 1
# define COLOR 8
# define RESET 15

# define MAND 1
# define JUL 2
# define MY_1 3
# define MY_2 4
# define BRN_SP 5
# define CEL_MAN 6
# define CEL_MANBAR 7
# define CEL_PER 8
# define SPIDER 9

# define CL_ERROR 0
# define STD_ERROR 1

typedef struct		s_opcl
{
	cl_device_id		dev;
	cl_command_queue	queue;
	cl_context			context;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				buf;
	size_t				total_s;
	size_t				local_s;
}					t_opcl;

typedef struct		s_img
{
	void			*id;
	int				bpp;
	int				size_line;
	int				endian;
	char			*data;
}					t_img;

typedef struct		s_fractol
{
	void			*mlx;
	void			*win;
	t_img			*img;
	t_opcl			*opcl;
	int				iter;
	double			zoom;
	double			dx;
	double			dy;
	double			m_x;
	double			m_y;
	double			ms_x;
	double			ms_y;
	int				type;
	int				pause;
	int				color;
	int				in_move;
	double			m_xx;
	double			m_yy;
}					t_fractol;

void				draw(t_fractol *f);
int					keyboard(int key, t_fractol *f);
int					mouse_press(int key, int x, int y, t_fractol *f);
int					init_cl(t_opcl *opcl);
void				terminate(t_opcl *opcl, int flag);
int					ft_close(t_fractol *f);
int					mouse_move(int x, int y, t_fractol *f);
void				reset(t_fractol *f);
int					mouse_release(int key, int x, int y, t_fractol *f);

#endif
