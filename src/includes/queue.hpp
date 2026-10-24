/**
 * @file queue.hpp
 * @brief Defines the Queue template class.
 */

#pragma once

/**
 * @brief A circular queue template class with a fixed capacity.
 *
 * When the queue is full, adding a new item overwrites the oldest item.
 *
 * @tparam T The type of elements stored in the queue.
 * @tparam Capacity The maximum number of elements the queue can hold.
 */
template <typename T, int Capacity>
class Queue
{
public:
    T records[Capacity];
    int front; // Index of the oldest element
    int rear;  // Index of the newest element
    int count; // Number of elements currently stored

    /**
     * @brief Constructs an empty queue.
     */
    Queue()
    {
        front = 0;
        rear = -1;
        count = 0;
    }

    /**
     * @brief Checks if the queue is empty.
     * @returns True if empty, false otherwise.
     */
    bool is_empty() const
    {
        return count == 0;
    }

    /**
     * @brief Checks if the queue is full.
     * @returns True if full, false otherwise.
     */
    bool is_full() const
    {
        return count == Capacity;
    }

    /**
     * @brief Adds an item to the queue, overwriting the oldest item if full.
     * @param item The item to enqueue.
     */
    void enqueue(const T &item)
    {
        if (is_full())
        {
            front = (front + 1) % Capacity;
        }
        else
        {
            count++;
        }

        rear = (rear + 1) % Capacity;
        records[rear] = item;
    }
};
