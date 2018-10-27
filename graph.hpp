#pragma once
#include <vector>
#include <map>
#include <string>
#include <utility>
#include <queue>
#include <memory>

#include "graphreader.hpp"

struct Vertex
{
    enum class Color { White, Grey, Black };

    std::vector<std::pair<int, Vertex*>> m_adj;
    std::string m_name;
    Color m_color = Color::White;

    Vertex() 
    { }

    virtual ~Vertex() 
    {
        for(auto it : m_adj)
        {
            delete it.second;
        }
    }

    Vertex(const std::string& name)
        : m_name(name) {}
};

class Graph 
{
    public:
        Graph() = default;

        Graph(GraphReader& reader)
        {
            auto uniqueNodes = reader.getUniqueNodes();
            for(auto node: uniqueNodes)
            {
                addVertex(node);
            }

            auto connList = reader.getConnectionList();
            for(std::size_t i = 0; i < connList.size(); i++)
            {   
                for(std::size_t j = 0; j < connList[i].second.size(); j++)
                {
                    addEdge(connList[i].first, connList[i].second[j], -1);
                }
            }
        }

        virtual ~Graph() { }

        void addEdge(const std::string& from, const std::string& to, int cost) 
        {
            auto itFrom = m_graph.find(from);
            if(itFrom == m_graph.end())
            {
                std::cout << "No such vertex name = " << from << " in graph\nExiting...\n";
                return;
            }

            auto itTo = m_graph.find(to);
            if(itTo == m_graph.end())
            {
                std::cout << "No such vertex name = " << to << " in graph\nExiting...\n";
                return;
            }

            auto edge = std::make_pair(cost, itTo->second);
            itFrom->second->m_adj.push_back(edge);
        }

        void addVertex(const std::string& name)
        {
            // Check, if vertex with that name already exists
            decltype(m_graph)::iterator itToName= m_graph.find(name);
            if(itToName != m_graph.end())
            {
                std::cout << "Vertex with name = " << name << " already exists\n";
                return;
            }

            // Add vertex to @m_graph 
            Vertex *pVertex = new Vertex(name);
            m_graph[name] = pVertex;    
        }

        void bfs(const std::string& start)
        {
            using Color = Vertex::Color;

            auto it = m_graph.find(start);
            if(it == m_graph.end())
            {
                std::cout << "No such vertex in graph\n";
                return;
            }

            // Make all vertexes colored to the White
            for(auto it : m_graph)
            {
                it.second->m_color = Color::White;
            }

            it->second->m_color = Color::Grey;
            std::queue<Vertex*> que;
            que.push(it->second);
            while(!que.empty())
            {
                auto& pVertex = que.front();
                que.pop();
                for(auto pAdjVertex : pVertex->m_adj)
                {
                    if(pAdjVertex.second->m_color == Color::White)
                    {
                        visit(pAdjVertex.second);
                        pAdjVertex.second->m_color = Color::Grey;
                        que.push(pAdjVertex.second);
                    }
                }
                pVertex->m_color = Color::Black;
            }

        }

        void dfs(const std::string& start)
        {

        }

        void visit(Vertex* pVertex) const 
        {   
            std::cout << "Visited vertex name = " << pVertex->m_name << '\n';
        }

        void printGraph() const
        {
            for(auto vertex: m_graph)
            {
                std::cout << vertex.first << ": ";
                for(auto adjVertex: vertex.second->m_adj)
                {
                    std::cout << adjVertex.second->m_name << ' ';
                }
                std::cout << '\n';
            }
        }
    private:
        std::map<std::string, Vertex*> m_graph{};
};
