// ConsoleApplication2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <string>
#include <iostream>
typedef struct
{
	uint8_t Hours;
	uint8_t Minutes;
}Lines;
typedef struct
{
	uint8_t Hours;
	uint8_t Minutes;
}STime;
Lines line[4];
STime sTime;
int get_sTimeLinesDiff(Lines* lineToCheck)
{
	//Если возвращается отрицательное число, то необходимо ждать возвращенное количество минут.
	//Если положительное, то необходимо добавить к времени на линиях
	int diff_Min = 0;
	uint8_t sHour12 = 0, lHour12 = 0;
	sHour12 = sTime.Hours % 12;
	if (sTime.Hours == 0)
	{
		sHour12 = 12;
	}

	lHour12 = lineToCheck->Hours % 12;
	if (lineToCheck->Hours == 0)
	{
		lHour12 = 12;
	}

	diff_Min = sHour12 * 60 + sTime.Minutes - (lHour12 * 60 + lineToCheck->Minutes);

	if (diff_Min < -10)
	{
		//если ждать более 10 минут
		diff_Min = 720 + diff_Min;         //крутим стрелки вперед
	}
	//корректируем время на линии, подгоняя под системное время для начала инкремента (чтобы не было переполнения часов или недобора)

	return diff_Min;
}

int main()
{
	int32_t out = 0;
	bool again = true;
	char in[6];
	std::string strMinutes = "";
	setlocale(LC_ALL, "rus");
	while (again == true)
	{
		strMinutes = "";
		std::cout << "Время на линии ЧЧ:ММ\r\n";
		std::cin >> in;

		line[0].Hours = (in[0] - 0x30) * 10 + (in[1] - 0x30);
		line[0].Minutes = (in[3] - 0x30) * 10 + (in[4] - 0x30);
		std::cout << "\r\nСистемное время ЧЧ:ММ\r\n";
		std::cin >> in;
		sTime.Hours = (in[0] - 0x30) * 10 + (in[1] - 0x30);
		sTime.Minutes = (in[3] - 0x30) * 10 + (in[4] - 0x30);
		out = get_sTimeLinesDiff(line);
		line[0].Hours = (line[0].Hours + out / 60) % 24;
		line[0].Minutes += out % 60;
		if (line[0].Minutes >= 60)
		{
			line[0].Hours = (line[0].Hours + line[0].Minutes / 60) % 24;
			line[0].Minutes = line[0].Minutes % 60;
		}
		if (line[0].Minutes - 0x30 < 10)
		{
			strMinutes.append("0");
			strMinutes.append(std::to_string(line[0].Minutes));
		}
		else
		{
			strMinutes = std::to_string(line[0].Minutes);
		}
		std::cout << "Результат после работы функции: " << std::to_string(line[0].Hours) << ":" << strMinutes << "\r\n" << "Еще?(1/0)\r\n";
		std::cin >> in;
		std::cout << "\r\n";
		again = in[0] - 0x30;
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
