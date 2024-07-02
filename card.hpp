//Maayan1sher@gmail.com

#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <stdexcept>
#include <random>
#include <algorithm>



using namespace std;


class Card
{
public:
    enum class ResourceCard
    {
        Wheat,
        Sheep,
        Wood,
        Brick,
        Ore
    };
    enum class SpecialCard
    {
        Knight,
        Monopoly,
        RoadBuilding,
        YearOfPlenty,
        VictoryPoint
    };

private:
    ResourceCard resourceCard;
    SpecialCard specialCard;
    bool isResourceCard;
    static vector<Card> developmentDeck;

public:
    Card(ResourceCard resource, int amount = 0);
    Card(SpecialCard specialCard);

    bool isResource() const;
    ResourceCard getResourceCard() const;
    SpecialCard getSpecialCard() const;

    static void initializeDevelopmentDeck();
    static Card drawDevelopmentCard();
};

#endif