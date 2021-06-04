#include "Header.h"


#define DEBUG 0
const size_t INITIAL_CAPACITY = 8;
const double MAX_ALPHA = 0.75;

class StringHasher {
public:
    StringHasher(size_t prime = 71)
        : prime(prime)
    {
    }

    size_t operator()(const std::string& str)
    {
        size_t hash = 0;
        for (const auto& c : str)
        {
            hash = hash * prime + c;
        }
        return hash;
    }
private:
    size_t prime;
};

class StringHasher71 {
public:
    size_t operator()(const std::string &str)
    {
        size_t hash = 0;
        for (const auto &c: str)
            hash = hash * 71 + c;
        return hash;
    }
};

class StringHasher47 {
public:
    size_t operator()(const std::string& str)
    {
        size_t hash = 0;
        for (const auto& c : str)
            hash = hash * 47 + c;
        return hash;
    }
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

template <typename T, typename Hasher1, typename Hasher2>
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
    Hasher1 get_hash1;
    Hasher2 get_hash2;
    KeyWords<T> key_words;
};

template <typename T, typename Hasher1, typename Hasher2>
bool HashTable<T, Hasher1, Hasher2>::Add(const T& key)
{
    if (DEBUG)
        std::cout << "adding " << key << std::endl;

    if (size >= table.size() * MAX_ALPHA)
    {
        if (DEBUG)
            std::cout << "\texpansion: " << size << '/' << table.size() << " = " << (double(size) / table.size()) << " >= " << MAX_ALPHA << std::endl;
        grow();
    }
    // TODO: reduce | не особо нужно, конечно

    size_t hash1 = get_hash1(key);
    size_t hash2 = get_hash2(key);
    size_t hash = hash1;
    size_t first_del = table.size();

    if (DEBUG)
        std::cout << "\tfirst hash: " << hash << " | pos: " << hash % table.size() << std::endl;

    for (size_t i = 0; i < table.size() && table[hash % table.size()] != key_words.nil; ++i)
    {
        if (table[hash % table.size()] == key)
            return false;
        
        if (first_del == table.size() && table[hash % table.size()] == key_words.del)
            first_del = hash % table.size();

        // probe
        //hash = (hash + (i + 1) * (2 * hash + 1));
        hash = hash1 + (i + 1) * (2 * hash2 + 1);
        if (DEBUG)
            std::cout << "\thash: " << hash << " | pos: " << hash % table.size() << std::endl;
    }

    if (first_del != table.size())
        table[first_del] = key;
    else
        table[hash % table.size()] = key;
    
    size++;
    return true;
}

template <typename T, typename Hasher1, typename Hasher2>
bool HashTable<T, Hasher1, Hasher2>::Has(const T& key)
{
    size_t hash1 = get_hash1(key);
    size_t hash2 = get_hash2(key);
    size_t hash = hash1;
     
    for (size_t i = 0; i < table.size() && table[hash % table.size()] != key_words.nil; ++i) {
        
        if (table[hash % table.size()] == key)
            return true;

        hash = hash1 + (i + 1) * (2 * hash2 + 1);
    }
    return false;
}

template <typename T, typename Hasher1, typename Hasher2>
bool HashTable<T, Hasher1, Hasher2>::Remove(const T& key)
{
    size_t hash1 = get_hash1(key);
    size_t hash2 = get_hash2(key);
    size_t hash = hash1;

    for (size_t i = 0; i < table.size() && table[hash % table.size()] != key_words.nil; ++i) {

        if (table[hash % table.size()] == key) {
            table[hash % table.size()] = key_words.del;
            size--;
            return true;
        }

        //hash = (hash + (i + 1) * (2 * hash + 1));
        hash = hash1 + (i + 1) * (2 * hash2 + 1);
    }
    return false;
}

template <typename T, typename Hasher1, typename Hasher2>
void HashTable<T, Hasher1, Hasher2>::grow()
{
    std::vector<T> table_copy;
    std::vector<T> new_table(table.size() * 2, key_words.nil);

    for (size_t i = 0; i < table.size(); i++) {
        if (table[i] == key_words.nil || table[i] == key_words.del)
            continue;
        table_copy.push_back(table[i]);
    }
    table = std::move(new_table);
    size = 0;

    for (size_t i = 0; i < table_copy.size(); i++)
        this->Add(table_copy[i]);
}

template <typename T, typename Hasher1, typename Hasher2>
void HashTable<T, Hasher1, Hasher2>::print()
{
    for (int i = 0; i < table.size(); i++)
    {
        std::cout << "\t[" << i << "]: " << table[i] << std::endl;
    }
}

void run1_2() {
    StringOptions so;
    HashTable<std::string, StringHasher71, StringHasher47> table(so.nil, so.del);
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

void test1_2() {
    const int n = 4;
    std::string input[] = {
        "+ hello\n\
            + bye\n\
            ? bye\n\
            + bye\n\
            - bye\n\
            ? bye\n\
            ? hello\n",
        "? smtg\n\
            + smtg\n\
            ? smtg\n\
            - smtg\n\
            ? smtg\n",
        "+ a\n\
            + a\n\
            + b\n\
            ? a\n\
            ? b\n\
            - a\n\
            - a\n\
            ? a\n\
            ? b\n\
            - b\n\
            ? b\n\
            ? a\n\
            + a\n\
            ? a\n\
            - a\n\
            ? a\n",
        "\
            + abcd\n\
            + abdc\n\
            + acdb\n\
            + acbd\n\
            + adcb\n\
            + adbc\n\
            + bacd\n\
            + badc\n\
            ? abcd\n\
            ? abdc\n\
            ? acdb\n\
            ? acbd\n\
            ? adcb\n\
            ? adbc\n\
            ? bacd\n\
            ? badc\n\
            - abcd\n\
            - abdc\n\
            - acdb\n\
            - acbd\n\
            - adcb\n\
            - adbc\n\
            - bacd\n\
            - badc\n\
            ? abcd\n\
            ? abdc\n\
            ? acdb\n\
            ? acbd\n\
            ? adcb\n\
            ? adbc\n\
            ? bacd\n\
            ? badc\n\
        "
    };
    std::string answers[] = {
        "\
            OK\n\
            OK\n\
            OK\n\
            FAIL\n\
            OK\n\
            FAIL\n\
            OK\n",
        "\
            FAIL\n\
            OK\n\
            OK\n\
            OK\n\
            FAIL\n",
        "\
+ a OK\n\
+ a FAIL\n\
+ b OK\n\
? a OK\n\
? b OK\n\
- a OK\n\
- a FAIL\n\
? a FAIL\n\
? b OK\n\
- b OK\n\
? b FAIL\n\
? a FAIL\n\
+ a OK\n\
? a OK\n\
- a OK\n\
? a FAIL\n",
"OK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\n   \nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\n     \nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\n     \nFAIL\nFAIL\nFAIL\nFAIL\nFAIL\nFAIL\nFAIL\nFAIL\n"
    };

    for (int i = 0; i < n; ++i) {
        StringOptions so;
        HashTable<std::string, StringHasher71, StringHasher47> table(so.nil, so.del);
        char op;
        std::string str;

        std::stringstream ss(input[i]);

        while (ss >> op)
        {
            switch (op)
            {
            case '+':
            {
                ss >> str;
                std::cout << (table.Add(str) ? "OK" : "FAIL") << std::endl;
                break;
            }
            case '?':
            {
                ss >> str;
                std::cout << (table.Has(str) ? "OK" : "FAIL") << std::endl;
                break;
            }
            case '-':
            {
                ss >> str;
                std::cout << (table.Remove(str) ? "OK" : "FAIL") << std::endl;
                break;
            }
            }
        }
        std::cout << "\n==============\nanswer: \n" << answers[i] << "===================\n";
    }
}
