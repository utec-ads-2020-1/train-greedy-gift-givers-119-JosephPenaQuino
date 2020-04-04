#include <iostream>
#include <deque>
#include <string>
#include <cmath>

#define there_is_a_new_group(n) scanf("%d", &n) != EOF

class GGFriend
{
    private:
    std::deque<GGFriend*> friends;
    std::deque<std::string> friends_name;
    int initial_worth;
    int net_worth;
    void friend_listed(std::string name)
    {
        std::deque<std::string>::iterator it; 
        for (it = friends_name.begin(); it != friends_name.end(); it++)
            if(*it == name)
            {
                friends_name.erase(it);
                break;
            }
    }
    public:
    GGFriend() : net_worth{0}, initial_worth{0}{}
    void read_gift_spending()
    {
        int n_friends;
        std::cin >> net_worth;
        initial_worth = net_worth;
        std::cin >> n_friends;
        std::string current_name;
        for (int i = 0; i < n_friends; ++i)
        {
            std::cin >> current_name;
            friends_name.push_back(current_name);
        }
    }
    void set_friend(GGFriend * new_friend, std::string name_friend)
    {
        friends.push_back(new_friend);
        friend_listed(name_friend);
    }
    std::string request_void_name_space()
    {
        if(friends_name.size() !=0)
            return friends_name[0];
        return std::string(" ");
    }
    void give_gifts()
    {
        if (friends.size() == 0)
            return;
        int individual_gift_price= floor(initial_worth/friends.size());
        net_worth = net_worth - individual_gift_price*friends.size();
        std::deque<GGFriend*>::iterator it;
        for (it=friends.begin(); it!=friends.end(); ++it)
            (*it)->receive_gift(individual_gift_price);
    }
    void receive_gift(int gift)
    {
        net_worth = net_worth + gift;
    }
    int get_net_worth()
    {
        return net_worth - initial_worth;
    }
};

class GGGroup
{
    private:
    int number_of_ggfriends;
    std::deque<std::pair<std::string, GGFriend*>> ggfriends;

    void read_list_of_friends()
    {
        bool start_reading = false;
        std::string list_of_names;
        getline(std::cin, list_of_names);
        getline(std::cin, list_of_names);
        std::string name = ""; 
        for ( std::string::iterator x=list_of_names.begin(); x!=list_of_names.end(); ++x)
        { 
            if (*x != ' ') 
            {
                name = name+*x;
                start_reading = true;
            }
            else if (start_reading && name.length() > 1)
            {
                ggfriends.push_back(std::pair<std::string, GGFriend*>(name, new GGFriend()));
                name.clear();
            }
        }  
        ggfriends.push_back(std::pair<std::string, GGFriend*>(name, new GGFriend()));
    }
    std::pair<std::string, GGFriend*> * get_ggfriend(std::string name)
    {
        std::deque<std::pair<std::string, GGFriend*>>::iterator it; 
        for (it = ggfriends.begin(); it != ggfriends.end(); it++) 
        {
            if (it->first == name)
                return &(*it);
        }
    }

    public:
    GGGroup(int _number_of_ggfriends)
    {  
        number_of_ggfriends = _number_of_ggfriends;
        read_list_of_friends();
    }
    void read_friends_givings()
    {
        std::string current_name;
        for (int i = 0; i < number_of_ggfriends; ++i)
        {
            std::cin >> current_name;
            get_ggfriend(current_name)->second->read_gift_spending();
        }
    }
    bool is_not_void()
    {
        return ggfriends.size() > 1;
    }
    void apply_connections()
    {
        std::deque<std::pair<std::string, GGFriend*>>::iterator it; 
        std::string current_name;
        for (it = ggfriends.begin(); it != ggfriends.end(); it++)
        {
            while((current_name = it->second->request_void_name_space()) != " ")
            {
                it->second->set_friend(get_ggfriend(current_name)->second, current_name);
            }
        }
    }
    void give_gifts()
    {
        std::deque<std::pair<std::string, GGFriend*>>::iterator it; 
        for (it = ggfriends.begin(); it != ggfriends.end(); it++)
            it->second->give_gifts();
    }
    void print_friends_net_worth()
    {
        std::deque<std::pair<std::string, GGFriend*>>::iterator it; 
        for (it = ggfriends.begin(); it != ggfriends.end(); it++) 
            std::cout << it->first << " " << it->second->get_net_worth() << std::endl;
    }
};

int main()
{
    int number_of_friends;
    bool first = true;
    while (there_is_a_new_group(number_of_friends))
    {
        if (!first)
            std::cout << std::endl;
        first=false;
        GGGroup my_group(number_of_friends);
        my_group.read_friends_givings();
        my_group.apply_connections();
        my_group.give_gifts();
        my_group.print_friends_net_worth();
        
    }
}