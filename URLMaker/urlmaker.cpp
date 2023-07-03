#include "urlmaker.h"
#include "qdebug.h"

//default constructor
urlmaker::urlmaker()
    : command(""), token(""), arguments("")
{}

//urlmaker constructor
urlmaker::urlmaker(QString command , QString token , QString arguments )
{   try{
        this->command = command;
        this->arguments = arguments;
        this->token = token;
    }catch (...) {
        qDebug() << "Unknown exception caught";
    }
}

//Special constructor with two arguments for when the token has not been initilized by server
urlmaker::urlmaker(QString command , QString arguments )
{   try{
        this->command = command;
        this->arguments = arguments;
    }catch (...) {
        qDebug() << "Unknown exception caught";
    }
}

//generates urls for httprequest to the server
const QString urlmaker::generate(){
    try{
        QString url = "http://api.barafardayebehtar.ml:8080/";
        if (command != "signup" && command != "login" && command != "logout"){ // these three dont have token
            url = url+command+"?"+"token="+token+"&"+arguments; //should pass the arguments as a QString with &
        }else {
            url = url+command+"?"+arguments; //should pass the arguments as a QString with &
        }
        return url;
    }catch (...) {
        qDebug() << "Unknown exception caught";
    }
}
