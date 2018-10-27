#pragma once
#include <sstream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <set>

class GraphReader final
{
    public:
        using Connection = std::pair<std::string, std::vector<std::string>>;
        using ConnectionList = std::vector<Connection>;

        GraphReader(const std::string& filename)
            : m_filename(filename), m_file(filename) 
        {
            m_isOpened = m_file.is_open();
            if(m_isOpened)
            {
                std::cout << "File " << m_filename << " is opened\n";
            }
        }

        ~GraphReader()
        {
            if(m_isOpened)
            {
                m_file.close();
                std::cout << "File " << m_filename << " is closed\n";
            }
        }

        ConnectionList getConnectionList()
        {
            if(!m_isOpened)
            {
                std::cerr << "Unable to open graph connections file: " << m_filename << '\n'; 
                return ConnectionList();
            }

            ConnectionList connList;

            std::string connectionsLine;
            while(std::getline(m_file, connectionsLine))
            {
                std::istringstream iss(connectionsLine);
                std::string node;

                iss >> node;
                Connection conn;
                conn.first = node;

                while(iss >> node)
                {
                    conn.second.push_back(node);
                }

                connList.push_back(conn);
            }

            m_file.clear();
            m_file.seekg(0, std::ios::beg);

            return connList;
        }

        std::set<std::string> getUniqueNodes()
        {
            if(!m_isOpened)
            {
                std::cerr << "Unable to open graph connections file: " << m_filename << '\n'; 
                return std::set<std::string>();
            }

            std::set<std::string> uniqueNodes;

            std::string node;
            while(m_file >> node)
            {
                uniqueNodes.insert(node);
            }

            m_file.clear();
            m_file.seekg(0, std::ios::beg);

            return uniqueNodes;
        }

    private:
        std::string m_filename;
        std::fstream m_file;
        bool m_isOpened {false};
};
