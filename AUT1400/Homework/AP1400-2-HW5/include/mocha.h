#ifndef MOCHA_H
#define MOCHA_H

#include "espresso_based.h"

class Mocha : public EspressoBased
{
    public:
        Mocha();
        Mocha(const Mocha& mocha);
        ~Mocha()override;
        void operator=(const Mocha& mocha);
        std::string get_name()override;
        double price()override;
        std::vector<std::shared_ptr<Ingredient>>& get_side_items();
        void add_side_item(Ingredient* side);
    private:
        std::vector<std::shared_ptr<Ingredient>> side_items;
};
#endif // MOCHA_H