#pragma once

#define DEBUG3 1

#include "list_graph.h"

struct WeightedMatrixGraph : IGraph {
    WeightedMatrixGraph(size_t size) : adjacencyMatrix(size, std::vector<int>(size, INT32_MAX))
    {
    }

    ~WeightedMatrixGraph() {}

    void AddEdge(int from, int to) override {
        this->AddEdge(from, to, 1);
    }

    void AddEdge(int from, int to, int cost) {
        assert(0 <= from && from < adjacencyMatrix.size());
        assert(0 <= to && to < adjacencyMatrix.size());
        adjacencyMatrix[from][to] = cost;
    }

    int VerticesCount() const override { return adjacencyMatrix.size(); }

    std::vector<int> GetNextVertices(int vertex) const override {
        assert(0 <= vertex && vertex < adjacencyMatrix[0].size());
        std::vector<int> res;

        for (size_t i = 0; i < adjacencyMatrix[vertex].size(); ++i)
            if (adjacencyMatrix[vertex][i] != INT32_MAX)
                res.push_back(i);

        return res;
    };

    std::vector<int> GetPrevVertices(int vertex) const override {
        assert(0 <= vertex && vertex < adjacencyMatrix.size());
        std::vector<int> res;

        for (size_t i = 0; i < adjacencyMatrix.size(); ++i)
            if (adjacencyMatrix[i][vertex] != INT32_MAX)
                res.push_back(i);

        return res;
    }

    int GetWeight(int from, int to) const {
        assert(0 <= from && from < adjacencyMatrix.size());
        assert(0 <= to && to < adjacencyMatrix.size());
        return adjacencyMatrix[from][to];
    }

    friend std::ostream& operator<< (std::ostream& out, const WeightedMatrixGraph& obj) {
        for (size_t i = 0; i < obj.adjacencyMatrix.size(); ++i) {
            for (size_t j = 0; j < obj.adjacencyMatrix[i].size(); ++j)
                if (obj.adjacencyMatrix[i][j] == INT32_MAX)
                    out << "- ";
                else
                    out << obj.adjacencyMatrix[i][j] << " ";
            out << std::endl;
        }
        return out;
    }

private:
    std::vector<std::vector<int>> adjacencyMatrix;
};

struct priority_comparator {
    bool operator() (const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) const {
        if (lhs.first < rhs.first)
            return true;
        if (lhs.first == rhs.first)
            if (lhs.second < rhs.second)
                return true;
        return false;
    }
};

void run_3(std::string input = "") {
    
    // input
    std::stringstream ss(input);

    int n = 0, v = 0;
    if (input.empty())
        std::cin >> v >> n;
    else
        ss >> v >> n;

    WeightedMatrixGraph graph(v);

    for (int i = 0; i < n; ++i) {
        int from = 0;
        int to = 0;
        int cost = 0;
        if (input.empty())
            std::cin >> from >> to >> cost;
        else
            ss >> from >> to >> cost;
        graph.AddEdge(from, to, cost);
    }

    int beg = 0, end = 0;
    if (input.empty())
        std::cin >> beg >> end;
    else
        ss >> beg >> end;
    // input


    std::vector<bool> visited(graph.VerticesCount(), false);
    // можно было использовать Map
    // first - приоритет, second - вершина
    std::set<std::pair<int, int>, priority_comparator> priority_q;
    bool found = false;

    priority_q.insert({ 0, beg });
    visited[beg] = true;

    while (!priority_q.empty())
    {
        if (DEBUG3) {
            std::cout << "\nqueue: ";
            for (auto i : priority_q) {
                if (i == *priority_q.begin())
                    std::cout << "[ ";
                std::cout << "(" << i.first << ", " << i.second << ") ";
                if (i == *priority_q.begin())
                    std::cout << "] ";
            }
            std::cout << "\n";
        }

        // pop most prior
        auto cur = *priority_q.begin();
        priority_q.erase(cur);

        if (cur.second == end) {
            std::cout << cur.first;
            std::cout << std::endl;
            found = true;
            break;
        }

        for (int next : graph.GetNextVertices(cur.second))
        {
            visited[next] = true;
            std::pair<int, int> to_insert = { cur.first + graph.GetWeight(cur.second, next), next };
            if (DEBUG3) std::cout << "inserting (" << to_insert.first << ", " << next << ")\n";
            // проверяем, выгоднее ли новый путь
            for (auto i : priority_q)
                if (i.second == next) {
                    if (i.first > to_insert.first)
                        // подменяем элемент, чтобы не перестроить дерево и сохранить уникальность вершины
                        priority_q.erase(i);
                    else
                        // то что уже есть повторно не вставится
                        to_insert = i;
                    break;
                }
            priority_q.insert(to_insert);
        }
    }
    if (!found)
        std::cout << "\nno path\n";
}

void test_3() {
    const int n = 8;
    std::string input[] = {
        //"6 7\n0 1\n0 2\n0 3\n3 5\n2 4\n1 4\n 5 4 0 4\n",
        //"4 3\n0 1\n0 2\n1 3\n0 3",
        //"6 8 0 1 1 2 0 2 1 3 2 4 1 4 3 5 4 5 1 5",
        //"7 8 0 1 0 2 0 3 1 6 2 4 3 4 6 5 4 5 0 5"
        "9 15 \
         0 2 2 0 3 6 0 1 9 \
         1 6 4 \
         2 4 1 2 3 3 \
         3 1 2 3 6 7 \
         4 3 1 4 7 6 \
         5 8 1 5 7 5 \
         6 5 1 6 8 5 \
         7 8 5 \
         0 8",  // from to
        "9 15 \
         0 2 2 0 3 6 0 1 9 \
         1 6 4 \
         2 4 1 2 3 3 \
         3 1 2 3 6 7 \
         4 3 1 4 7 6 \
         5 8 1 5 7 5 \
         6 5 1 6 8 5 \
         7 8 5 \
         0 7",
        "9 15 \
         0 2 2 0 3 6 0 1 9 \
         1 6 4 \
         2 4 1 2 3 3 \
         3 1 2 3 6 7 \
         4 3 1 4 7 6 \
         5 8 1 5 7 5 \
         6 5 1 6 8 5 \
         7 8 5 \
         0 5",
        "6 8 \
         0 1 1 0 2 2 0 3 3 0 4 4 \
         1 5 1 2 5 2 3 5 3 4 5 4 \
         0 5",
        "6 8 \
         0 1 1 0 2 2 0 3 3 0 4 4 \
         1 5 4 2 5 3 3 5 2 4 5 1 \
         0 5",
        "4 5 \
         0 3 3 \
         0 1 1 \
         0 2 5 \
         1 3 1 \
         2 1 1 \
         0 3",
        "10 0 \
         0 1",
        "4 4 \
         0 1 0 0 2 0 1 3 0 2 3 0 \
         0 3"
        // на отрицательнеых путях не работает
    };
    std::string answers[] = {
        "12",
        "9",
        "11",
        "2",
        "5",
        "2",
        "none",
        "0"
    };
    for (int i = 0; i < n; ++i) {
        std::cout << "=><======== [" << i << "] ========><=" << std::endl;
        run_3(input[i]);
        std::cout << "answer: " << answers[i] << '\n' << std::endl;
    }
}

void test_weighted_matrix() {
    const int n = 1;
    std::string input[] = {
        "7 12 0 1 0 5 1 2 1 3 1 5 1 6 3 2 3 4 3 6 5 4 5 6 6 4"
    };
    std::string answers[] = {
        "0 1 5 2 3 6 4\n0 1 2 3 4 6 5\n0 1 5 3 6 4 2"
    };

    for (int i = 0; i < n; ++i) {
        std::stringstream ss(input[i]);

        int n = 0, v = 0;
        ss >> v >> n;

        std::vector<std::pair<int, int>> input_(n);
        for (int i = 0; i < n; ++i)
            ss >> input_[i].first >> input_[i].second;

        // MatrixGraph
        std::cout << "\tWeighted Matrix Graph:\n";
        WeightedMatrixGraph weighted_matrix_graph(v);

        for (int i = 0; i < n; ++i)
            weighted_matrix_graph.AddEdge(input_[i].first, input_[i].second);
        std::cout << weighted_matrix_graph;

        mainBFS(weighted_matrix_graph, [](int vertex) { std::cout << vertex << " "; });
        std::cout << std::endl;
        mainDFS(weighted_matrix_graph, [](int vertex) { std::cout << vertex << " "; });
        std::cout << std::endl;

        for (int vertex : topologicalSort(weighted_matrix_graph))
            std::cout << vertex << " ";
        std::cout << std::endl;
        std::cout << "\nanswer:\n" << answers[i] << '\n' << std::endl;
    }
}