#pragma once
#include <iostream>
#include <map>
#include <exception>

class Service
{
    std::map <std::string, int> base;
    std::map <std::string, int> cart;
public:
    void addBase();
    void add();
    void remove();
    void input(std::string&, int&);
    bool valid(std::string&, int&);
    int check(std::map<std::string, int>&, std::string&, int&);
    void show(std::map<std::string, int>&);
};
//------------------------------
//проверка ввода пользователя
bool Service::valid(std::string& article, int& count)
{
    try
    {
        if(article.length() != 5) throw std::invalid_argument ("article");
        for (int i = 0; i < article.length(); ++i){
            if(article[i] < '0' || article[i] > '9') throw std::invalid_argument ("article");
        }
        if(count <= 0) throw std::invalid_argument ("count");
        return true;
    }
    catch(const std::invalid_argument& x)
    {
        std::cerr << "Invalid value " << x.what() << std::endl;
        return false;
    }
}
//------------------------------
void Service::show(std::map<std::string, int> & m) {
	if(m.empty()) std::cout << "empty" << std::endl;
    for(auto it : m)
        std::cout << "article: " << it.first << "\tcounty: " << it.second << std::endl;
}
//------------------------------
//проверка наличие товара в базе
int Service::check(std::map<std::string, int>&m, std::string& article, int& count){
    auto it = m.find(article);
    if( it != m.end()) return it->second;
    else {
        std::cout << "Position not found!" << std::endl;
        return -1;
    }
}
//------------------------------
void Service::input(std::string& article, int& count)
{
    bool enter = true;
    while (enter){
        std::cout << "Enter article and count: ";
        try
        {
            std::cin >> article >> count;
            if(valid(article, count)) return;
        }
        catch(...)
        {
            if(std::ios::failbit) {
                std::cin.clear();
                std::cin.ignore(512,'\n');
                std::cerr << "Some exception " << std::endl;
            }
        }
    }
}
//------------------------------
void Service::addBase(/*std::string& article, int count*/)
{
    std::string article;
    int count;
    int num;
    std::cout << "How many positions do you want to add to the database? " << std::endl;
    while(true)
    {
        try
        {
            std::cin >> num;
            if (num < 0) throw std::invalid_argument ("count position");
            for(int i= 0; i < num; ++i) {
                input(article, count);
                base[article] += count;
            }
            std::cout << "Adding a position to the store's database. Successful!" << std::endl;
            show(base);
            break;
        }
        catch (std::invalid_argument &x)
        {
            std::cerr << "Invalid number " << x.what() << std::endl;
        }
        catch(...)
        {
            if(std::ios::failbit) {
                std::cin.clear();
                std::cin.ignore(512,'\n');
                std::cerr << "Some exception " << std::endl;
            }
        }
    }
}
//--------------------------------
void Service::add()
{
    std::string article;
    int count;
    std::cout << "What product and its quantity do you want to add to the cart?" << std::endl;
    input(article, count);
    int chkArt= check(base, article,count);
    if(chkArt >= count) {
        base[article] -= count;
        cart[article] += count;
        if (cart[article] == 0) cart.erase(cart.find(article));
        std::cout << "Adding an item to the cart. Successful!" << std::endl;
        show(cart);
    } else if(chkArt == -1){
        //std::cout << "A product with such an article was not found in the database." << std::endl;
    } else {
        std::cout << "There are only " << chkArt << " product positions with this article in the database" << std::endl;
    }

}
//--------------------------------
void Service::remove()
{
    std::string article;
    int count;
    std::cout << "Which product and its quantity do you want to remove from the cart?" << std::endl;
    input(article, count);
    int chkArt= check(cart, article,count);
    if(chkArt >= count) {
        cart[article] -= count;
        base[article] += count;
        if (cart[article] == 0) cart.erase(cart.find(article));
        std::cout << "Remove position from the Cart. Successful" << std::endl;
        show(cart);
    } else if(chkArt == -1){
        //std::cout << "A product with such an article was not found in the database." << std::endl;
    } else {
        std::cout << "There are only " << chkArt << " product positions with this article in the database" << std::endl;
    }
}
