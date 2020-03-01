/* This file is auto generated by C-Sugar @author Steven Dellamore 
URL = https://github.com/Dellamoresteven/C-Sugar */

#ifndef MY_CREATETEX
#define MY_CREATETEX

// author: Steven Dellamore
// date: 2020-2-29
// version: 1.0.0


#define yellow "\033[1;33m"

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
#include <unordered_map>
#include <boost/bind.hpp>

using namespace std;

namespace createtex {

    static void fixHighlighting(){}

    static void replace( string& contents, string replace, string replaceWith ) {
        {} // fix the weird syntex highlighting
        auto pos = contents.find(replace);
        while (pos != string::npos) {
            contents.replace(pos, replace.length(), replaceWith);
            pos = contents.find(replace, pos);
        }
    }

    static void WriteHeader() {
        ifstream stream( "templates/startDoc.txt" );
        string contents;
        for (char ch; stream.get(ch); contents.push_back(ch)) {}
        ofstream out("./output/output.tex");
        out << contents;
        out.close();
    }

    static void endDoc() {
        ifstream stream( "templates/endDoc.txt" );
        string contents;
        for (char ch; stream.get(ch); contents.push_back(ch)) {}
        ofstream out("./output/output.tex", std::ios_base::app);
        out << contents;
        out.close();
    }

    static void frontpage( config::Header* header ) {
        // vecReplace @TODO
        auto vecReplace = std::vector< string >();
        // vecFind @TODO
        auto vecFind = std::vector< string >();
        vecReplace.push_back( "DATE"); // pushing  "DATE" onto vecReplace
        vecReplace.push_back("AUTHOR"); // pushing "AUTHOR" onto vecReplace
        vecReplace.push_back("COMPANY"); // pushing "COMPANY" onto vecReplace
        vecReplace.push_back("TITLE"); // pushing "TITLE" onto vecReplace
        vecReplace.push_back("LOCATION"); // pushing "LOCATION" onto vecReplace
        vecReplace.push_back("EMAIL"); // pushing "EMAIL" onto vecReplace
        vecReplace.push_back("COMPANY"); // pushing "COMPANY" onto vecReplace
        vecReplace.push_back("VERSION"); // pushing "VERSION" onto vecReplace
        vecFind.push_back( "@date"); // pushing  "@date" onto vecFind
        vecFind.push_back("@author"); // pushing "@author" onto vecFind
        vecFind.push_back("@company"); // pushing "@company" onto vecFind
        vecFind.push_back("@title"); // pushing "@title" onto vecFind
        vecFind.push_back("@location"); // pushing "@location" onto vecFind
        vecFind.push_back("@email"); // pushing "@email" onto vecFind
        vecFind.push_back("@company"); // pushing "@company" onto vecFind
        vecFind.push_back("@version"); // pushing "@version" onto vecFind

        ifstream stream( "templates/frontPage.txt" );
        string contents;

        for (char ch; stream.get(ch); contents.push_back(ch)) {}

        for( int i = 0; i < vecFind.size(); i++ ) {
            for( int j = 0; j < header->configMap.size(); j++ ) {
                if(header->configMap.at(j).first == vecFind.at(i)) {
                    replace( contents, vecReplace.at(i), header->configMap.at(j).second );
                    break;
                } else if( (j + 1) == header->configMap.size()) {
                    std::cout << yellow << "Did not Provide " << vecFind.at(i) << std::endl << normal;
                }
            }
        }

        ofstream out("./output/output.tex", std::ios_base::app);
        out << contents;
        out.close();
    }

    static void functionpage( config::Header* header ) {
        // vecReplace @TODO
        auto vecReplace = std::vector< string >();
        // vecFind @TODO
        auto vecFind = std::vector< string >();
        vecReplace.push_back( "AUTHOR"); // pushing  "AUTHOR" onto vecReplace
        vecReplace.push_back("DESC"); // pushing "DESC" onto vecReplace
        vecFind.push_back( "@author"); // pushing  "@author" onto vecFind
        vecFind.push_back("@desc"); // pushing "@desc" onto vecFind

        ifstream stream( "templates/functionPage.txt" );
        string contents;

        for (char ch; stream.get(ch); contents.push_back(ch)) {}

        replace( contents, "FUNC", header->name );
        for( int i = 0; i < vecFind.size(); i++ ) {
            for( int j = 0; j < header->configMap.size(); j++ ) {
                if(header->configMap.at(j).first == vecFind.at(i)) {
                    replace( contents, vecReplace.at(i), header->configMap.at(j).second );
                    break;
                } else if( (j + 1) == header->configMap.size()) {
                    std::cout << yellow << "Did not Provide " << vecFind.at(i) << std::endl << normal;
                }
            }
        }

        ofstream out("./output/output.tex", std::ios_base::app);
        out << contents;
        out.close();
    }

    static void classpage( config::Header* header ) {
        // vecReplace @TODO
        auto vecReplace = std::vector< string >();
        // vecFind @TODO
        auto vecFind = std::vector< string >();
        vecReplace.push_back( "AUTHOR"); // pushing  "AUTHOR" onto vecReplace
        vecReplace.push_back("DESC"); // pushing "DESC" onto vecReplace
        vecFind.push_back( "@author"); // pushing  "@author" onto vecFind
        vecFind.push_back("@desc"); // pushing "@desc" onto vecFind

        ifstream stream( "templates/classPage.txt" );
        string contents;

        for (char ch; stream.get(ch); contents.push_back(ch)) {}

        replace( contents, "CLASS", header->name );
        for( int i = 0; i < vecFind.size(); i++ ) {
            for( int j = 0; j < header->configMap.size(); j++ ) {
                if(header->configMap.at(j).first == vecFind.at(i)) {
                    replace( contents, vecReplace.at(i), header->configMap.at(j).second );
                    break;
                } else if( (j + 1) == header->configMap.size()) {
                    std::cout << yellow << "Did not Provide " << vecFind.at(i) << std::endl << normal;
                }
            }
        }



        ofstream out("./output/output.tex", std::ios_base::app);
        out << contents;
        out.close();
        for( int i = 0; i < header->inner.size(); i++ ) {
            functionpage( header->inner[i] );
        }
    }

    static void loopThroughHeaderMap() {
        for_each(config::headerMap.begin(), 
                config::headerMap.end(),
                [](auto &x){
                    // cout << x->typ << endl;
                    if( x->typ == "#frontpage" )
                        frontpage( x );
                    if( x->typ == "#class" ){
                        classpage( x );
                    }
                });
    }

    static void startDoc() {
        fixHighlighting();
        // auto x = config::headerMap;
        WriteHeader();

        loopThroughHeaderMap();

        endDoc();
    }
}

#endif