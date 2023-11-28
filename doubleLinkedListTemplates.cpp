#include <iostream>
#include <sstream>

template <typename T>
struct Node
{
    T data;
    Node* next;
    Node* previous;

    /**
     * @brief Конструктор класса Node.
     * @param data Значение, которое содержит элемент списка.
     * @param next Указатель на следующий элемент списка.
     * @param previous Указатель на предыдующий элемент списка.
    */
    Node(const T data, Node* next = nullptr, Node* previous = nullptr);

    /**
     * @brief Оператор сравнения двух объектов класса Node.
     * @param node Объект класса Node.
     * @return true/false в зависимости от объектов.
    */
    bool operator == (const Node& node);

    /**
     * @brief Оператор сравнения двух объектов класса Node.
     * @param node Объект класса Node.
     * @return true/false в зависимости от объектов.
    */
    bool operator != (const Node& node);
};  

template <typename T>
Node<T>::Node(const T data, Node* next, Node* previous):data(data), next(next), previous(previous){}

template <typename T>
bool Node<T>::operator==(const Node &node)
{
    bool value = (data == node.data) * (next == node.next) * (previous == node.previous);
    return value;
}

template <typename T>
bool Node<T>::operator!= (const Node& node)
{
    return !(*this == node);
}

template <typename T>
class List
{
    private:
        Node<T>* head;
        Node<T>* tail;

    public:
        /**
        * @brief Конструктор класса List.
        * @param head Указатель на первый элемент списка.
        * @param tail Указатель на последний элемент списка.
        */
        List(Node<T>* head = nullptr, Node<T>* tail = nullptr);

        /**
         * @brief Вставляет новый узел с заданными данными в конец списка
         * @param data Данные для вставки
         */
        void PushBack(const T data);

        /**
         * @brief Проверяет, пуст ли список
         * @return True, если список пуст, иначе false
         */
        bool IsEmpty();

        /**
         * @brief Деструктор класса List.
        */
        ~List();

        /**
         * @brief Очищает список, удаляя все его элементы.
         */
        void clear();

        /**
         * @brief Вставляет новый узел с заданными данными в начало списка
         * @param data Данные для вставки
         */
        void PushAhead(const T data);

        /**
         * @brief Удаляет узел с конца списка
         */
        void DeleteBack();

        /**
         * @brief Удаляет узел с начала списка
         */
        void DeleteAhead();

        /**
         * @brief Перегружает оператор == для сравнения двух списков
         * @param list Список для сравнения
         * @return True, если списки равны, иначе false
         */
        bool operator==(List<T> &list);

        /**
         * @brief Перегружает оператор != для сравнения двух списков
         * @param list Список для сравнения
         * @return True, если списки не равны, иначе false
         */
        bool operator!=(List<T> list);

        /**
         * @brief Возвращает строковое представление списка.
         * @return Строка, содержащая все элементы списка.
         */
        std::string toString();

        /**
         * @brief Конструктор копирования класса List.
         * @param other Объект для копирования.
         */
        List(const List<T> &other);

        /**
         * @brief Оператор присваивания копированием для класса List.
         * @param other Объект для копирования.
         * @return Ссылка на текущий объект.
         */
        List<T> &operator=(const List<T> &other);

        /**
         * @brief Конструктор перемещения класса List.
         * @param other Объект для перемещения.
         */
        List(List<T> &&other) noexcept;

        /**
         * @brief Оператор присваивания перемещением для класса List.
         * @param other Объект для перемещения.
         * @return Ссылка на текущий объект.
         */    
        List<T> &operator=(List<T> &&other) noexcept;

        /**
         * @brief Перегружает оператор << для вывода списка
         * @param os Поток вывода
         * @param list Список для вывода
         * @return Поток вывода
         */
        template <typename U> 
        friend std::ostream& operator<<(std::ostream& os, const List<U>& list);
};

template <typename T>
List<T>::List(Node<T>* head, Node<T>* tail) : head(head), tail(tail) {}

template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& list)
{
    Node<T>* current = list.head;
    while (current != nullptr)
    {
        os << current->data << " ";
        current = current->previous;
    }
    return os;
}

template <typename T>
bool List<T>::IsEmpty()
{
    return (this->tail == nullptr);
}

template <typename T>
void List<T>::PushBack(const T data)
{
    Node<T>* node = new Node<T>(data);

    if (this->IsEmpty())
    {
        this->tail = node;
        this->head = node;
        this->tail->next = this->head;
        this->head->previous = this->tail;
    }
    else if (this->tail == this->head)
    {
        this->tail = node;
        this->tail->next = this->head;
        this->head->previous = this->tail;
    }
    else
    {
        node->data = this->tail->data;
        Node<T>* temp = this->tail->next;
        this->tail->next->previous = node;
        node->next = temp;
        node->previous = this->tail;
        this->tail->next = node;
        this->tail->data = data;
    }
}

template <typename T>
List<T>::~List()
{
    clear();
}

template <typename T>
void List<T>::clear()
{
    while (tail != head)
    {
        DeleteAhead();
    }

    if (tail == head)
    {
        delete head;
    }
}

template <typename T>
void List<T>::PushAhead(const T data)
{
    Node<T> *node = new Node<T>(data);

    if (IsEmpty())
    {
        tail = node;
        head = node;
    }
    else if (tail == head)
    {
        head = node;
        head->previous = tail;
        tail->next = head;
    }
    else
    {
        node->data = head->data;
        Node<T> *temp = head->previous;
        head->previous->next = node;
        node->previous = temp;
        node->next = head;
        head->previous = node;
        head->data = data;
    }
}

template <typename T>
void List<T>::DeleteBack()
{
    Node<T> *next = tail->next;

    if (next != nullptr)
    {
        delete next->previous;
        next->previous = nullptr;
    }
    tail = next;
}

template <typename T>
void List<T>::DeleteAhead()
{
    Node<T> *previous = head->previous;

    if (previous != nullptr)
    {
        delete previous->next;
        previous->next = nullptr;
    }
    head = previous;
}

template <typename T>
bool List<T>::operator==(List<T> &list)
{
    return (toString() == list.toString());
}

template <typename T>
std::string List<T>::toString()
{
    std::stringstream buffer;
    buffer << *this;
    return buffer.str();
}

template <typename T>
bool List<T>::operator!=(List<T> list)
{
    return !(*this == list);
}

template <typename T>
List<T>::List(const List<T> &other) : head(nullptr), tail(nullptr)
{
    Node<T> *temp = other.head;
    while (temp != nullptr)
    {
        this->PushBack(temp->data);
        temp = temp->previous;
    }
}

template <typename T>
List<T> &List<T>::operator=(const List<T> &other)
{
    if (this != &other)
    {
        clear();
        Node<T> *temp = other.head;
        while (temp != nullptr)
        {
            this->PushBack(temp->data);
            temp = temp->previous;
        }
    }
    return *this;
}

template <typename T>
List<T>::List(List<T> &&other) noexcept : head(other.head), tail(other.tail)
{
    other.head = nullptr;
    other.tail = nullptr;
}

template <typename T>
List<T> &List<T>::operator=(List<T> &&other) noexcept
{
    if (this != &other)
    {
        clear();
        head = other.head;
        tail = other.tail;
        other.head = nullptr;
        other.tail = nullptr;
    }
    return *this;
}