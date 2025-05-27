#include "mocha.h"
Mocha::Mocha():EspressoBased()
{   
    name = "Mocha"; 
    ingredients.push_back(std::make_shared<Milk>(2));
    ingredients.push_back(std::make_shared<MilkFoam>(1));
    ingredients.push_back(std::make_shared<Espresso>(2));
    ingredients.push_back(std::make_shared<Chocolate>(1));
};

Mocha::Mocha(const Mocha& mocha):EspressoBased(mocha)
{
    for(const auto& side : mocha.side_items)
    {
        side_items.push_back(std::shared_ptr<Ingredient>(side->clone()));
    }
};

void Mocha::operator=(const Mocha& mocha)
{
    EspressoBased::operator=(mocha);
    this->side_items = mocha.side_items;
}
Mocha::~Mocha()
{   
    std::cout << "Cappuccino destructor called" << std::endl;
    side_items.clear();
};

std::string Mocha::get_name()
{
    return name;
};

double Mocha::price()
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

void Mocha::add_side_item(Ingredient* side)
{
    side_items.push_back(std::shared_ptr<Ingredient>(side));
};

std::vector<std::shared_ptr<Ingredient>>& Mocha::get_side_items()
{
    return this->side_items;
};
