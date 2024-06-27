#include "client.h"
#include "server.h"

Client::Client(std::string id, const Server& server) : id(id), server(&server) {
    crypto::generate_key(public_key, private_key);
}

std:: string Client::get_id()const{
    return id;
};

std::string Client::get_publickey()const{
    return public_key;
};

double Client::get_wallet()const{
    return server->get_wallet(id); 
};

std::string Client::sign(std::string txt)const{
    std::string signature = crypto::signMessage(private_key, txt);
    return signature;
};

bool Client::transfer_money(std::string receiver, double value){
    if(server->get_client(receiver) == nullptr){
        return false;
    }
    std::string sender = Client::get_id();
    std::string trx = sender + "-" + receiver + "-" + std::to_string(value);
    Server::parse_trx(trx, sender, receiver, value);
    if (server->get_wallet(sender) < value){
        return false;
    }
    pending_trxs.push_back(trx);
    return true;
};

size_t Client::generate_nonce() {
  return std::rand();
}