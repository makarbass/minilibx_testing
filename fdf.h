#ifndef FDF_H
# define FDF_H

#define MAX(a, b) ((a > b) ? a : b)  // вычисление максимального значения с помощью теранарного оператора
#define MOD(a) ((a > 0) ? a : -a) // модуль числа с помощью теранарного оператора

#include "../minilibx/mlx.h"
#include <stdio.h>
#include <stdlib.h> 

typedef struct // та самая структура, в которой хранятся все переменные
{
	int x;
	int y;
	int zoom;

	void *mlx_ptr;
	void *win_ptr;
}	fdf;

void bresenham(float x, float y, float x1, float y1, fdf *data); //прототип ф-ции для рисования линии
void square(fdf *data); // прототип функции для рисования квадрата

#endif