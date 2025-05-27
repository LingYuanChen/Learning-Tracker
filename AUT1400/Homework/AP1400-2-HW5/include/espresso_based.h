#ifndef ESPRESSO_BASED_H
#define ESPRESSO_BASED_H
#include<string>
#include<vector>
#include"sub_ingredients.h"
#include<memory>

class EspressoBased
{
public:
    virtual std::string get_name() = 0;
    virtual double price() = 0;

    void brew();
    std::vector<std::shared_ptr<Ingredient>>& get_ingredients();
    virtual ~EspressoBased();

protected:
    EspressoBased();
    EspressoBased(const EspressoBased& esp);
    void operator=(const EspressoBased& esp);

    std::vector<std::shared_ptr<Ingredient>> ingredients;
    std::string name;

};
#endif // ESPRESSO_BASED_H