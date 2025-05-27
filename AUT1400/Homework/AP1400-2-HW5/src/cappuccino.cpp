#include "cappuccino.h"
#include <iostream>

Cappuccino::Cappuccino():EspressoBased()
{   
    name = "Cappuccino"; 
    ingredients.push_back(std::make_shared<Milk>(2));
    ingredients.push_back(std::make_shared<MilkFoam>(1));
    ingredients.push_back(std::make_shared<Espresso>(2));
};

Cappuccino::Cappuccino(const Cappuccino& cap):EspressoBased(cap)
{
    for(const auto& side : cap.side_items)
    {
        side_items.push_back(std::shared_ptr<Ingredient>(side->clone()));
    }
};

void Cappuccino::operator=(const Cappuccino& cap)
{
    EspressoBased::operator=(cap);
    this->side_items = cap.side_items;
}
Cappuccino::~Cappuccino()
{   
    std::cout << "Cappuccino destructor called" << std::endl;
    side_items.clear();
};

std::string Cappuccino::get_name()
{
    return name;
};

double Cappuccino::price()
{   
    double price = 0;
    for (auto ingredient:ingredients)
    {   
        price += (ingredient->price());
    }
    for (auto ingredient:side_items)
    {
        price += (ingredient->price());
    }

    return price;
};

void Cappuccino::add_side_item(Ingredient* side)
{
    side_items.push_back(std::shared_ptr<Ingredient>(side));
};

std::vector<std::shared_ptr<Ingredient>>& Cappuccino::get_side_items()
{
    return this->side_items;
};
