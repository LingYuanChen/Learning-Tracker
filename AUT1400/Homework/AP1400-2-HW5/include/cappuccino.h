#ifndef CAPPUCCINO
#define CAPPUCCINO
#include"espresso_based.h"
class Cappuccino:public EspressoBased
{
public:
    Cappuccino();
    Cappuccino(const Cappuccino& cap);
	~Cappuccino() override;
    void operator=(const Cappuccino& cap);

    virtual std::string get_name();
    virtual double price();

    void add_side_item(Ingredient* side);
    std::vector<std::shared_ptr<Ingredient>>& get_side_items();

private:
    std::vector<std::shared_ptr<Ingredient>> side_items;

};
#endif // CAPPUCCINO