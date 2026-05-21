#include <iostream>
#include <vector>

#include "Engine.h"
#include "LoginCommand.h"
#include "CommandParseException.h"

Engine::Engine() : isRunning(false) {}

void Engine::stop() {
    isRunning = false;
}

std::vector<std::string> Engine::splitInput(const std::string& input) {
    std::vector<std::string> tokens;
    std::string currentToken = "";

    for (char ch : input) {
        if (ch != ' ') {
            currentToken += ch;
        }
        else {
            if (!currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken = "";
            }
        }
    }

    if (!currentToken.empty()) {
        tokens.push_back(currentToken);
    }

    return tokens;
}

std::unique_ptr<Command> Engine::parseCommand(const std::string& input) {
    std::vector<std::string> args = splitInput(input);

    if (args.empty()) return nullptr;

    std::string action = args[0];

    if (action == "login") {
        if (args.size() < 3) {
			throw CommandParseException("Login command requires username and password!");
        }

        std::string username = args[1];
        std::string password = args[2];

        return std::make_unique<LoginCommand>(username, password);
    }
	// TODO: Add more commands here (e.g., register, add, delete, etc.)
    else if (action == "end") {
        stop();
        // The save logic itself can be in EndCommand or NotinOOP::saveData() can be called here
        return nullptr;
    }

	throw CommandParseException("Unknown command: " + action);
}

void Engine::run() {
    isRunning = true;
    std::string inputLine;

    std::cout << "Welcome to NotinOOP! Enter command:" << std::endl;

    while (isRunning) {
        std::cout << "> ";
        std::getline(std::cin, inputLine);

        if (inputLine.empty()) continue;

        try {
            std::unique_ptr<Command> cmd = parseCommand(inputLine);

            if (cmd) {
                cmd->execute(*this);
            }
        }
        catch (const CommandParseException& e) {
            std::cout << "Syntax error: " << e.what() << "\n";
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
}