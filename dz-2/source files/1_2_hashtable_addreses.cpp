#include "header.h"

#define DEBUG 1
const size_t INITIAL_CAPACITY = 8;
const double MAX_ALPHA = 0.75;


class StringHasher {
public:
    StringHasher(size_t prime = 71)
    : prime(prime)
    {
    }
    
    size_t operator()(const std::string &str)
    {
        size_t hash = 0;
        for (const auto &c: str)
        {
            hash = hash * prime + c;
        }
        return hash;
    }
private:
    size_t prime;
};
template <typename T>
class KeyWords {
public:
    T nil;
    T del;
};
    
class StringOptions: public KeyWords<std::string> {
public:
    std::string nil = "N";
    std::string del = "D";
};

template <typename T, typename Hasher>
class HashTable
{
public:
    HashTable(T kw_nil, T kw_del, size_t initial_capacity = INITIAL_CAPACITY)
    : size(0), table(initial_capacity)
    {
        key_words.nil = kw_nil;
        key_words.del = kw_del;
        for (size_t i = 0; i < initial_capacity; ++i)
            table[i] = key_words.nil;
    }
    
    ~HashTable() = default;
    
    bool Add(const T& key);
    bool Has(const T& key);
    bool Remove(const T& key);
    void print();
    void grow();

private:
    
    std::vector<T> table;
    size_t size;
    Hasher get_hash;
    KeyWords<T> key_words;
};

template <typename T, typename Hasher>
bool HashTable<T, Hasher>::Add(const T& key)
{
    if (DEBUG)
        std::cout << "adding " << key << std::endl;

    if (size >= table.size() * MAX_ALPHA)
    {
        if (DEBUG)
            std::cout << "expansion: " << size << '/' << table.size() << " = " << (double(size) / table.size()) << " >= " << MAX_ALPHA << std::endl;
        grow();
    }
    // TODO: reduce

    size_t hash = get_hash(key);
    size_t first_del = table.size();

    if (DEBUG)
        std::cout << "first hash: " << hash << " | pos: " << hash % table.size() << std::endl;

    for (size_t i = 0; i < table.size() && table[hash % table.size()] != key_words.nil; ++i)
    {
        if (table[hash % table.size()] == key)
            return false;
        
        if (first_del != table.size() && table[hash % table.size()] == key_words.del)
            first_del = hash % table.size();

        // probe
        hash = (hash + (i + 1) * (2 * hash + 1));
        if (DEBUG)
            std::cout << "hash: " << hash << " | pos: " << hash % table.size() << std::endl;

    }

    if (first_del != table.size())
        table[first_del] = key;
    else
        table[hash % table.size()] = key;
    
    size++;
    return true;
}

template <typename T, typename Hasher>
bool HashTable<T, Hasher>::Has(const T& key)
{
    size_t hash = get_hash(key);
     
    for (size_t i = 0; i < table.size() && table[hash % table.size()] != key_words.nil; ++i) {
        
        if (table[hash % table.size()] == key)
            return true;

        hash = hash + (i + 1) * (2 * hash + 1);
    }
    return false;
}


template <typename T, typename Hasher>
bool HashTable<T, Hasher>::Remove(const T& key)
{
    size_t hash = get_hash(key);

    for (size_t i = 0; i < table.size() && table[hash % table.size()] != key_words.nil; ++i) {

        if (table[hash % table.size()] == key) {
            table[hash % table.size()] = key_words.del;
            size--;
            return true;
        }

        hash = (hash + (i + 1) * (2 * hash + 1));
    }
    return false;
}


template <typename T, typename Hasher>
void HashTable<T, Hasher>::grow()
{
    std::vector<T> table_copy;
    std::vector<T> new_table(table.size() * 2, key_words.nil);

    for (size_t i = 0; i < table.size(); i++) {
        if (table[i] == key_words.nil || table[i] == key_words.del)
            continue;
        table_copy.push_back(table[i]);
    }
    table = std::move(new_table);

    for (size_t i = 0; i < table_copy.size(); i++)
        this->Add(table_copy[i]);
}

template <typename T, typename Hasher>
void HashTable<T, Hasher>::print()
{
    for (int i = 0; i < table.size(); i++)
    {
        std::cout << "[" << i << "]: " << table[i] << std::endl;
    }
}

void run1_2(std::string input) {
    StringOptions so;
    HashTable<std::string, StringHasher> table(so.nil, so.del);
    char op;
    std::string str;
    
    while (std::cin >> op)
    {
        switch (op)
        {
            case '+':
            {
                std::cin >> str;
                std::cout << (table.Add(str) ? "OK": "FAIL") << std::endl;
                break;
            }
            case '?':
            {
                std::cin >> str;
                std::cout << (table.Has(str) ? "OK": "FAIL") << std::endl;
                break;
            }
            case '-':
            {
                std::cin >> str;
                std::cout << (table.Remove(str) ? "OK": "FAIL") << std::endl;
                break;
            }
            case 'p':
            {
                table.print();
                break;
            }
            case 'g':
            {
                table.grow();
                break;
            }
        }
    }
}
