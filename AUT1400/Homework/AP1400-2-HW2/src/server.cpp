#include <memory>
#include <string>
#include <stdexcept>
#include <sstream>
#include <vector>
#include "server.h"
#include "client.h"

Server::Server(){}

std::shared_ptr<Client> Server::add_client(std::string id){
    for (const auto& client:clients){
        if(client.first ->get_id() == id){
            id += std::to_string( std::rand() % 9000 + 1000);
        }
    }
    auto client_ptr = std::make_shared<Client>(id, *this);
    Server::clients[client_ptr] = 5;
    return client_ptr;
}

std::shared_ptr<Client> Server::get_client(const std::string id)const{
    for (const auto& client:clients){
        if(client.first ->get_id() == id){
            return client.first;
        }
    }
    return nullptr;
}

double Server::get_wallet(std::string id)const {
    for (const auto& client:clients){
        if(client.first ->get_id() == id){
            return client.second;
        }
    }
    return 0.0;
};

bool Server::parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value){
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(trx);
    char delimiter = '-';
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    if (tokens.size() < 3) {
        std::cout<<"error!"<< std::endl;
        throw std::runtime_error("wrong trx");
        return false;
    }
    sender = tokens[0];
    receiver = tokens[1];
    value = std::stod(tokens[2]);
    return true;
};

size_t Server::mine() {
    std::string mempool;
    for (const auto& trx : pending_trxs) {
        mempool += trx;
    }
    size_t nonce{0};
    while (true) {
        for(auto &client : clients) {
            nonce = client.first->generate_nonce();
            std::string hash = crypto::sha256(mempool + std::to_string(nonce));
            if (hash.substr(0, 10).find("000") != std::string::npos) {
            // Reward the miner (simplified, assuming the miner is "sarah" for illustration)
                clients[client.first] += 6.25;
                for(auto pending_trx : pending_trxs) {
                    std::string sender, receiver;
                    double value;
                    parse_trx(pending_trx, sender, receiver, value);
                    for(auto &client: clients) {
                        if(client.first->get_id() == sender) {
                        client.second -= value;
                        } 
                        else if(client.first->get_id() == receiver) {
                        client.second += value;
                        }
                    }
                }
                pending_trxs.clear();
                std::cout << "miner " << client.first->get_id() << " successfully get the award!" << std::endl;
                return nonce;
            }
        }
    }
}



