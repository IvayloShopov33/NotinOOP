#include <iostream>
#include <vector>

#include "Engine.h"
#include "RegisterCommand.h"
#include "LoginCommand.h"
#include "LogoutCommand.h"
#include "EndCommand.h"
#include "HelpCommand.h"
#include "CommandParseException.h"

#include "BlockUserCommand.h"
#include "CreateFragranceCommand.h"
#include "AddQuantityCommand.h"
#include "DeliverCommand.h"
#include "RemoveReviewCommand.h"

#include "AddBalanceCommand.h"
#include "AddToCartCommand.h"
#include "RemoveFromCartCommand.h"
#include "AddToWishlistCommand.h"
#include "RemoveFromWishlistCommand.h"
#include "ViewCartCommand.h"

#include "CheckoutCommand.h"
#include "ViewPurchasesCommand.h"
#include "ViewBoughtCommand.h"
#include "CancelPurchaseCommand.h"
#include "MakeReviewCommand.h"

Engine::Engine() : isRunning(false) {}

NotinoOOP& Engine::getSystem() {
    return system;
}

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
			throw CommandParseException("Login command requires username and password! Usage: login <username> <password>");
        }

        std::string username = args[1];
        std::string password = args[2];

        return std::make_unique<LoginCommand>(username, password);
    }
    else if (action == "register") {
        if (args.size() < 3) {
            throw CommandParseException("Register command requires username and password! Usage: register <username> <password>");
        }

        std::string username = args[1];
        std::string password = args[2];

        return std::make_unique<RegisterCommand>(username, password);
    }
    else if (action == "logout") {
        return std::make_unique<LogoutCommand>();
    }
    else if (action == "help") {
        return std::make_unique<HelpCommand>();
    }
    else if (action == "block-user") {
        if (args.size() < 2) {
            throw CommandParseException("Usage: block-user <username>");
        }

		std::string username = args[1];

        return std::make_unique<BlockUserCommand>(username);
    }
    else if (action == "create-fragrance") {
        // Expecting at least 5 arguments: command, name, brand, price and at least 1 note
        if (args.size() < 5) {
            throw CommandParseException("Usage: create-fragrance <name> <brand> <price> <note1> [note2...]");
        }

		std::string name = args[1];
		std::string brand = args[2];
        double price = std::stod(args[3]);

        // Collecting all remaining arguments (from index 4 onwards) into a vector of notes
        std::vector<std::string> notes(args.begin() + 4, args.end());

        return std::make_unique<CreateFragranceCommand>(name, brand, price, notes);
    }
    else if (action == "add-quantity") {
        if (args.size() < 3) {
            throw CommandParseException("Usage: add-quantity <fragrance-name> <quantity>");
        }

		std::string fragranceName = args[1];
		int quantity = std::stoi(args[2]);

        return std::make_unique<AddQuantityCommand>(fragranceName, quantity);
    }
    else if (action == "deliver") {
        if (args.size() < 2) {
            throw CommandParseException("Usage: deliver <purchase-id>");
        }

		int purchaseId = std::stoi(args[1]);

        return std::make_unique<DeliverCommand>(purchaseId);
    }
    else if (action == "remove-review") {
        if (args.size() < 3) {
            throw CommandParseException("Usage: remove-review <fragrance-id> <review-id>");
        }

		int fragranceId = std::stoi(args[1]);
		int reviewId = std::stoi(args[2]);

        return std::make_unique<RemoveReviewCommand>(fragranceId, reviewId);
    }
    else if (action == "add-to-balance") {
        if (args.size() < 2) {
            throw CommandParseException("Usage: add-to-balance <amount>");
        }

		double amount = std::stod(args[1]);

        return std::make_unique<AddBalanceCommand>(amount);
    }
    else if (action == "add-to-cart") {
        if (args.size() < 2) {
            throw CommandParseException("Usage: add-to-cart <fragrance-name>");
        }

		std::string fragranceName = args[1];

        return std::make_unique<AddToCartCommand>(fragranceName);
    }
    else if (action == "remove-from-cart")
    {
        if (args.size() < 2)
        {
            throw CommandParseException("Usage: remove-from-cart <fragrance-name>");
        }

		std::string fragranceName = args[1];

		return std::make_unique<RemoveFromCartCommand>(fragranceName);
    }
    else if (action == "add-to-wishlist")
    {
        if (args.size() < 2) {
            throw CommandParseException("Usage: add-to-wishlist <fragrance-name>");
        }

        std::string fragranceName = args[1];

        return std::make_unique<AddToWishlistCommand>(fragranceName);
    }
    else if (action == "remove-from-wishlist")
    {
        if (args.size() < 2)
        {
            throw CommandParseException("Usage: remove-from-wishlist <fragrance-name>");
        }

        std::string fragranceName = args[1];

        return std::make_unique<RemoveFromWishlistCommand>(fragranceName);
    }
    else if (action == "view-cart") {
        return std::make_unique<ViewCartCommand>();
    }
    else if (action == "checkout") {
        return std::make_unique<CheckoutCommand>();
    }
    else if (action == "view-purchases") {
        return std::make_unique<ViewPurchasesCommand>();
    }
    else if (action == "view-bought") {
        return std::make_unique<ViewBoughtCommand>();
    }
    else if (action == "cancel") {
        if (args.size() < 2) {
            throw CommandParseException("Usage: cancel <purchase-id>");
        }
        
        int purchaseId = std::stoi(args[1]);

        return std::make_unique<CancelPurchaseCommand>(purchaseId);
    }
    else if (action == "make-review") {
        if (args.size() < 4) {
            throw CommandParseException("Usage: make-review <fragrance-name> <rating> <comment>");
        }
        
        std::string fragName = args[1];
        int rating = std::stoi(args[2]);

        // Collecting all the remaining words from the console to form the entire sentence of the comment
        std::string comment = args[3];
        for (size_t i = 4; i < args.size(); ++i) {
            comment += " " + args[i];
        }

        return std::make_unique<MakeReviewCommand>(fragName, rating, comment);
    }
	// TODO: Add more commands here (e.g., register, add, delete, etc.)
    else if (action == "end") {
        return std::make_unique<EndCommand>();
    }

	throw CommandParseException("Unknown command: " + action);
}

void Engine::run() {
	system.loadData();

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
        catch (const std::invalid_argument& e) {
            std::cout << "Validation error: " << e.what() << "\n";
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

	system.saveData();
}