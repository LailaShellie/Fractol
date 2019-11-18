/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 16:32:36 by lshellie          #+#    #+#             */
/*   Updated: 2019/11/09 16:32:37 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

char	*load_src(char *path)
{
	int		fd;
	char	buf[100];
	char	*tmp;
	char	*src;

	src = 0;
	if ((fd = open(path, O_RDONLY)) < 0)
		return (0);
	while (read(fd, buf, 99) > 0)
	{
		if (!src)
			src = ft_strdup(buf);
		else
		{
			tmp = src;
			src = ft_strjoin(tmp, buf);
			free(tmp);
		}
		ft_bzero(buf, 100);
	}
	return (src);
}

void	get_kernel(t_opcl *opcl)
{
	int		ret;
	char	buf[10000];

	ret = clBuildProgram(opcl->program, 1,
			&opcl->dev, 0, 0, 0);
	if (CL_SUCCESS != ret)
	{
		clGetProgramBuildInfo(opcl->program, opcl->dev,
				CL_PROGRAM_BUILD_LOG, 100000, &buf, NULL);
		ft_putstr(buf);
		terminate(opcl, CL_ERROR);
	}
	if (!(opcl->kernel = clCreateKernel(opcl->program,
			"draw", &ret)))
		terminate(opcl, CL_ERROR);
}

int		get_device(t_opcl *opcl)
{
	int					ret;
	cl_platform_id		platformid;
	cl_uint				pltf_num;
	cl_uint				dev_num;

	if ((ret = clGetPlatformIDs(0, 0, &pltf_num)) != CL_SUCCESS)
		terminate(opcl, CL_ERROR);
	if ((ret |= clGetPlatformIDs(pltf_num, &platformid, 0)) != CL_SUCCESS)
		terminate(opcl, CL_ERROR);
	if ((ret |= clGetDeviceIDs(platformid,
			CL_DEVICE_TYPE_GPU, 0, 0, &dev_num)) != CL_SUCCESS)
		terminate(opcl, CL_ERROR);
	if ((ret |= clGetDeviceIDs(platformid,
			CL_DEVICE_TYPE_GPU, dev_num, &opcl->dev, 0)) != CL_SUCCESS)
		terminate(opcl, CL_ERROR);
	return (1);
}

int		init_cl(t_opcl *opcl)
{
	int			ret;
	char		*src;

	if (!(get_device(opcl)))
		return (0);
	if (!(opcl->context = clCreateContext(0, 1, &opcl->dev, 0, 0, &ret)))
		terminate(opcl, CL_ERROR);
	if (!(opcl->queue = clCreateCommandQueue(opcl->context,
			opcl->dev, 0, &ret)))
		terminate(opcl, CL_ERROR);
	opcl->buf = clCreateBuffer(opcl->context,
			CL_MEM_WRITE_ONLY, WIDTH * HEIGHT * 4, 0, &ret);
	if (ret != CL_SUCCESS)
		terminate(opcl, CL_ERROR);
	if (!(src = load_src("src/calc.cl")))
		terminate(opcl, STD_ERROR);
	if (!(opcl->program =
			clCreateProgramWithSource(opcl->context,
					1, (const char**)&src, NULL, &ret)))
		terminate(opcl, CL_ERROR);
	free(src);
	get_kernel(opcl);
	return (1);
}
