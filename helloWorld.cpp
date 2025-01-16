#include <iostream>
#include <ctime>
#include <sstream>
// Code généré par Copilot pour optimisier le temps de développement
int main() {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    std::ostringstream oss;
    oss  
              << (now->tm_year + 1900) << '-'
              << (now->tm_mon + 1) << '-'
              << now->tm_mday << ' '
              << now->tm_hour << ':'
              << now->tm_min << ':'
              << now->tm_sec << std::endl;

    std::cout << "Hello! il est présentement " << oss.str() << std::endl;
    return 0;
}