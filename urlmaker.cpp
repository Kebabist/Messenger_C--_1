#include "urlmaker.h"

urlmaker::urlmaker(QString command , QString token , QString arguments )
{
    this->command = command;
    this->arguments = arguments;
    this->token = token;
}


QString urlmaker::generate(){
    QString url = "http://api.barafardayebehtar.ml:8080/";
    if (command != "signup" && command != "login" && command != "logout"){ // these three dont have token
        url = url+command+"?"+token+arguments; //should pass the arguments as a QString with &
    }else {
        url = url+command+"?"+arguments; //should pass the arguments as a QString with &
    }
    return url;
}
