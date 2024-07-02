//Maayan1sher@gmail.com

#include "card.hpp"

vector<Card> Card::developmentDeck;

Card::Card(ResourceCard resource, int amount) : resourceCard(resource), isResourceCard(true) {}

Card::Card(SpecialCard specialCard) : specialCard(specialCard) ,isResourceCard(false) {}

bool Card::isResource() const
{
    return isResourceCard;
}

Card::ResourceCard Card::getResourceCard() const
{
    return resourceCard;
}

Card::SpecialCard Card::getSpecialCard() const
{
    return specialCard;
}

void Card::initializeDevelopmentDeck()
{
    developmentDeck.clear();
    // Add each card and their amount to the deck

    for (int i = 0; i < 2; ++i)
    {
        developmentDeck.push_back(Card(SpecialCard::RoadBuilding));
    }

    for (int i = 0; i < 2; ++i)
    {
        developmentDeck.push_back(Card(SpecialCard::YearOfPlenty));
    }

    for (int i = 0; i < 2; ++i)
    {
        developmentDeck.push_back(Card(SpecialCard::Monopoly));
    }

    for (int i = 0; i < 3; ++i)
    {
        developmentDeck.push_back(Card(SpecialCard::Knight));
    }

    for (int i = 0; i < 4; ++i)
    {
        developmentDeck.push_back(Card(SpecialCard::VictoryPoint));
    }

    // Shuffle the deck
    srand(unsigned(std::time(0)));
    random_shuffle(developmentDeck.begin(), developmentDeck.end());
}

Card Card::drawDevelopmentCard()
{
    if (developmentDeck.empty())
    {
        throw ::std::runtime_error("no more development card in the deck.");
    }

    Card drawnCard = developmentDeck.back();
    developmentDeck.pop_back(); // remove the card from the deck
    return drawnCard;
}