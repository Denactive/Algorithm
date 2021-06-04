#pragma once

#include <sstream>
#include "list_graph.h"

#define DEBUG2 1
void run_2(std::string input = "") {
    std::stringstream ss(input);

    int n = 0, v = 0;
    if (input.empty())
        std::cin >> v >> n;
    else
        ss >> v >> n;

    ListGraph graph(v);

    for (int i = 0; i < n; ++i) {
        int from = 0; 
        int to = 0;
        if (input.empty())
            std::cin >> from >> to;
        else
            ss >> from >> to;
        graph.AddEdge(from, to);
    }

    int beg = 0, end = 0;
    if (input.empty())
        std::cin >> beg >> end;
    else 
        ss >> beg >> end;

    std::vector<bool> visited(graph.VerticesCount(), false);
    std::vector<size_t> cost(graph.VerticesCount(), -1);
    std::vector<size_t> amount(graph.VerticesCount(), 0);
    std::queue<int> q;

    if (DEBUG2) std::cout << "iterating: " << beg;

    q.push(beg);
    visited[beg] = true;
    cost[beg] = 0;
    amount[beg] = 1;

    while (!q.empty())
    {
        int cur= q.front();
        q.pop();

        if (cur == end)
            break;

        for (int next: graph.GetNextVertices(cur))
        {
            if (cost[cur] + 1 == cost[next])
                amount[next] += amount[cur];

            if (cost[cur] + 1 < cost[next]) {
                cost[next] = cost[cur] + 1;
                amount[next] = amount[cur];
            }

            if (!visited[next])
            {
                visited[next] = true;      
                q.push(next);
                if (DEBUG2) std::cout << " " << next;
                if (DEBUG2 && next == end) std::cout << "(<end)";
            }
        }
    }

    if (DEBUG2) {
        std::cout << "\ncost:";
        for (size_t i = 0; i < cost.size(); ++i)
            std::cout << " " << cost[i];
        std::cout << "\n";
    }

    std::cout << amount[end];
}

void test_2() {
    const int n = 4;
    std::string input[] = {
        "6 7\n0 1\n0 2\n0 3\n3 5\n2 4\n1 4\n 5 4 0 4\n",
        "4 3\n0 1\n0 2\n1 3\n0 3",
        "6 8 0 1 1 2 0 2 1 3 2 4 1 4 3 5 4 5 1 5",
        "7 8 0 1 0 2 0 3 1 6 2 4 3 4 6 5 4 5 0 5"
    };
    std::string answers[] = {
        "2",
        "1",
        "2",
        "3"
    };
    for (int i = 0; i < n; ++i) {
        run_2(input[i]);
        std::cout << "\nanswer: " << answers[i] << '\n' << std::endl;
    }
}