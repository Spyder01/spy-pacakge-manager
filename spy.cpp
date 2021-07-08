#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <ctype.h>
using namespace std;


 struct Details {
   string author;
   string project;
   string version="1.0.0";
   string description;
 } details;




class Packager {
public:
   char** args;
   int argN;
   string command;

   Packager (int ArgN, char** Args) {
     args = Args;
     argN = ArgN;
     command = Args[1];
     //cout<<command;
   }
   void checker();
   void init();
   void cloner();

};


void Packager::checker () {
  if(command=="init")
    init();
  else if(command=="clone")
     cloner();
}


void Packager::init () {
  int flag = 0;
  string answer = "no";
  while(!flag) {
    cout<<"\n Project Name: ";
    cin>>details.project;
    cout<<"\n version(1.0.0): ";
    cin>>details.version;
    cout<<"\n author(Your GitHub Username): ";
    cin>>details.author;
    cout<<"\n Description: ";
    cin>>details.description;
    cout<<"\n{ \n ";
    cout<<"\t name: "<<details.project<<"\n";
    cout<<"\t version: "<<details.version<<"\n";
    cout<<"\t author: "<<details.author<<"\n";
    cout<<"\t Description: "<<details.description<<"\n";
    cout<<"}";
    cout<<"\n Is this Okay?(yes)\n";
    cin>>answer;
    transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
    if(answer=="yes")
      flag=1;
    else flag=0;
 }

}

void Packager::cloner () {


  mkdir("spy-Dependencies", 70006);
  chdir("spy-Dependencies");
  mkdir("cloned",70007);
  chdir("cloned");
  //https://github.com/
  string package = "git clone https://github.com/"+string(args[2])+".git";
  char Command[package.length()+1];
  strcpy(Command, package.c_str());
  system(Command);
}






int main (int argN, char** argv) {

   Packager pack(argN, argv);
   pack.checker();

   return 0;

}
