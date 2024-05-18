#include "../include/server.hpp"

bool isDupChannel(std::vector<Channels> haystack, std::string needle)
{
    for (size_t i = 0; i < haystack.size(); i++)
        if (haystack[i].getChannelName() == needle)
            return false;
    return true;
}

void Server::JoinConstruction(Client *client)
{
    std::vector<std::string> cmd = client->get_commande();
    std::string msg = ERROR_NEEDMOREPARAMS(client->get_nickname(), client->get_hostname());
    if (cmd.size() < 2 || cmd[1].empty() || !cmd[1][1])
    {
        std::cout<< msg << std::endl;
        if (send(client->get_fd(),msg.c_str(), msg.length(), 0) == -1)
            throw std::runtime_error("Failed Send JOIN message to the client");
        return ;
    }
    else if(!isDupChannel(channels, cmd[1]))
        return ;
    else
    {
        Channels channel;
        for(size_t i; i < cmd.size(); i++)
            if(cmd.size() > 2 && cmd[i][1])
            {
                channels.push_back(cmd[i]);

            }
            
        channel.join(client);
        channels.push_back(cmd[1]);
    }
    // for(size_t i = 0; i < channels.size(); i++)
    //     std::cout << "channel: " << channels[i].getChannelName() << std::endl;
    // for(size_t i = 0; i < clients.size(); i++)
    //     std::cout << "client: " << clients[i].get_fd() << std::endl;
    // std::cout<< "Client joined "<< cmd[1] << " successfully !" << std::endl;
}