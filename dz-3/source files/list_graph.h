#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <cassert>
#include <deque>
#include <set>

struct IGraph {
    virtual ~IGraph() {}
    
    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

struct ListGraph: public IGraph
{
    ListGraph(size_t size)
    : adjacencyLists(size)
    {
    }
    
    ListGraph(const IGraph &graph)
    : adjacencyLists(graph.VerticesCount())
    {
        for (int i = 0; i < graph.VerticesCount(); i++)
            adjacencyLists[i] = graph.GetNextVertices(i);
    }
    
    void AddEdge(int from, int to) override
    {
        assert(0 <= from && from < adjacencyLists.size());
        assert(0 <= to && to < adjacencyLists.size());
        adjacencyLists[from].push_back(to);
    }
    
    int VerticesCount() const override
    {
        return (int)adjacencyLists.size();
    }
    
    std::vector<int> GetNextVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        return adjacencyLists[vertex];
    }
    
    std::vector<int> GetPrevVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        std::vector<int> prevVertices;
        
        for (int from = 0; from < adjacencyLists.size(); from++)
        {
            for (int to: adjacencyLists[from])
            {
                if (to == vertex)
                    prevVertices.push_back(from);
            }
        }
        return prevVertices;
    }
    
private:
    std::vector<std::vector<int>> adjacencyLists;
};


struct MatrixGraph : IGraph {
    ~MatrixGraph() {}

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) = 0;

    int VerticesCount() const = 0;

    std::vector<int> GetNextVertices(int vertex) const = 0;
    std::vector<int> GetPrevVertices(int vertex) const = 0;

private:
    std::vector<std::vector<int>> adjacencyLists;
};

struct ArcGraph : IGraph {

    ArcGraph(size_t size) : arcs(size)
    {
    }

    ~ArcGraph() {}

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) {
        assert(0 <= from && from < arcs.size());
        assert(0 <= to && to < arcs.size());
        arcs.push_back(std::pair<int, int>(from, to));
    }

    int VerticesCount() const {
        std::set<int> visited;

        for (auto arc : arcs) {
            // сохраняем только уикальные
            visited.insert(arc.first);
            visited.insert(arc.second);
        }
        return visited.size();
    }

    std::vector<int> GetNextVertices(int vertex) const {
        std::vector<int> res;
        for (auto arc : arcs)
            if (arc.first == vertex)
                res.push_back(arc.second);
        return res;
    }

    std::vector<int> GetPrevVertices(int vertex) const {
        std::vector<int> res;
        for (auto arc : arcs)
            if (arc.second == vertex)
                res.push_back(arc.first);
        return res;
    }

private:
    std::vector<std::pair<int, int>> arcs;
};


struct SetGraph : IGraph {
    SetGraph(size_t size) : adjacencySets(size)
    {
    }

    ~SetGraph() {}

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) {
        assert(0 <= from && from < adjacencySets.size());
        assert(0 <= to && to < adjacencySets.size());
        adjacencySets[from].insert(to);
    }

    int VerticesCount() const { return adjacencySets.size(); }

    std::vector<int> GetNextVertices(int vertex) const {
        assert(0 <= vertex && vertex < adjacencySets.size());
        std::vector<int> res(adjacencySets[vertex].size());
        for (auto next : adjacencySets[vertex])
            res.push_back(next);
        return res;
    }

    std::vector<int> GetPrevVertices(int vertex) const {
        assert(0 <= vertex && vertex < adjacencySets.size());
        std::vector<int> res(adjacencySets[vertex].size());

        for (auto i = 0; i < adjacencySets.size(); ++i) {
            auto set = adjacencySets[i];
            if (set.find(vertex) != set.end())
                res.push_back(i);
        }
        return res;
    }

private:
    std::vector<std::set<int>> adjacencySets;
};

void BFS(const IGraph &graph, int vertex, std::vector<bool> &visited, std::function<void(int)> &func)
{
    std::queue<int> qu;
    qu.push(vertex);
    
    visited[vertex] = true;
    
    while (!qu.empty())
    {
        int currentVertex = qu.front();
        qu.pop();
        
        func(currentVertex);
        
        for (int nextVertex: graph.GetNextVertices(currentVertex))
        {
            if (!visited[nextVertex])
            {
                visited[nextVertex] = true;
                qu.push(nextVertex);
            }
        }
    }
}

void mainBFS(const IGraph &graph, std::function<void(int)> func)
{
    std::vector<bool> visited(graph.VerticesCount(), false);
    for (int i = 0; i < graph.VerticesCount(); i++)
    {
        if (!visited[i])
            BFS(graph, i, visited, func);
    }
}

void DFS(const IGraph &graph, int vertex, std::vector<bool> &visited, std::function<void(int)> &func)
{
    visited[vertex] = true;
    func(vertex);
    
    for (int nextVertex: graph.GetNextVertices(vertex))
    {
        if (!visited[nextVertex])
            DFS(graph, nextVertex, visited, func);
    }
}

void mainDFS(const IGraph &graph, std::function<void(int)> func)
{
    std::vector<bool> visited(graph.VerticesCount(), false);
    for (int i = 0; i < graph.VerticesCount(); i++)
    {
        if (!visited[i])
            DFS(graph, i, visited, func);
    }
}

void topologicalSortInternal(const IGraph &graph, int vertex, std::vector<bool> &visited, std::deque<int> &sorted)
{
    visited[vertex] = true;
    
    for (int nextVertex: graph.GetNextVertices(vertex))
    {
        if (!visited[nextVertex])
            topologicalSortInternal(graph, nextVertex, visited, sorted);
    }
    
    sorted.push_front(vertex);
}

std::deque<int> topologicalSort(const IGraph &graph)
{
    std::deque<int> sorted;
    std::vector<bool> visited(graph.VerticesCount(), false);
    
    for (int i = 0; i < graph.VerticesCount(); i++)
    {
        if (!visited[i])
            topologicalSortInternal(graph, i, visited, sorted);
    }
    
    return sorted;
}

void run_1() {
    // списки смежности
    std::cout << "\tAdjacency Lists Graph:\n";
    ListGraph graph(7);
    graph.AddEdge(0, 1);
    graph.AddEdge(0, 5);
    graph.AddEdge(1, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(1, 5);
    graph.AddEdge(1, 6);
    graph.AddEdge(3, 2);
    graph.AddEdge(3, 4);
    graph.AddEdge(3, 6);
    graph.AddEdge(5, 4);
    graph.AddEdge(5, 6);
    graph.AddEdge(6, 4);
    
    mainBFS(graph, [](int vertex){ std::cout << vertex << " ";});
    std::cout << std::endl;
    mainDFS(graph, [](int vertex){ std::cout << vertex << " ";});
    std::cout << std::endl;
    
    for (int vertex: topologicalSort(graph))
    {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;
    
    // MatrixGraph matrixGraph(graph);
    // std::cout << matrixGraph.GetVerticesCount() << std::endl;
    // mainBFS(matrixGraph, [](int vertex){ std::cout << vertex << " ";});
    // std::cout << std::endl;
    // mainDFS(matrixGraph, [](int vertex){ std::cout << vertex << " ";});
    // std::cout << std::endl;
    
    // ArcGraph arcGraph(matrixGraph);
    // ...
    std::cout << "\tArc Graph:\n";
    ArcGraph arc_graph(7);
    arc_graph.AddEdge(0, 1);
    arc_graph.AddEdge(0, 5);
    arc_graph.AddEdge(1, 2);
    arc_graph.AddEdge(1, 3);
    arc_graph.AddEdge(1, 5);
    arc_graph.AddEdge(1, 6);
    arc_graph.AddEdge(3, 2);
    arc_graph.AddEdge(3, 4);
    arc_graph.AddEdge(3, 6);
    arc_graph.AddEdge(5, 4);
    arc_graph.AddEdge(5, 6);
    arc_graph.AddEdge(6, 4);

    mainBFS(arc_graph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    mainDFS(arc_graph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    for (int vertex : topologicalSort(arc_graph))
    {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    // SetGraph setGraph(arcGraph);
    // ...
    std::cout << "\tSet Graph:\n";
    SetGraph set_graph(7);
    set_graph.AddEdge(0, 1);
    set_graph.AddEdge(0, 5);
    set_graph.AddEdge(1, 2);
    set_graph.AddEdge(1, 3);
    set_graph.AddEdge(1, 5);
    set_graph.AddEdge(1, 6);
    set_graph.AddEdge(3, 2);
    set_graph.AddEdge(3, 4);
    set_graph.AddEdge(3, 6);
    set_graph.AddEdge(5, 4);
    set_graph.AddEdge(5, 6);
    set_graph.AddEdge(6, 4);

    mainBFS(set_graph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    mainDFS(set_graph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    for (int vertex : topologicalSort(set_graph))
    {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;
}
