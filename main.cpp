/* This file is auto generated by C-Sugar @author Steven Dellamore 
URL = https://github.com/Dellamoresteven/C-Sugar */

// author: Steven Dellamore
// date: 2020-3-1
// version: 1.0.0


#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cctype>
#include <list>
#include <sys/stat.h>
#include <unistd.h>
#include <functional>
#include <map>
#include <sstream>
#include <iterator>
#include <string>
#include <functional>
#include <iomanip>

#include "config.cpp"
#include "createTex.cpp"

using namespace std;
using namespace config;
using namespace createtex;

#define green "\u001b[32m"
#define red "\u001b[31m"
#define normal "\033[0m"

template <typename T >
string getNextComment( T &stream ) {
    string fullLine = "";
    string line;
    while (getline( stream, line )) {
        // found @TODO
        auto found = line.find("//");
        if (found != string::npos) {

            const std::string& chars = "\t\v\f\r ";
            line.erase(0, line.find_first_not_of(chars));

            if(line.at(0) == '/' && line.at(1) == '/'){
                fullLine += line.substr(2);
            } else {
                fullLine += line;
            }

            if(line.at(line.length() - 1) == '|' || line.at(line.length() - 2) == '|'){
                fullLine = "//" + fullLine;
                // cout << "fullLine: " << fullLine << endl << endl;
                return fullLine;
            }
        }
    }
    return "-1";
}

static Header * currHeader;
static vector<string> validTagList = { "#frontpage", "#class" };
static vector<string> validTagListIsInner = { "#function" };
static vector<string> validConfigList = { "@author", "@date", 
                                        "@version", "@company", 
                                        "@title", "@location",
                                        "@email", "@name", "@desc",
                                        "@code", "@param", "@return", "@header" };


template <typename T, typename U >
auto parseLineWithComment( T line, U &file ) {
    cout << line << endl;
    if( line == "-1" ) return;

    stringstream lineReaderSS( line );
    string word;
    

    auto getSubstance = [&](auto &stream) mutable {
        string name; 
        while( stream >> word  ) {
            if(word == "|") {
                return name.substr( 0, name.length() - 1 );
            }
            name += word;
            name += " ";
        }
        cout << "UH OHOHH" << endl;
        return name.substr( 0, name.length() - 1 ); 
    };

    while( lineReaderSS >> word ) {
        if( std::find( validTagListIsInner.begin(), validTagListIsInner.end(), word ) != validTagListIsInner.end() ) {
            Header * e = new config::Header();
            // headerMap.push_back( e );
            e->typ = word;
            string longerName;
            lineReaderSS >> longerName;
            size_t found = longerName.find("::"); 
            if (found != string::npos) {
                for( int i = 0; i < headerMap.size(); i++ ) {
                    if(headerMap[i]->name == longerName.substr(0,found)){
                        e->depth = headerMap[i]->depth + 1;
                        e->name = longerName.substr(found + 2);
                        headerMap[i]->inner.push_back(e);
                    }
                }
                 // objectTest
                // longerName.substr(found + 2) // functionTest
            }
            currHeader = e;
        } 
        if( std::find( validTagList.begin(), validTagList.end(), word ) != validTagList.end() ) {
            Header * e = new config::Header();
            e->typ = word;
            lineReaderSS >> e->name;
            headerMap.push_back( e );
            currHeader = e;
        }

        if( currHeader != NULL ) {
            if( std::find( validConfigList.begin(), validConfigList.end(), word ) != validConfigList.end() ) {
                string temp = word;
                currHeader->configMap.push_back(std::pair<string,string>(temp, getSubstance( lineReaderSS )));
            }
        }
    }
}

ostream& operator<<(ostream& os, const Header* hd) {
    os << green << std::setw(hd->depth * 8) <<"type: " << hd->typ << std::setw( (50 - hd->typ.length()) ) << " name: " << hd->name << "\n";
    for_each(hd->configMap.begin(), hd->configMap.end(), [&](const std::pair<string,string> &p){
        os << red << std::setw(hd->depth * 8) << "{" << p.first << ": " << std::setw( (56 - p.first.length()) ) << p.second << "}\n" << normal;
    });
    for( int i = 0; i < hd->inner.size(); i++ ) {
        cout << hd->inner[i];
    }
    return os;
}

int main(int argc, char* argv[])  {
    ifstream file( "input/text.cpp" );
    string found;
    while( found != "-1" ) {
        found = getNextComment( file );
        parseLineWithComment( found, file ); 
    }
    std::cout << "HEADER MAP" << std::endl;
    // Printing out the entire headerMap vector with delim: "\n"
    for (auto i = headerMap.begin(); i != headerMap.end(); ++i)
    {
        std::cout << *i << "\n";
    }

    startDoc();

    return 0;
}
