#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <string>

template<typename T>
class dynamic_array
{
private:
    int size;
    int array_capacity;
    T *data;

public:
    dynamic_array()
    {
        size = 0;
        array_capacity = 10;
        data = new T[array_capacity];
    }

    ~dynamic_array()
    {
        delete[] data;
    }

    dynamic_array(const dynamic_array &other) = delete;
    dynamic_array &operator=(const dynamic_array &other) = delete;

    int length() const
    {
        return size;
    }

    int capacity() const
    {
        return array_capacity;
    }

    void add(T value)
    {
        if (size >= array_capacity)
        {
            int new_capacity = array_capacity * 2;
            T *new_data = new T[new_capacity];

            for (int i = 0; i < size; i++)
            {
                new_data[i] = data[i];
            }

            delete[] data;
            data = new_data;
            array_capacity = new_capacity;
        }

        data[size] = value;
        size++;
    }

    void remove(int index)
    {
        if (index < 0 || index >= size)
        {
            throw std::string("Index out of range");
        }

        for (int i = index; i < size - 1; i++)
        {
            data[i] = data[i + 1];
        }

        size--;
    }

    T &get(int index)
    {
        if (index < 0 || index >= size)
        {
            throw std::string("Index out of range");
        }

        return data[index];
    }

    const T &get(int index) const
    {
        if (index < 0 || index >= size)
        {
            throw std::string("Index out of range");
        }

        return data[index];
    }

    T &operator[](int index)
    {
        return get(index);
    }

    const T &operator[](int index) const
    {
        return get(index);
    }
};

#endif
