# define NEW 0
# define OLD 1
# define HEIGHT 1000
# define WIDTH 1000
# define MAND 1
# define JUL 2
# define MY_1 3
# define MY_2 4
# define BRN_SP 5
# define CEL_MAN 6
# define CEL_MANBAR 7
# define CEL_PER 8
# define SPIDER 9

int		set_colors(unsigned char o, unsigned char r, \
			unsigned char g, unsigned char b)
{
	return ((int)o << 24 | (int)r << 16 | (int)g << 8 | (int)b);
}

int 		choose_color(int i, int max, int color)
{
	int			red;
	int			blue;
	int			green;
	double		n;
	int			s = 100;

	n = (double)i / (double)max;
	red = (int)(9 * (1 - n) * pow(n, 3) * 255);
	green = (int)(15 * pow((1 - n), 2) * pow(n, 2) * 255);
	blue = (int)(8.5 * pow((1 - n), 3) * n * 255);
	if (color == 1)
		return (set_colors(0, red, blue, green));
	else if (color == 0)
		return (set_colors(0, blue, green, red));
	else if (color == 2)
		return (set_colors(0, blue, red, green));
	else if (color == 3)
		return (set_colors(0, red, green, blue));
	return (0);
}

__kernel void draw(__global char *data, double m_x, double m_y, double zoom,
		double dx, double dy, int iter, int type, double ms_x, double ms_y, int color)
{
    	double	re[2];
    	double	im[2];
    	double	c_re;
    	double	c_im;
    	int     i;
        size_t  id;
        int     x;
        int     y;

        id = get_global_id(0);
    	i = 0;
    	x = id % WIDTH;
    	y = id / HEIGHT;
    	c_re = (x - m_x) / zoom + dx;
        c_im = (y - m_y) / zoom + dy;
        re[NEW] = c_re;
        im[NEW] = c_im;
        if (type == MAND)
        {
    		while (re[NEW] * re[NEW] + im[NEW] * im[NEW] < 4 && ++i < iter)
   	 		{
    			re[OLD] = re[NEW];
        		im[OLD] = im[NEW];
        		im[NEW] = 2 * im[OLD] * re[OLD] + c_im;
        	    re[NEW] = re[OLD] * re[OLD] - im[OLD] * im[OLD] + c_re;
    		}
    	}
    	else if (type == JUL)
    	{
    		while (re[NEW] * re[NEW] + im[NEW] * im[NEW] < 4 && ++i < iter)
   	 		{
    			re[OLD] = re[NEW];
        		im[OLD] = im[NEW];
        		im[NEW] = 2 * im[OLD] * re[OLD] + ms_y;
        	    re[NEW] = re[OLD] * re[OLD] - im[OLD] * im[OLD] + ms_x;
    		}
    	}
    	else if (type == MY_1)
    	{
    		while (re[NEW] * re[NEW] + im[NEW] * im[NEW] < 4 && ++i < iter)
   	 		{
    			re[OLD] = re[NEW];
        		im[OLD] = im[NEW];
        		im[NEW] = -2 * im[OLD] * re[OLD] + c_im;
        	    re[NEW] = re[OLD] * re[OLD] - im[OLD] * im[OLD] + c_re;
    		}
    	}
    	else if (type == MY_2)
    	{
    		while (re[NEW] * re[NEW] + im[NEW] * im[NEW] < 4 && ++i < iter)
   	 		{
    			re[OLD] = re[NEW];
        		im[OLD] = im[NEW];
        		im[NEW] = 2 * im[OLD] * re[OLD] * re[OLD] + re[OLD] * re[OLD] * im[OLD] - im[OLD] * im[OLD] * im[OLD] + c_im;
        	    re[NEW] = re[OLD] * re[OLD] * re[OLD] - im[OLD] * im[OLD] * re[OLD] - 2 * re[OLD] * im[OLD] * im[OLD] + c_re;
    		}
    	}
		else if (type == BRN_SP)
		{
			while (re[NEW] * re[NEW] + im[NEW] * im[NEW] < 4 && ++i < iter)
			{
				re[OLD] = re[NEW];
				im[OLD] = im[NEW];
				im[NEW] = 2.0 * fabs(re[OLD] * im[OLD]) + c_im;
				re[NEW] = re[OLD] * re[OLD] - im[OLD] * im[OLD] + c_re;
			}
		}
		else if (type == CEL_MAN)
		{
			while (re[NEW] * re[NEW] + im[NEW] * im[NEW] < 4 && ++i < iter)
			{
				re[OLD] = re[NEW];
				im[OLD] = im[NEW];
				im[NEW] = 2.0 * re[OLD] * im[OLD] + c_im;
				re[NEW] = fabs(re[OLD] * re[OLD] - im[OLD] * im[OLD]) + c_re;
			}
		}
		else if (type == CEL_MANBAR)
		{
			while (re[NEW] * re[NEW] + im[NEW] * im[NEW] < 4 && ++i < iter)
			{
				re[OLD] = re[NEW];
				im[OLD] = im[NEW];
				im[NEW] = -2.0 * re[OLD] * im[OLD] + c_im;
				re[NEW] = fabs(re[OLD] * re[OLD] - im[OLD] * im[OLD]) + c_re;
			}
		}
		else if (type == CEL_PER)
		{
			while (re[NEW] * re[NEW] + im[NEW] * im[NEW] < 4 && ++i < iter)
			{
				re[OLD] = re[NEW];
				im[OLD] = im[NEW];
				im[NEW] = -2.0 * fabs(re[OLD]) * im[OLD] + c_im;
				re[NEW] = fabs(re[OLD] * re[OLD] - im[OLD] * im[OLD]) + c_re;
			}
		}
		else if (type == SPIDER)
		{
			while (re[NEW] * re[NEW] + im[NEW] * im[NEW] < 4 && ++i < iter)
			{
				re[OLD] = re[NEW];
				im[OLD] = im[NEW];
				re[NEW] = re[OLD] * re[OLD] - im[OLD] * im[OLD] + c_re;
				im[NEW] = 2.0 * re[OLD] * im[OLD] + c_im;
				c_im = c_im / 2 + im[NEW];
				c_re = c_re / 2 + re[NEW];
			}
		}
    	if (i < iter)
    	    ((__global int *)data)[id] = choose_color(i, iter, color);
    	else
            ((__global int *)data)[id] = 0;
}