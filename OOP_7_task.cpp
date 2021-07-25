#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
//1 задание
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
class Date
{
private:
    int day; 
    int month;
    int year;
public:

    Date(int d = 1, int m = 1, int y = 2021) : day(d), month(m), year(y)
    { }

    int getDay() { return day; }
    int getMonth() { return month; }
    int getYear() { return year; }

    void setDay(int d)
    {
        day = d;
    }
    void setMonth(int m)
    {
        month = m;
    }
    void setYear(int y)
    {
        year = y;
    }

    friend ostream& operator<< (ostream& out, const Date& date);

};
ostream& operator<< (ostream& out, const Date& date)
{
    out << "Date: " << date.day << ". " << date.month << ". " << date.year << "\n";
    return out;
}


template <typename T>
void isEmpty(unique_ptr<T>& ptr)
{
    if (ptr)
    {
        cout << "Не пуст " << endl;
    } 
    else 
    {
        cout << "Пуст " << endl;
    }
} 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
//2 задание
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

 
unique_ptr<Date>& eval(unique_ptr<Date>& ptr1, unique_ptr<Date>& ptr2)
{ 
    int ptrINT1 = stoi(to_string(ptr1->getYear())+ to_string(ptr1->getMonth())+ to_string(ptr1->getDay())); 
    int ptrINT2 = stoi(to_string(ptr2->getYear()) + to_string(ptr2->getMonth()) + to_string(ptr2->getDay()));
    
    if (ptrINT1 == ptrINT2)
    {
        cout << "Даты равны " << endl;
        return ptr1;
    }
    else
    {
        if(ptrINT1 > ptrINT2)
        { 
            return ptr1; 
        }
        else
        { 
            return ptr2; 
        }
    }
}

void change (unique_ptr<Date>& ptr1, unique_ptr<Date>& ptr2)
{
    int tempINT= ptr1->getYear();
    ptr1->setYear(ptr2->getYear());
    ptr2->setYear(tempINT);

    tempINT = ptr1->getMonth();
    ptr1->setMonth(ptr2->getMonth());
    ptr2->setMonth(tempINT);

    tempINT = ptr1->getDay();
    ptr1->setDay(ptr2->getDay());
    ptr2->setDay(tempINT);
}



//int main()
//{
//    setlocale(LC_ALL, "Russian");
//
//    unique_ptr<Date> today = make_unique<Date>(25, 07, 2021);
//    unique_ptr<Date> date;
//    today->setDay(25);
//    today->setMonth(07);
//    today->setYear(2021);
//    cout << "Доступ к полю день " << today->getDay() << " Доступ к полю месяц " << today->getMonth() << " Доступ к полю год " << today->getYear()<< endl;
//    cout << *today << endl;
//    date = move(today);
//    
//    cout << "Указатель today " << endl;
//    isEmpty(today); 
//    cout << "Указатель date " << endl;
//    isEmpty(date);
//
//    cout << endl;
//
//    unique_ptr<Date> date1 = make_unique<Date>(1, 2, 1);
//    unique_ptr<Date> date2 = make_unique<Date>(2, 1, 2);
//    cout << "Сравнение. Большая дата:  " << *eval(date1, date2)<< endl;
//    /*eval(date1, date2);*/
//    cout << "Изменение. Было:  " << endl << *date1 << endl<< *date2 << endl;
//    change(date1, date2); 
//    cout << "Изменение. Стало:  " << endl << *date1 << endl << *date2 << endl;
//
//}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
//3 задание (460 строка)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  





class Card
{
public:
    enum suit
    {
        CLUBS,
        SPADES,
        HEARTS,
        DIMONDS
    };
    enum rank
    {
        ACE = 1,
        TWO = 2,
        THREE = 3,
        FOUR = 4,
        FIVE = 5,
        SIX = 6,
        SEVEN = 7,
        EIGHT = 8,
        NINE = 9,
        TEN = 10,
        JACK = 10,
        QUEEN = 10,
        KING = 10,

    };

    Card(rank r = ACE, suit s = SPADES, bool ifu = true);
    void Flip();
    int GetValue() const;

    rank getRank()const { return m_Rank; }
    suit getSuit()const { return m_Suit; }
    bool getIFU()const { return m_IsFaceUp; }

    friend ostream& operator<<(ostream& os, const Card& aCard);

private:
    rank m_Rank;
    suit m_Suit;
    bool m_IsFaceUp;
};

Card::Card(rank r, suit s, bool ifu) : m_Rank(r), m_Suit(s), m_IsFaceUp(ifu) {}

int Card::GetValue()const
{
    int value = 0;
    if (m_IsFaceUp)
    {
        value = m_Rank;
        if (value > 10)
        {
            value = 10;
        }
    }
    return value;
}

void Card::Flip()
{
    m_IsFaceUp = !(m_IsFaceUp);
}


class Hand
{
public:
    Hand();

    virtual ~Hand();


    void Add(Card* pCard);


    void Clear();


    int GetTotal() const;

protected:
    vector<Card*> m_Cards;
};

Hand::Hand()
{
    m_Cards.reserve(7);
}

Hand::~Hand()
{
    Clear();
}

void Hand::Add(Card* pCard)
{
    m_Cards.push_back(pCard);
}


void Hand::Clear()
{

    vector<Card*>::iterator iter = m_Cards.begin();
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        delete* iter;
        *iter = 0;
    }

    m_Cards.clear();
}


int Hand::GetTotal() const
{

    if (m_Cards.empty())
    {
        return 0;
    }


    if (m_Cards[0]->GetValue() == 0)
    {
        return 0;
    }

    int total = 0;
    vector<Card*>::const_iterator iter;
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        total += (*iter)->GetValue();
    }


    bool containsAce = false;
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        if ((*iter)->GetValue() == Card::ACE)
        {
            containsAce = true;
        }
    }

    // если рука держит туз и сумма довольно маленькая, туз дает 11 очков
    if (containsAce && total <= 11)
    {
        total += 10;
    }

    return total;
}





// абстрактный класс
class GenericPlayer : public Hand
{
    friend ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer);

public:
    GenericPlayer(const string& name = "");

    virtual ~GenericPlayer();

    virtual bool IsHitting() const = 0;

    bool IsBusted() const;

    void Bust() const;

protected:
    string m_Name;
};



class Player : public GenericPlayer
{
public:
    Player(const string& name = "");

    virtual ~Player();


    virtual bool IsHitting() const;


    void Win() const;


    void Lose() const;


    void Push() const;
};


bool Player::IsHitting() const
{
    cout << m_Name << ", do you want a hit? (Y/N): ";
    char response;
    cin >> response;
    return (response == 'y' || response == 'Y');
}

void Player::Win() const
{
    cout << m_Name << " wins.\n";
}

void Player::Lose() const
{
    cout << m_Name << " loses.\n";
}

void Player::Push() const
{
    cout << m_Name << " pushes.\n";
}





class House : public GenericPlayer
{
public:
    House(const string& name = "House");

    virtual ~House();


    virtual bool IsHitting() const;


    void FlipFirstCard();
};

bool House::IsHitting() const
{
    return (GetTotal() <= 16);
}

void House::FlipFirstCard()
{
    if (!(m_Cards.empty()))
    {
        m_Cards[0]->Flip();
    }
    else
    {
        cout << "No card to flip!\n";
    }
}



ostream& operator<<(ostream& os, const Card& aCard)
{
    const string RANKS[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8", "9","10", "J", "Q", "K" };
    const string SUITS[] = { "c", "d", "h", "s" };

    if (aCard.getIFU())
    {
        os << RANKS[aCard.getRank()] << SUITS[aCard.getSuit()];
    }
    else
    {
        os << "XX";
    }

    return os;
}


ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer)
{
    os << aGenericPlayer.m_Name << ":\t";

    vector<Card*>::const_iterator pCard;
    if (!aGenericPlayer.m_Cards.empty())
    {
        for (pCard = aGenericPlayer.m_Cards.begin();
            pCard != aGenericPlayer.m_Cards.end();
            ++pCard)
        {
            os << *(*pCard) << "\t";
        }


        if (aGenericPlayer.GetTotal() != 0)
        {
            cout << "(" << aGenericPlayer.GetTotal() << ")";
        }
    }
    else
    {
        os << "<empty>";
    }

    return os;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Deck : public Hand
{
public:
    Deck();

    virtual ~Deck();

    // создает стандартную колоду из 52 карт
    void Populate();

    // тасует карты
    void Shuffle();

    // раздает одну карту в руку
    void Deal(Hand& aHand);

    // дает дополнительные карты игроку
    void AdditionalCards(GenericPlayer& aGenericPlayer);
};

Deck::Deck()
{
    m_Cards.reserve(52);
    Populate();
}

Deck::~Deck()
{}



void Deck::Populate()
{
    Clear();
    // создает стандартную колоду
    for (int s = Card::CLUBS; s <= Card::SPADES; ++s)
    {
        for (int r = Card::ACE; r <= Card::KING; ++r)
        {
            Add(new Card(static_cast<Card::rank>(r),
                static_cast<Card::suit>(s)));
        }
    }
}

void Deck::Shuffle()
{
    random_shuffle(m_Cards.begin(), m_Cards.end());
}

void Deck::Deal(Hand& aHand)
{
    if (!m_Cards.empty())
    {
        aHand.Add(m_Cards.back());
        m_Cards.pop_back();
    }
    else
    {
        cout << "Out of cards. Unable to deal.";
    }
}

void Deck::AdditionalCards(GenericPlayer& aGenericPlayer)
{
    cout << endl;
    // продолжает раздавать карты до тех пор, пока у игрока не случается
    // перебор или пока он хочет взять еще одну карту
    while (!(aGenericPlayer.IsBusted()) && aGenericPlayer.IsHitting())
    {
        Deal(aGenericPlayer);
        cout << aGenericPlayer << endl;

        if (aGenericPlayer.IsBusted())
        {
            aGenericPlayer.Bust();
        }
    }
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
//4 задание
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  


class Game
{
public:
    Game(const vector<string>& names);

    ~Game();

    // проводит игру в Blackjack
    void Play();

private:
    Deck m_Deck;
    House m_House;
    vector<Player> m_Players;
};

// Конструктор этого класса принимает ссылку на вектор строк, представляющих
// имена игроков-людей. Конструктор создает объект класса Player для каждого имени
Game::Game(const vector<string>& names)
{
    // создает вектор игроков из вектора с именами
    vector<string>::const_iterator pName;
    for (pName = names.begin(); pName != names.end(); ++pName)
    {
        m_Players.push_back(Player(*pName));
    }

    // запускает генератор случайных чисел
    srand(static_cast<unsigned int>(time(0)));
    m_Deck.Populate();
    m_Deck.Shuffle();
}

Game::~Game()
{}

void Game::Play()
{
    // раздает каждому по две стартовые карты
    vector<Player>::iterator pPlayer;
    for (int i = 0; i < 2; ++i)
    {
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            m_Deck.Deal(*pPlayer);
        }
        m_Deck.Deal(m_House);
    }

    // прячет первую карту дилера
    m_House.FlipFirstCard();

    // открывает руки всех игроков
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    {
        cout << *pPlayer << endl;
    }
    cout << m_House << endl;

    // раздает игрокам дополнительные карты
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    {
        m_Deck.AdditionalCards(*pPlayer);
    }

    // показывает первую карту дилера
    m_House.FlipFirstCard();
    cout << endl << m_House;

    // раздает дилеру дополнительные карты
    m_Deck.AdditionalCards(m_House);

    if (m_House.IsBusted())
    {
        // все, кто остался в игре, побеждают
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            if (!(pPlayer->IsBusted()))
            {
                pPlayer->Win();
            }
        }
    }
    else
    {
        // сравнивает суммы очков всех оставшихся игроков с суммой очков дилера
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end();
            ++pPlayer)
        {
            if (!(pPlayer->IsBusted()))
            {
                if (pPlayer->GetTotal() > m_House.GetTotal())
                {
                    pPlayer->Win();
                }
                else if (pPlayer->GetTotal() < m_House.GetTotal())
                {
                    pPlayer->Lose();
                }
                else
                {
                    pPlayer->Push();
                }
            }
        }

    }

    // очищает руки всех игроков
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    {
        pPlayer->Clear();
    }
    m_House.Clear();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
//5 задание
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

int main()
{
    setlocale(LC_ALL, "Russian");
   
    vector<string> names;
    int numplayers;

    while(true)
    {
        cout << "Введите количество игроков" << endl;
        cin >> numplayers;
        if (numplayers < 1)
        {
            cout << "Вы ввели неверное значение" << endl;
        }
        else
        {
            break;
        }
    }
    string vPlayerName;
    for (int i=0; i<numplayers;i++)
    {
        cout << "Введите имя " << i+1 << " игрока " << endl;
        cin >> vPlayerName;
        names.push_back(vPlayerName);

    }

    Game game = Game(names);
    game.Play();
    while (true)
    {
        cout <<  "continue the game? (Y/N): ";
        char response;
        cin >> response;
        if (response == 'y' || response == 'Y') 
        {
            game.Play();
        }
        else 
        {
            break;
        }
        
    }

    

}