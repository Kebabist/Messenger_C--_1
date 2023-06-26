#include "client.h"

//Client class constructor
Client::Client(QString username ,QString password ,QString firstname ,QString lastname)
{
    this->username = username;
    this->password = password;
    this->firstname = firstname;
    this->lastname = lastname;
}

//Signs up a new user
void Client::Singup(){
    //send a http request to the server with url = http://api.barafardayebehtar.ml:8080/signup?username=user&password=pass&firstname=first&lastname=last
    //handle the servers response
}
