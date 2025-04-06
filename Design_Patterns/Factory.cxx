#include <iostream>
#include <string>
#include <vector>
#include <print>

#ifdef _WIN32
#include <windows.h>
#endif

enum class Burgers
{
    CHEESE
    , DELUXE
    , VEGAN
    , DELUXEVEGAN
};

class Burger
{
public:

    virtual void prepare() {}
    virtual void cook() {}
    virtual void serve() {}
    std::string getName() { return name; }

protected:

    std::string name;
    std::string bread;
    std::string sauce;
    std::vector<std::string> toppings;

};

class CheeseBurger : public Burger
{
public:
    CheeseBurger(const std::string& name = "Cheese Burger"
        , const std::string& bread = "bun"
        , const std::string& sauce = ""
        , const std::vector<std::string>& toppings_ = {})
         : Burger{}
    {
        this->name = std::string{name};
        this->bread = std::string{bread};
        this->sauce = std::string{sauce};

        toppings.push_back("beef-patty");
        toppings.push_back("cheese");

        for (const auto& topping : toppings_) {
            this->toppings.push_back(topping);
        }
    }

    void prepare() override { 
        std::println("\033[1;35m--- Preparing a {} ---\033[0m", getName());
        for (const auto& topping : toppings)
            std::println("\033[32mAdding a {}\033[0m", topping);
    }

    void cook() override { 
        std::println("\033[1;33m--- Cooking a {} ---\033[0m", getName());
        std::println("\033[1;33mMelting Cheese\033[0m");
        
    }

    void serve() override { 
        std::println("\033[1;32m--- Serving a {} ---\033[0m", getName());
    }
};

class DeluxeCheeseBurger : public Burger
{
public:
    DeluxeCheeseBurger(const std::string& name = "Deluxe Cheese Burger"
        , const std::string& bread = "bun"
        , const std::string& sauce = ""
        , const std::vector<std::string>& toppings_ = {})
        : Burger{}
    {
        this->name = std::string{name};
        this->bread = std::string{bread};
        this->sauce = std::string{sauce};

        toppings.push_back("letuce");
        toppings.push_back("beef-patty");
        toppings.push_back("tomato");
        toppings.push_back("cheese");

        for (const auto& topping : toppings_) {
            this->toppings.push_back(topping);
        }
    }

    void prepare() override { 
        std::println("\033[1;35m--- Preparing a {} ---\033[0m", getName());
        for (const auto& topping : toppings)
            std::println("\033[32mAdding a {}\033[0m", topping);
    }

    void cook() override { 
        std::println("\033[1;33m--- Cooking a {} ---\033[0m", getName());
        std::println("\033[1;33mMelting Cheese\033[0m");
        
    }

    void serve() override { 
        std::println("\033[1;32m--- Serving a {} ---\033[0m", getName());
    }
};

class VeganBurger : public Burger
{
public:
    VeganBurger(const std::string& name = "Vegan Burger"
        , const std::string& bread = "bun"
        , const std::string& sauce = "special souce\xf0\x9f\xa5\xab"
        , const std::vector<std::string>& toppings_ = {})
        : Burger{}
    {
        this->name = std::string{name};
        this->bread = std::string{bread};
        this->sauce = std::string{sauce};

        toppings.push_back("veggie-patty");

        for (const auto& topping : toppings_) {
            this->toppings.push_back(topping);
        }
    }

    void prepare() override { 
        std::println("\033[1;35m--- Preparing a {} ---\033[0m", getName());
        for (const auto& topping : toppings)
            std::println("\033[32mAdding a {}\033[0m", topping);
    }

    void cook() override { 
        std::println("\033[1;33m--- Cooking a {} ---\033[0m", getName());
        std::println("\033[1;33mChopping salad\033[0m");
        
    }

    void serve() override { 
        std::println("\033[1;32m--- Serving a {} ---\033[0m", getName());
        std::println("\033[1;32mI promise it doesn't taste like \xF0\x9F\x92\xA9\033[0m");
    }
};

class DeluxeVeganBurger : public Burger
{
public:
    DeluxeVeganBurger(const std::string& name = "Vegan Burger"
        , const std::string& bread = "bun"
        , const std::string& sauce = "special souce\xf0\x9f\xa5\xab"
        , const std::vector<std::string>& toppings_ = {})
        : Burger{}
    {
        this->name = std::string{name};
        this->bread = std::string{bread};
        this->sauce = std::string{sauce};

        toppings.push_back("letuce");
        toppings.push_back("veggie-patty");
        toppings.push_back("tomato");
        toppings.push_back("\xF0\x9F\xA7\x86");
        toppings.push_back("\xF0\x9F\x90\x9B");

        for (const auto& topping : toppings_) {
            this->toppings.push_back(topping);
        }
    }

    void prepare() override { 
        std::println("\033[1;35m--- Preparing a {} ---\033[0m", getName());
        for (const auto& topping : toppings)
            std::println("\033[32mAdding a {}\033[0m", topping);
    }

    void cook() override { 
        std::println("\033[1;33m--- Cooking a {} ---\033[0m", getName());
        std::println("\033[1;33mChopping salad\033[0m");
        
    }

    void serve() override { 
        std::println("\033[1;32m--- Serving a {} ---\033[0m", getName());
        std::println("\033[1;32mI promise it doesn't taste like \xF0\x9F\x92\xA9\033[0m");
    }
};

class BurgerStore
{
public:
    virtual Burger* createBurger(Burgers item) = 0;

    Burger* orderBurger(Burgers type) {
        Burger* burger{ createBurger(type) };
        std::println("\033[1;36m--- Making a {} ---\033[0m", burger->getName());
        burger->prepare();
        burger->cook();
        burger->serve();
        return burger;
    }
};

class CheeseBurgerStore : public BurgerStore
{
public:
    Burger* createBurger(Burgers item) override {
        switch (item)
        {
            using enum Burgers;
        case CHEESE:
            return new CheeseBurger();
        case DELUXE:
            return new DeluxeCheeseBurger();
        default:
            return nullptr;
        }
    }
};

class VeganBurgerStore : public BurgerStore
{
public:
    Burger* createBurger(Burgers item) override {
        switch (item)
        {
            using enum Burgers;
        case VEGAN:
            return new VeganBurger();
        case DELUXEVEGAN:
            return new DeluxeVeganBurger();
        default:
            return nullptr;
        }
    }
};

auto main() -> int
{
#ifdef _WIN32
    // Enable UTF-8 output on Windows
    SetConsoleOutputCP(CP_UTF8);
    // Optional, but can help with some consoles
    SetConsoleCP(CP_UTF8);
#endif

    BurgerStore* cheeseBurgerStore{ new CheeseBurgerStore() };
    
    Burger* burger{ cheeseBurgerStore->orderBurger(Burgers::CHEESE) };
    std::println("You ordered a {}", burger->getName());
    
    BurgerStore* vegeBurgerStore{ new VeganBurgerStore() };

    Burger* vege_pop{ vegeBurgerStore->orderBurger(Burgers::DELUXEVEGAN) };
    std::println("You ordered a {}", vege_pop->getName());

    delete cheeseBurgerStore;
    delete burger;

    delete vegeBurgerStore;
    delete vege_pop;

    return 0;
}