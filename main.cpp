#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

using namespace std;

class Item
{
private:
    string name;
    float dmg;
    int price;
public:
    Item(string name, float dmg, int price) :
    name{name},
    dmg{dmg},
    price{price}
    {
        
    }
    string GetName()
    {
        return name;
    }
    float GetDmg()
    {
        return dmg;
    }
    int GetPrice()
    {
        return price;
    }
    void ShowStats()
    {
        cout << name << " [" << price << "]" << endl;
        cout << "Damage: " << dmg << endl;
    }
};

class Player
{
private:
    string name;
    int gold;
    vector<Item*> eq;
public:
    Player(string name, int gold) :
    name{name},
    gold{gold}
    {
        
    }
    string GetName()
    {
        return name;
    }
    int GetGold()
    {
        return gold;
    }
    int GetItemPrice(int index)
    {
        return eq[index]->GetPrice();
    }
    Item* GetItem(int index)
    {
        return eq[index];
    }
    void ShowEq()
    {
        cout << "Name: " << this->name << endl;
        cout << "Gold: " << this->gold << endl;
        int i = 0;
        for(Item* item : eq)
        {
            cout << i << ": " << endl;
            item->ShowStats();
            i++;
        }
    }
    void ModifyGold(int amount)
    {
        this->gold += amount;
    }
    void AddItem(Item* item)
    {
        eq.push_back(item);
    }
    void RemoveItem(int index)
    {
        eq.erase(eq.begin() + index);
    }
};

class Shop
{
private:
    Player* Merchant;
    Player* Client;
public:
    Shop()
    {
        Merchant = new Player("Merchant", 400);
        Merchant->AddItem(new Item("Sword", 10, 200));
        Merchant->AddItem(new Item("Wand", 6, 140));
        Merchant->AddItem(new Item("Axe", 12.6, 134));
        
        Client = new Player("Andrzej", 200);
        Client->AddItem(new Item("Sword", 10, 50));
    }
    ~Shop()
    {
        delete Merchant;
        delete Client;
    }
    void Buy()
    {
        cout << "Loading buy menu..." << endl;
        sleep(2);
        cout << endl;
        cout << "Shop [" << Merchant->GetGold() << "]" << endl;
        Merchant->ShowEq();
        int index = 0;
        cin >> index;
        if(Merchant->GetItemPrice(index) > Client->GetGold())
        {
            cout << "Not enough Gold!" << endl;
            return;
        }
        else
        {
            Client->AddItem(Merchant->GetItem(index));
            int itemPrice = Merchant->GetItem(index)->GetPrice();
            Client->ModifyGold(itemPrice*(-1));
            Merchant->ModifyGold(itemPrice);
            Merchant->RemoveItem(index);
        }
    }
    void Sell()
    {
        cout << "Loading sell menu..." << endl;
        sleep(2);
        cout << endl;
        cout << "Shop [" << Merchant->GetGold() << "]" << endl;
        cout << "Your Gold [" << Client->GetGold() << "]" << endl;
        cout << endl;
        cout << "your eq: " << endl;
        cout << endl;
        Client->ShowEq();
        cout << endl;
        cout << "Select an item to sell: " << endl;
        int index;
        cin >> index;
        if(Client->GetItemPrice(index) > Merchant->GetGold())
        {
            cout << "The merchant doesn't have enough gold" << endl;
            return;
        }
        Merchant->AddItem(Client->GetItem(index));
        int itemPrice = Client->GetItem(index)->GetPrice();
        Merchant->ModifyGold(itemPrice*(-1));
        Client->ModifyGold(itemPrice);
        Client->RemoveItem(index);
    }
    void Trade()
    {
        cout << "Loading trade menu..." << endl;
        sleep(2);
        cout << endl;
        cout << "your eq: " << endl;
        Client->ShowEq();
        
        cout << endl;
        
        cout << "shop eq: " << endl;
        Merchant->ShowEq();
        
        cout << endl;
        
        string option;
        while(option != "exit")
        {
            Merchant->ShowEq();
            Client->ShowEq();
            cout << "buy, sell, exit" << endl;
            cout << endl;
            cin >> option;
            if(option == "buy")
            {
                Buy();
            }
            else if(option == "sell")
            {
                Sell();
            }
        }
    }
};

int main(){
    
    Shop S;
    S.Trade();
    
    Item* item1 = new Item("Sword", 12.5, 200);
    Item* item2 = new Item("Wand", 10.5, 154);
    Item* item3 = new Item("Axe", 15.8, 123);
    
    cout << "Your items are: " << endl;
    cout << endl;
    item1->ShowStats();
    item2->ShowStats();
    item3->ShowStats();
    
    delete item1;
    delete item2;
    delete item3;
    
    Player* player1 = new Player("Andrzej", 300);
    
    player1->AddItem(new Item("Sword", 12.5, 200));
    player1->AddItem(new Item("Wand", 10.5, 154));
    player1->ShowEq();
    player1->RemoveItem(0);
    player1->ShowEq();
    
    return 0;
}
