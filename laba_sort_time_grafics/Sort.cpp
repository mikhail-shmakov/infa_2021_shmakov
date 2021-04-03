#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace std::chrono;

void InsertionSort(int* s_arr, int last);
void QuickSort(int* s_arr, int first, int last);

int progress_bar(int Now, int Total)
{
	if (Total <= 0.0) {
		return 0;
	}

	double percent_now = (double)Now / (double)Total;
	double progress = round(percent_now * 10000) / 10000 * 100;

	cout << "Done: " << progress << " %\r";
	cout.flush();
	return 0;
}

void write_to_file(string input, string file_name)
{
	ofstream out("calculations/" + file_name + ".txt", ios::app);
	if (out.is_open())
	{
		out << input;
	}
	out.close();
}

void quicksort(int* mas, int first, int last)
{
	int mid, count;
	int f = first, l = last;
	mid = mas[(f + l) / 2]; //вычисление опорного элемента
	do
	{
		while (mas[f] < mid) f++;
		while (mas[l] > mid) l--;
		if (f <= l) //перестановка элементов
		{
			count = mas[f];
			mas[f] = mas[l];
			mas[l] = count;
			f++;
			l--;
		}
	} while (f < l);
	if (first < l) quicksort(mas, first, l);
	if (f < last) quicksort(mas, f, last);
}

class t_array
{
public:

	friend ostream& operator << (ostream& stream, t_array& tmp);

	t_array(int n = 0, bool fill = false)
	{
		size = n;
		content = new int[size];
		if (fill)
		{
			for (int i = 0; i < size; i++)
			{
				content[i] = rand() % 100 + 1;
			}
		}
	}

	~t_array()
	{
		delete[] content;
	}

	void insertionsort() // сортировка вставками
	{
		InsertionSort(content, size);
	}

	void quicksort()
	{
		QuickSort(content, 0, size);
	}

	void resize(int n, bool fill = false)
	{
		delete[] content;
		size = n;
		content = new int[size];
		if (fill)
		{
			for (int i = 0; i < size; i++)
			{
				content[i] = rand() % 100 + 1;
			}
		}
	}
	

private:
	int* content;
	int size;
};

ostream& operator << (ostream& stream, t_array& tmp)
{
	for (int i = 0; i < tmp.size - 1; i++)
	{
		stream << tmp.content[i] << ' ';
	}
	stream << tmp.content[tmp.size - 1];
	return stream;
}


void InsertionSort(int* s_arr, int last) // сортировка вставками
{
	int temp, item;
	for (int counter = 1; counter < last; counter++)
	{
		temp = s_arr[counter];
		item = counter - 1;
		while (item >= 0 && s_arr[item] > temp)
		{
			s_arr[item + 1] = s_arr[item];
			s_arr[item] = temp;
			item--;
		}
	}
}

void QuickSort(int* s_arr, int first, int last) // быстрая сортировка
{
	if (first < last)
	{
		int left = first, right = last - 1, middle = s_arr[(left + right) / 2];
		do
		{
			while (s_arr[left] < middle) left++;
			while (s_arr[right] > middle) right--;
			if (left <= right)
			{
				int tmp = s_arr[left];
				s_arr[left] = s_arr[right];
				s_arr[right] = tmp;
				left++;
				right--;
			}
		} while (left <= right);
		QuickSort(s_arr, first, right);
		QuickSort(s_arr, left, last);
	}
}

int main()
{
	t_array a1;

	int count = 20000; /*до какого числа считаем*/

	auto start = high_resolution_clock::now();
	auto end = high_resolution_clock::now();

	ofstream ofs;
	ofs.open("calculations/InsertionSort.txt", ofstream::out | ofstream::trunc);
	ofs.close();

	ofs.open("calculations/QuickSort.txt", ofstream::out | ofstream::trunc);
	ofs.close();


	for (int i = 1; i <= count; ++i)
	{
		a1.resize(i, true);
		start = high_resolution_clock::now();
		a1.insertionsort();
		end = high_resolution_clock::now();
		write_to_file(to_string(i) + " " + to_string(duration_cast<nanoseconds>(end - start).count()) + "\n", "InsertionSort");
		progress_bar(i, count);
	}
	cout << "InsertionSort, count = " << count << '\n';

	for (int i = 1; i <= count; ++i)
	{
		a1.resize(i, true);
		start = high_resolution_clock::now();
		a1.quicksort();
		end = high_resolution_clock::now();
		write_to_file(to_string(i) + " " + to_string(duration_cast<nanoseconds>(end - start).count()) + "\n", "QuickSort");
		progress_bar(i, count);
	}
	cout << "QuickSort, count = " << count << '\n';

	system("pause");
}

