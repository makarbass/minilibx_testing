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