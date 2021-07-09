#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <ctype.h>
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;



//Structure to store initialiazation details.
 struct Details {
   string author;
   string project;
   string version="1.0.0";
   string description;

 } details;



//Package Manager Class
class Packager {
public:
   char** args;
   int argN;
   string command;
   fstream spyJSON;
   json JSON;

   Packager (int ArgN, char** Args) {
     args = Args;
     argN = ArgN;
     command = Args[1];
     //cout<<command;
   }
   void checker();
   void init();
   bool exists(const string name);
   void cloner();
   void JSONLoader();
   void ClonePusher(char* Identity, string section);
   void depsInstaller();
   void depsInstallerSectionCloned ();

};


//Function to keppa check on the commands.
void Packager::checker () {
  if(command=="init")
    init();
  else if(command=="clone")
     cloner();
  else if(command=="deps")
     depsInstaller ();
}



//Function to initiaze the project.
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

  ofstream JSONFile;
  JSONFile.open("spy-package.json");
  JSON["author"] = details.author;
  JSON["version"] = details.version;
  JSON["description"] = details.description;
  JSON["name"] = details.project;
  JSON["dependencies"]["cloned"] =  json::array();
  JSON["dependencies"]["installed"] = json::array();
  JSONFile<<JSON.dump(4);
  JSONFile.close();
}

bool Packager::exists (const string name) {
    return ( access( name.c_str(), F_OK ) != -1 );
}

//Function to add outside cloned repositories.
void Packager::cloner () {
if(exists("spy-package.json")){
  JSONLoader ();
  char* Identity = args[2];
  mkdir("spy-Dependencies", 70006);
  chdir("spy-Dependencies");
  mkdir("cloned",70007);
  chdir("cloned");
  //https://github.com/
  string package = "git clone https://github.com/"+string(args[2])+".git";
  char Command[package.length()+1];
  strcpy(Command, package.c_str());
try {
  system(Command);
}
 catch(...) {
   exit(0);
 }
 chdir("..");
 chdir("..");
 ClonePusher(Identity, "cloned");

 }
  else cerr<<"\n ERROR: \"Initialize Your Project First\"\n";
}

//Function to load the JSON with spy-package.json
void Packager::JSONLoader () {
  ifstream i("spy-package.json");
  i >> JSON;
}

//Function to register the cloned repository to spy-package.json
void Packager::ClonePusher(char* Identity, string section) {
  int flag = 1;
  for (int i=0; i<JSON["dependencies"][section].size();i++) {
     if(string(Identity)==JSON["dependencies"][section][i])
       flag = 0;
  }
if(flag) {
  JSON["dependencies"][section].push_back(Identity);
  ofstream spyJSON;
  spyJSON.open("spy-package.json");
  spyJSON<<JSON.dump(4);
  spyJSON.close();
}

}


//Function to install dependencies from spy-package,json
void Packager::depsInstaller () {
   depsInstallerSectionCloned ();
   //depsInstallerSectionInstalled ("installed");
}

void Packager::depsInstallerSectionCloned () {
JSONLoader();
mkdir("spy-Dependencies", 70006);
chdir("spy-Dependencies");
mkdir("cloned", 70007);
chdir("cloned");
for(int i=0; i<JSON["dependencies"]["cloned"].size(); i++) {
    string command = "git clone https://github.com/"+string(JSON["dependencies"]["cloned"][i])+".git";
    system(command.c_str());
  }
chdir("..");
chdir("..");
}




int main (int argN, char** argv) {

   Packager pack(argN, argv);
   pack.checker();

   return 0;

}
