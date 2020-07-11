#include <iostream>
#include <vector>

class Stooge
{
public:
    virtual void slap_stick() = 0;
};

class Larry : public Stooge
{
public:
    void slap_stick()
    {
        std::cout << "Larry : poke eyes\n";
    }
};

class Moe : public Stooge
{
public:
    void slap_stick()
    {
        std::cout << "Moe : slap head\n";
    }
};

class Curly : public Stooge
{
public:
    void slap_stick()
    {
        std::cout << "Curly : poke eyes\n";
    }
};

int main()
{
    std::vector<Stooge*> roles;
    int choice;
    bool go = false;

    while (!go) {
        std::cout << "Larry(1) Moe(2) Curly(3) Go(0) ";
        std::cin >> choice;
        switch (choice) {
        case 0:
            go = true;
            break;
        case 1:
            roles.push_back(new Larry);
            break;
        case 2:
            roles.push_back(new Moe);
            break;
        case 3:
            roles.push_back(new Curly);
            break;
        default:
            break;
        }
    }

    for (int i = 0; i < roles.size(); i++)
        roles[i]->slap_stick();
    for (int i = 0; i < roles.size(); i++)
        delete roles[i];

    return 0;
}
