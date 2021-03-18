#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <list>

using namespace std;
using namespace std::chrono;

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
    ofstream out("calculations/" +  file_name + ".txt", ios::app);
    if (out.is_open())
    {
        out << input;
    }
    out.close();
}


struct subvector
{
    int* arr;
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
            cout << arr[i] << ' ';
        }
    }

    void push_back(int d)
    {
        if (size == capacity)
        {
            arr = (int*)realloc(arr, 2 * capacity * sizeof(int));
            capacity *= 2;
            arr[size] = d;
            size++;
        }
        else
        {
            arr[size] = d;
            size++;
        }
    }

    int pop_back()
    {
        size--;
        return arr[size + 1];
    }

    void clear()
    {
        size = 0;
    }

    void push_front(int a)
    {
        if (size == capacity)
        {
            for (int i = size; i > 0; i--)
            {
                arr[i] = arr[i - 1];
            }
            capacity *= 2;
            arr[0] = a;
            size++;
        }
        else
        {
            for (int i = size; i > 0; i--)
            {
                arr[i] = arr[i - 1];
            }
            arr[0] = a;
            size++;
        }
    }
};

int main()
{
    subvector vec;
    list<int> lst;
    int count = 1000000;

    auto start = high_resolution_clock::now();
    auto end = high_resolution_clock::now();

    ofstream ofs;
    ofs.open("logs/vec.push_back.txt", ofstream::out | ofstream::trunc);
    ofs.close();

    ofs.open("logs/lst.push_back.txt", ofstream::out | ofstream::trunc);
    ofs.close();

    ofs.open("logs/vec.pop_back.txt", ofstream::out | ofstream::trunc);
    ofs.close();

    ofs.open("logs/lst.pop_back.txt", ofstream::out | ofstream::trunc);
    ofs.close();

    ofs.open("logs/vec.push_front.txt", ofstream::out | ofstream::trunc);
    ofs.close();

    ofs.open("logs/lst.push_front.txt", ofstream::out | ofstream::trunc);
    ofs.close();

    for (int i = 0; i <= count; ++i)
    {
        start = high_resolution_clock::now();
        vec.push_back(i);
        end = high_resolution_clock::now();
        write_to_file(to_string(i) + " " + to_string(duration_cast<nanoseconds>(end - start).count()) + "\n", "vec.push_back");
        progress_bar(i, count);
    }
    cout << "vec.push_back done, count = " << count << '\n';

    for (int i = 0; i <= count; ++i)
    {
        start = high_resolution_clock::now();
        lst.push_back(i);
        end = high_resolution_clock::now();
        write_to_file(to_string(i) + " " + to_string(duration_cast<nanoseconds>(end - start).count()) + "\n", "lst.push_back");
        progress_bar(i, count);
    }
    cout << "lst.push_back done, count = " << count << '\n';

    for (int i = count; i >= 0; --i)
    {
        start = high_resolution_clock::now();
        vec.pop_back();
        end = high_resolution_clock::now();
        write_to_file(to_string(i) + " " + to_string(duration_cast<nanoseconds>(end - start).count()) + "\n", "vec.pop_back");
        progress_bar(i, count);
    }
    cout << "vec.pop_back done, count = " << count << '\n';

    for (int i = count; i >= 0; --i)
    {
        start = high_resolution_clock::now();
        lst.pop_back();
        end = high_resolution_clock::now();
        write_to_file(to_string(i) + " " + to_string(duration_cast<nanoseconds>(end - start).count()) + "\n", "lst.pop_back");
        progress_bar(i, count);
    }
    cout << "lst.pop_back done, count = " << count << '\n';

    for (int i = 0; i <= count; ++i)
    {
        start = high_resolution_clock::now();
        vec.push_front(i);
        end = high_resolution_clock::now();
        write_to_file(to_string(i) + " " + to_string(duration_cast<nanoseconds>(end - start).count()) + "\n", "vec.push_front");
        progress_bar(i, count);
    }
    cout << "vec.push_front done, count = " << count << '\n';

    for (int i = 0; i <= count; ++i)
    {
        start = high_resolution_clock::now();
        lst.push_front(i);
        end = high_resolution_clock::now();
        write_to_file(to_string(i) + " " + to_string(duration_cast<nanoseconds>(end - start).count()) + "\n", "lst.push_front");
        progress_bar(i, count);
    }
    cout << "lst.push_front done, count = " << count << '\n';

    cout << "Done";
}


