#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include "AVL.h"

int main()
{
    std::string commands;
    std::cin >> commands;
    int numCommands = stoi(commands);

    BST AVL;

    for (int command = -1; command < numCommands; command++){
        // certain inputs like name, gatorID, searching are only
        // assigned if the function needs them so no weird
        // accessing occurs
        std::string newCommand;
        std::getline(std::cin, newCommand);
        std::istringstream newCin(newCommand);
        std::string type;
        newCin >> type;
        std::string name;
        std::string gatorID;
        std::string searching;

        if (type == "insert"){
            size_t firstQuotePos = newCommand.find('"');
            size_t secondQuotePos = newCommand.find('"', firstQuotePos + 1);

            if (firstQuotePos != std::string::npos && secondQuotePos != std::string::npos)
            {
                // Extract the name between the quotes
                name = newCommand.substr(firstQuotePos, secondQuotePos - firstQuotePos + 1);

                // Extract the remaining part for the ID
                newCommand = newCommand.substr(secondQuotePos + 1);

                // Trim leading spaces from the rest of the input
                size_t pos = newCommand.find_first_not_of(' ');
                if (pos != std::string::npos)
                {
                    newCommand = newCommand.substr(pos); // Remove leading spaces
                }
            }
            AVL.insert(name, newCommand);
        }
        else if (type == "remove"){
            newCin >> gatorID;
            AVL.removeID(gatorID);
        }
        else if (type == "search"){
            size_t firstSpacePos = newCommand.find(' ');
            if (firstSpacePos != std::string::npos)
            {
                // Extract the name or ID
                searching = newCommand.substr(firstSpacePos + 1);
            }
            AVL.search(searching);
        }
        else if (type == "printInorder"){
            AVL.inorder();
        }
        else if (type == "printPreorder"){
            AVL.preorder();
        }
        else if (type == "printPostorder"){
            AVL.postorder();
        }
        else if (type == "printLevelCount"){
            AVL.printLevelCount();
        }
        else if (type == "removeInorder"){
            newCin >> searching;
            AVL.removeInorder(searching);
        }
        else if (command != -1) // if no incorrect exams
            std::cout << "unsuccessful" << std::endl;
    }
}