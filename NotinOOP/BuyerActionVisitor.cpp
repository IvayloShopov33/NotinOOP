#pragma once
#include <functional>

#include "BuyerActionVisitor.h"
#include "UserModifierVisitor.h"

BuyerActionVisitor::BuyerActionVisitor(std::function<void(Buyer&)> actionFunc)
	: action(std::move(actionFunc)), isBuyer(false) {}

void BuyerActionVisitor::visit(Buyer& buyer)
{
	action(buyer);
	isBuyer = true;
}

void BuyerActionVisitor::visit(Admin& admin)
{
	isBuyer = false;
}

bool BuyerActionVisitor::wasExecuted() const
{
	return isBuyer;
}