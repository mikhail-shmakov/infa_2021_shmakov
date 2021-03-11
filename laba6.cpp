#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;


struct subvector
{
    int *arr;
    int capacity;  //размер массива
    int size;  //сколько элементов в массиве


    subvector()
    {
        size = 0;
        capacity = 1;
        arr = (int*)malloc(sizeof(int));
    }

    ~subvector()
    {
        size = 0;
        capacity = 1;
        free(arr);
        arr = (int*)malloc(sizeof(int));
    }

    void print()
    {
        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << '\n';
        }
    }

    void push_back(int d)
    {
        if (size == capacity)
        {
            arr = (int*)realloc(arr, 2 * capacity * sizeof(int));
            capacity *= 2;
            arr[size] = d;
            size += 1;
        }
        else
        {
            arr[size] = d;
            size += 1;
        }
    }

    int pop_back()
    {
        size -= 1;
        return arr[size + 1];
    }

    void clear()
    {
        size = 0;
    }

    void resize(int new_capacity)
    {
        if (new_capacity != 0)
        {
            int right_capacity = 1;
            while (right_capacity < new_capacity)
            {
                right_capacity = right_capacity << 1;
            }
            arr = (int*)realloc(arr, right_capacity * sizeof(int));
            if (right_capacity < size)
            {
                size = new_capacity;
                capacity = right_capacity;
            }
            else
            {
                capacity = right_capacity;
            }
        }
        else
        {
            size = 0;
            capacity = 1;
            free(arr);
            arr = (int*)malloc(sizeof(int));
        }
        
    }

    void shrink_to_fit()
    {
        int right_capacity = 1;
        while (right_capacity < size)
        {
            right_capacity = right_capacity << 1;
        }
        arr = (int*)realloc(arr, right_capacity * sizeof(int));
        capacity = right_capacity;
    }

    void input_from_file(string URL)
    {
        ifstream file (URL);
        string line{};
        string number{};
        while (getline(file, line))
        {
            stringstream strStream(line);
            while (getline(strStream, number, ','))
            {
                if (size == capacity)
                {
                    arr = (int*)realloc(arr, 2 * capacity * sizeof(int));
                    capacity *= 2;
                    arr[size] = atoi(number.c_str());
                    size += 1;
                }
                else
                {
                    arr[size] = atoi(number.c_str());
                    size += 1;
                }
            }
        }
    }
};





int main()
{
    subvector v1;
    for (int i = 0; i < 6; i++)
    {
        v1.push_back(i);
    }
    v1.print();
    v1.pop_back();
    v1.print();
    v1.resize(2);
    v1.print();
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
    }
    v1.resize(100);
    v1.shrink_to_fit();
    v1.print();

    v1.input_from_file("input.txt");
    v1.print();
}
