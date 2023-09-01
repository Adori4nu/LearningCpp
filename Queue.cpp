template <typename Type>
class Node
{
public:
    Node() : m_next(this), m_prev(this) {};
    Node(const Type& value) : m_next(this), m_prev(this), m_value(value) {};
    Node* m_next;
    Node* m_prev;
    Type m_value;
private:
};

#include <vector>
#include <cstddef>
#include <stdexcept>

template <typename Type>
class Node<std::vector<Type>>
{

};

template <typename Type>
class Queue
{

private:
    size_t m_size;
    //Node<Type>* m_head;
    //Node<Type>* m_tail;
    Node<Type> m_end;
public:
    Queue() : m_size(0)/*, m_head(nullptr), m_tail(nullptr)*/ {}

    void Enqueue(const Type& item)
    {
        auto* const tempNode = new Node<Type>(item);
        //if (!tempNode) throw std::runtime_error("Queue is full. Cannot enqueue");
        /*if (m_size == 0) {
            m_tail = m_head = tempNode;
        }
        else
        {
            this->m_tail->m_next = tempNode;
            this->m_tail = tempNode;
        }*/
        tempNode->m_prev = m_end.m_prev;
        tempNode->m_next = &m_end;
        m_end.m_prev->m_next = tempNode;
        m_end.m_prev = tempNode;
        m_size++;
    } 

    Type Dequeue() 
    {
        
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty. Cannot dequeue");
        }
        else
        {
            /*Node<Type>* head = this->m_head.m_value;
            this->m_head = this->m_head->m_next;
            this->m_head->m_next = nullptr;
            m_size--;*/
            auto* const head = m_end.m_next;
            auto ans = std :: move(head->m_value);
            head->m_next->m_prev = &m_end;
            m_end.m_next = head->m_next;
            delete head;
            m_size--;
            return ans;
        }
    }

    Type Peek() 
    {
        if (isEmpty())
            throw std::runtime_error("Empty. Cannot peek");
        return m_end.m_next->m_value;
    }

    inline bool isEmpty() const { return m_size == 0; };

    inline size_t getSize() const { return m_size; };
};

#include <iostream>

int main()
{
    Queue<int> intQueue;
    intQueue.Enqueue(10);
    intQueue.Enqueue(20);
    intQueue.Enqueue(30);

    std::cout << "Front element: " << intQueue.Peek() << std::endl;
    std::cout << "Deq element: " << intQueue.Dequeue() << std::endl;
    std::cout << "Front element after dequeue: " << intQueue.Peek() << std::endl;

    std::cout << "Queue size: " << intQueue.getSize() << std::endl;
}