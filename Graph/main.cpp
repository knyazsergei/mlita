﻿// Graph.cpp: определяет точку входа для консольного приложения.
//18.1.Максимальный груз 2 (8)
//Решить задачу 12.3 при ограничениях 2 ≤ N ≤ 104; 2 ≤ M ≤ 105; 0 ≤ Cij ≤ 105.
//Имеются города с номерами от 1 до N и дороги между некоторыми из них.По
//дороге можно ехать в любом направлении.Известно, какой максимальный груз можно
//провезти по каждой из дорог.Нужно узнать, какие максимальные грузы можно
//доставить из города 1 в остальные города.
//Ввод из файла INPUT.TXT.Первая строка содержит количество городов N и дорог
//M через пробел.В каждой из следующих M строк находится по 3 числа.Первые два из
//них - i и j - задают дорогу, а третье Cij – ее грузоподъемность.
//Вывод в файл OUTPUT.TXT.В i - й строке выводится значение максимального
//груза, который может быть доставлен их города 1 до i + 1 - го города.Таким образом,
//файл OUTPUT.TXT состоит из N - 1 строки.Если в какой - либо город пути нет, в
//соответствующей строке вывести - 1.
//Пример
//Ввод
//5 6
//1 2 6
//1 5 7
//2 4 3
//5 4 1
//2 3 6
//4 3 1
//Вывод
//6
//6
//3
//7
#include "stdafx.h"
#include "Graph.h"
#include <string>
#include <sstream>
#include <graphviz/gvc.h>

int main()
{
	
	std::shared_ptr<CVisualization> visualization = std::make_shared<CVisualization>();
	CGraph graph(visualization);
	while (visualization->IsOpen())
	{
		visualization->Update();
	}
    return 0;
}

