#pragma once
#include <algorithm>
#include <iostream>
#include <thread>
#include <vector>

#include "utils.hpp"
#include "common_objs.hpp"

class Matrix
{
    int* data;
    int rows;
    int columns;

public:
    Matrix(int _n, int _m): rows(_n), columns(_m)
    {
        data = new int[ rows * columns ];

        std::fill(data, data + rows * columns, 0);
    }

    ~Matrix()
    {
        delete data;
    }

    void set_value(int i, int j, int value)
    {
        data[ i * columns + j ] = value;
    }

    void set_all(int value)
    {
        std::fill(data, data + rows * columns, value);
    }

    static void multiply(Matrix* x, Matrix* y, Matrix* results)
    {
        if (!(x->columns == y->rows) || !( (x->rows == results-> rows) && (y->columns == results->columns)))
        {
            std::cerr << "Error: Invalid dimensions of martix for multiplication \n";
            return;
        }

        int r{ results->rows * results->columns };

        for (size_t i{0}; i < r; ++i)
        {
            for (size_t j{0}; j < x->columns; ++j)
            {
                results->data[i] = x->data[ (i / results->columns) 
                * x->columns + j ] * y->data[ i % results->rows
                 + j * y->columns];
            }
        }
    }

    static void parallel_multiply(Matrix* x, Matrix* y, Matrix* results)
    {
        struct process_data_chunk
        {
            void operator()(Matrix* x, Matrix* y, Matrix* results
                , int start_index, int end_index
            )
            {
                for (size_t i = start_index; i < end_index; ++i)
                {
                    for (size_t j{0}; j < x->columns; ++j)
                    {
                        results->data[i] = x->data[ (i / results->columns) 
                        * x->columns + j ] * y->data[ i % results->rows
                        + j * y->columns];
                    }
                }
            }
        };

        if (!(x->columns == y->rows) || !( (x->rows == results-> rows) && (y->columns == results->columns)))
        {
            std::cerr << "Error: Invalid dimensions of martix for multiplication \n";
            return;
        }

        int64_t const length{ results->rows * results->columns };
        
        if(!length)
            return;

        uint64_t const min_per_thread{ 10'000 };
        uint64_t const max_threads{ (length + min_per_thread - 1) / min_per_thread };
        uint64_t const hardware_threads = std::thread::hardware_concurrency();
        uint64_t const num_threads{ std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads) };
        uint64_t const block_size{ length / num_threads };

        std::vector<std::thread> threads(num_threads - 1);
        int block_start{0};
        int block_end{0};

        {
            join_threads joiner(threads);
            
            for (uint64_t i{0}; i < (num_threads - 1); ++i)
            {
                block_start = i * block_size;
                block_end = block_start + block_size;
                threads[i] = std::thread(process_data_chunk(), results, x, y, block_start, block_end);
            }
        }
    }

    static void transpose(Matrix* x, Matrix* results)
    {
        if (!(x->columns == results->rows)  && (x->rows == results->columns))
        {
            std::cerr << "Error: Invalid dimensions of martix for multiplication \n";
            return;
        }

        int r{ results->rows * results->columns };

        int result_column{};
        int result_row{};

        int input_column{};
        int input_row{};

        for (size_t i{0}; i < r; ++i)
        {
            result_row = i / results->columns;
            result_column = i % results->columns;

            input_row = result_column;
            input_column = result_row;

            results->data[i] = x->data[input_row * x->columns + input_column];
        }
    }

    static void parallel_transpose(Matrix* x, Matrix* results)
    {
        struct proces_data_chunk
        {
            void operator()(Matrix* results, Matrix* x, int start_index, int end_index)
            {
                int result_column{};
                int result_row{};

                int input_column{};
                int input_row{};

                for (size_t i{start_index}; i < end_index; ++i)
                {
                    result_row = i / results->columns;
                    result_column = i % results->columns;

                    input_row = result_column;
                    input_column = result_row;

                    results->data[i] = x->data[input_row * x->columns + input_column];
                }
            }
        };

        if (!(x->columns == results->rows)  && (x->rows == results->columns))
        {
            std::cerr << "Error: Invalid dimensions of martix for multiplication \n";
            return;
        }

        int64_t length{ results->rows * results->columns };

        if(!length)
            return;

        uint64_t const min_per_thread{ 1'000 };
        uint64_t const max_threads{ (length + min_per_thread - 1) / min_per_thread };
        uint64_t const hardware_threads = std::thread::hardware_concurrency();
        uint64_t const num_threads{ std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads) };
        uint64_t const block_size{ length / num_threads };


        std::vector<std::thread> threads(num_threads - 1);
        int block_start{ 0 };
        int block_end{ 0 };
        
        {
            join_threads joiner(threads);

            for (uint64_t i{0}; i < (num_threads - 1); ++i)
            {
                block_start = i * block_size;
                block_end = block_start + block_size;
                threads[i] = std::thread(proces_data_chunk(), results, x, block_start, block_end);
            }

            proces_data_chunk()(results, x, block_end, length);
        }
    }
};