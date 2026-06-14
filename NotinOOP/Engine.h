#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Command.h"
#include "NotinoOOP.h"

class Engine {
private:
    bool isRunning;
	NotinoOOP system;

    Engine();

	// Factory method for parsing user input into commands
    std::unique_ptr<Command> parseCommand(const std::string& input);

public:
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

    static Engine& getInstance();
    NotinoOOP& getSystem();

	std::vector<std::string> splitInput(const std::string& input);
    void run();
    void stop();

    ~Engine() = default;
};