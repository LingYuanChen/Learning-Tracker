#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H

#pragma once
#include "ingredient.h"
class Cinnamon:public Ingredient
{
public:
    Cinnamon(size_t units) : Ingredient{5, units}
    {
        this->name = "Cinnamon";
    }

    virtual std::string get_name() {return this->name;}
    Ingredient* clone() const override{return new Cinnamon(units);}
};

class Chocolate:public Ingredient
{
public:
    Chocolate(size_t units) : Ingredient{5, units}
    {
        this->name = "Chocolate";
    }

    virtual std::string get_name() {return this->name;}
    Ingredient* clone() const override{return new Chocolate(units);}
};

class Sugar:public Ingredient
{
public:
    Sugar(size_t units) : Ingredient{1, units}
    {
        this->name = "Sugar";
    }

    virtual std::string get_name() {return this->name;}
    Ingredient* clone() const override{return new Sugar(units);}
};

class Cookie:public Ingredient
{
public:
    Cookie(size_t units) : Ingredient{10, units}
    {
        this->name = "Cookie";
    }

    virtual std::string get_name() {return this->name;}
    Ingredient* clone() const override{return new Cookie(units);}
};

class Espresso:public Ingredient
{
public:
    Espresso(size_t units) : Ingredient{15, units}
    {
        this->name = "Espresso";
    }

    virtual std::string get_name() {return this->name;}
    Ingredient* clone() const override{return new Espresso(units);}
};

class Milk:public Ingredient
{
public:
    Milk(size_t units) : Ingredient{10, units}
    {
        this->name = "Milk";
    }

    virtual std::string get_name() {return this->name;}
    Ingredient* clone() const override{return new Milk(units);}
};

class MilkFoam:public Ingredient
{
public:
    MilkFoam(size_t units) : Ingredient{5, units}
    {
        this->name = "MilkFoam";
    }

    virtual std::string get_name() {return this->name;}
    Ingredient* clone() const override{return new MilkFoam(units);}
};

class Water:public Ingredient
{
public:
    Water(size_t units) : Ingredient{1, units}
    {
        this->name = "Water";
    }

    virtual std::string get_name() {return this->name;}
    Ingredient* clone() const override{return new Water(units);}
};

#endif // SUB_INGREDIENTS_H