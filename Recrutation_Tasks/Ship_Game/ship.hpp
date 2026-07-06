#pragma once
#include <array>
#include <cstddef>



enum class Section
{
    Working
    , Destroyed
};

enum class ShipType
{
    Frigate
    , Cruiser
    , Battleship
    , Carrier
};

class Ship
{
    ShipType type;

protected:

    explicit Ship(ShipType t) : type(t) {}

public:

    virtual ~Ship() = default;
    
    virtual size_t size() const = 0;

    virtual Section& operator[](size_t index) = 0;
    virtual const Section& operator[](size_t index) const = 0;

    bool isSunk() const {
        for (size_t i {}; i < size(); ++i)
        {
            if ((*this)[i] == Section::Working)
                return false;
        }
        return true;
    }

    void hit(size_t index) {
        (*this)[index] = Section::Destroyed;
    }
};

class Destroyer : public Ship
{
    std::array<Section, 2> sections{};

public:
    Destroyer() : Ship(ShipType::Frigate) {}

    size_t size() const override { return 2; }
    Section& operator[](size_t index) override {
        return sections[index];
    }
    const Section& operator[](size_t index) const override {
        return sections[index];
    }

};

class Cruiser : public Ship
{
        std::array<Section, 3> sections{};

public:
    Cruiser() : Ship(ShipType::Cruiser) {}

    size_t size() const override { return 3; }
    Section& operator[](size_t index) override {
        return sections[index];
    }
    const Section& operator[](size_t index) const override {

        return sections[index];
    }
};

class Battleship : public Ship
{
    std::array<Section, 4> sections{};

public:
    Battleship() : Ship(ShipType::Battleship) {}

    size_t size() const override { return 4; }
    Section& operator[](size_t index) override {
        return sections[index];
    }
    const Section& operator[](size_t index) const override {
        return sections[index];
    }
};