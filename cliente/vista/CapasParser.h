#ifndef CAPASPARSER_H
#define CAPASPARSER_H

#include <unordered_map>
#include <istream>
#include <vector>

class CapasParser {
public:
    CapasParser(std::istream& fuente);
    std::unordered_map<std::string, std::vector<int>> getCapas();
    std::vector<std::string> getCapasOrdenadas();

private:
    std::unordered_map<std::string, std::vector<int>> capas;
    std::vector<std::string> capasOrdenadas;
};
#endif
