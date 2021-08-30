#include "fdf.h"

void bresenham(float x, float y, float x1, float y1, fdf *data) // рисование линии ( передаём координаты начала и конца, и структуру)
{
	float x_step; 
	float y_step;
	int max;

	//x *= data->zoom; // умножаем координаты на zoom
	//y *= data->zoom; // умножаем координаты на zoom
	//x1 *= data->zoom; // умножаем координаты на zoom
	//x1 *= data->zoom; // умножаем координаты на zoom

	x_step = x1 - x; // считаем разницу
	y_step = y1 - y; // считаем разницу
	max = MAX(MOD(x_step), MOD(y_step)); // выбираем какая разница больше по модулю
	x_step /= max; // делим разницу на ту которая больше
	y_step /= max; // делим разницу на ту которая больше
	while ((int)(x - x1) ||  (int)(y - y1)) // пока разница не будет 0 (округленно к 0)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0x00ffffff); // рисуем пиксель
		x += x_step; // смещаемся по Х
		y += y_step; // смещаемся по Y
	}
}

void horizontal_line (int x, int x1, int y, fdf *data)
{
	while(x < x1)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0x00ffffff);	
		x++;
	}
}

void vertical_line (int x, int y, int y1, fdf *data)
{
	while(y < y1)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0x00ffffff);
		y++;
	}
}

void bresenham2(int x, int y, int x1, int y1, fdf *data)
{
	int d_x;
	int d_y;
	int er;
	int d_er;
	int yo;
	int diry;

	d_x = MOD(x1 - x);
	d_y = MOD(y1 - y);
	er = 0;
	d_er = d_y + 1;
	yo = y;
	diry = y1 - y;
	if (diry > 0)
		diry = 1;
	if (diry < 0)
		diry = -1;
	while (x < x1)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0x00ffffff);
		er = er + d_er;
		if (er >= (d_x + 1))
		{
			y = y + d_y;
			er = er - (d_x + 1);
		}
		x++;
	}
}

void square(fdf *data, int color) // для рисования квадрата передаем структуру
{
	int x;
	int y;

	x = 0;
	while (x < data->zoom) // пока Х меньше коэфицента зума
	{
		y = 0; // обнуляем y (возвращаемся в начало строки)
		while(y < data->zoom) // пока Y меньше коэфицента зума
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + data->x, y + data->y, color); // рисуем точку
			y++; // смещаемся по строке
		}
		x++; // переходим на следующую строку
	}
}