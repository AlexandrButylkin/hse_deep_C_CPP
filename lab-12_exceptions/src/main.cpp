#include <iostream>
#include "matrix.h"

enum class Command {
    Load,
    Print,
    Add,
    Mul,
    Elem,
    Exit,

    Count
};

Command GetCommand(std::istream& is){
    std::string command;
    is >> command;
    if(command == "load") return Command::Load;
    else if(command == "print") return Command::Print;
    else if(command == "add") return Command::Add;
    else if(command == "mul") return Command::Mul;
    else if(command == "elem") return Command::Elem;
    else if(command == "exit") return Command::Exit;
    else return Command::Count;
}

int GetRegIndex(std::istream& is){
    std::string reg;
    is >> reg;
    std::string regIndex(reg.begin() + 1, reg.end());
    return std::stoi(regIndex);
}

std::string GetPath(std::istream& is){
    std::string path;
    is >> path;
    return path;
}

int GetNumber(std::istream& is){
    int number;
    is >> number;
    return number;
}

int main() {

        bool isExit = false;
        Manager manager;
        while (!isExit) {
            switch (GetCommand(std::cin)) {
                case Command::Load: {
                    int index = GetRegIndex(std::cin);
                    std::string path = GetPath(std::cin);
                    manager.Load(index, path);
                    break;
                }
                case Command::Print: {
                    int index = GetRegIndex(std::cin);
                    manager.Print(index);
                    break;
                }
                case Command::Add: {
                    int index1 = GetRegIndex(std::cin);
                    int index2 = GetRegIndex(std::cin);
                    manager.Add(index1, index2);
                    break;
                }
                case Command::Mul: {
                    int index1 = GetRegIndex(std::cin);
                    int index2 = GetRegIndex(std::cin);
                    manager.Mul(index1, index2);
                    break;
                }
                case Command::Elem: {
                    int index = GetRegIndex(std::cin);
                    int row = GetNumber(std::cin);
                    int column = GetNumber(std::cin);
                    manager.Elem(index, row, column);
                    break;
                }
                case Command::Exit: {
                    isExit = true;
                    break;
                }
                case Command::Count: {
                    return 1;
                }
            }
        }
    return 0;
}
