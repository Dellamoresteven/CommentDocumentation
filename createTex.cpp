/* This file is auto generated by C-Sugar @author Steven Dellamore 
URL = https://github.com/Dellamoresteven/C-Sugar */

// author: Steven Dellamore
// date: 2020-3-9
// version: 1.0.0


// #define yellow "\033[1;33m"

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
#include <boost/algorithm/string.hpp>

using namespace std;

class texWriter {
    private:
    string fullTex = "";
    vector<string> optionalArgs{"@author", "@header"};
    public:
    texWriter() {}

    void replaceInlines( string& contents, int pos, string language ) {
        string AtLink = contents.substr(pos);
        
        auto foundEnd = AtLink.find_first_of( "}" );
        if( foundEnd != string::npos ) {
            AtLink = AtLink.substr( 0, foundEnd+1 );
            string inlineCode = AtLink.substr( 0, foundEnd );
            auto found = inlineCode.find_first_of( "{" );
            inlineCode = inlineCode.substr( found + 1 );
            string form = "\\mintinline[fontsize=\\footnotesize]{" + language + "}{" + inlineCode + "}";
            contents.replace( pos, AtLink.length(), form );
            return;
        }
    }

    void replaceLinks( string& contents, int pos ) {
        string AtLink = contents.substr(pos);
        auto foundEnd = AtLink.find_first_of( "}" );
        if( foundEnd != string::npos ) {
            AtLink = AtLink.substr( 0, foundEnd+1 );
            string varName = AtLink.substr( 0, foundEnd );
            varName.erase(remove( varName.begin(), varName.end(), ' ' ));
            auto found = varName.find_first_of( "{" );
            varName = varName.substr( found + 1 );
            varName.erase(remove( varName.begin(), varName.end(), ' ' ));
            for_each(config::vars.begin(), config::vars.end(), [&](auto &elem){
                if( elem->name == varName ){
                    contents.replace( pos, AtLink.length(), elem->code );
                    return;
                }
            });
        }
    }

    void replace( string& contents, string replace, string replaceWith ) {
        auto pos = contents.find(replace);
        while (pos != string::npos) {
            contents.replace(pos, replace.length(), replaceWith);
            pos = contents.find(replace, pos);
        }
    }

    void WriteHeader() {
        ifstream stream( "templates/startDoc.txt" );
        string contents;
        for (char ch; stream.get(ch); contents.push_back(ch)) {}
        fullTex += contents;
        stream.close();
    }

    void endDoc() {
        ifstream stream( "templates/endDoc.txt" );
        string contents;
        for (char ch; stream.get(ch); contents.push_back(ch)) {}
        fullTex += contents;
        stream.close();
    }

    void frontpage() {
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
        vecReplace.push_back("OFFICE"); // pushing "OFFICE" onto vecReplace
        vecFind.push_back( "@date"); // pushing  "@date" onto vecFind
        vecFind.push_back("@author"); // pushing "@author" onto vecFind
        vecFind.push_back("@company"); // pushing "@company" onto vecFind
        vecFind.push_back("@title"); // pushing "@title" onto vecFind
        vecFind.push_back("@location"); // pushing "@location" onto vecFind
        vecFind.push_back("@email"); // pushing "@email" onto vecFind
        vecFind.push_back("@company"); // pushing "@company" onto vecFind
        vecFind.push_back("@version"); // pushing "@version" onto vecFind
        vecFind.push_back("@office"); // pushing "@office" onto vecFind

        ifstream stream( "templates/frontPage.txt" );
        string contents;

        for (char ch; stream.get(ch); contents.push_back(ch)) {}

        for( int i = 0; i < vecFind.size(); i++ ) {
            for( int j = 0; j < config::frontPage->configMap.size(); j++ ) {
                if( config::frontPage->configMap.at(j).first == vecFind.at(i)) {
                    replace( contents, vecReplace.at(i), config::frontPage->configMap.at(j).second );
                    break;
                } else if( (j + 1) == config::frontPage->configMap.size()) {
                    std::cout << "Did not Provide " << vecFind.at(i) << std::endl << normal;
                }
            }
        }
        fullTex += contents;
    }

    template<typename T> 
    void printReturn(T classToParse) {
        bool isFirst = true;
        ifstream stream( "templates/returnsPage.txt" );
        string contents;
        for (char ch; stream.get(ch); contents.push_back(ch)) {}
        for( auto& e : classToParse->configMap ) {
            if( e.first == "@returns" ) {
                string contentsCopy = contents;
                if( isFirst ){
                    fullTex += "\\textbf{\\large{\\\\Returns}}:\\\\";
                }
                int index = e.second.find(":");
                if(index != string::npos){
                    replace(contentsCopy, "PARAMDEF", e.second.substr(0,index));
                    replace(contentsCopy, "DESC", e.second.substr(index + 2));
                } else {
                    replace(contentsCopy, "PARAMDEF", e.second);
                    replace(contentsCopy, "DESC", "");
                    contentsCopy = contentsCopy.substr(0, contentsCopy.length() - 4);
                }
                isFirst = false;
                fullTex += contentsCopy;
            }
        }
    }

    template<typename T> 
    void printParams(T classToParse) {
        bool isFirst = true;
        ifstream stream( "templates/paramPage.txt" );
        string contents;
        for (char ch; stream.get(ch); contents.push_back(ch)) {}
        for( auto& e : classToParse->configMap ) {
            if( e.first == "@param" ) {
                string contentsCopy = contents;
                if( isFirst ){
                    fullTex += "\n\\textbf{\\large{\\\\Parameters}}:\\\\";
                }
                int index = e.second.find(":");
                replace(contentsCopy, "PARAMDEF", e.second.substr(0,index));
                replace(contentsCopy, "DESC", e.second.substr(index + 2));
                isFirst = false;
                fullTex += contentsCopy;
            }
        }
    }

    template<typename T> 
    void deleteOptional( string& contents, T classToParse ) {
        for( string opt : optionalArgs ){
            auto found = find_if( 
                classToParse->configMap.begin(), 
                classToParse->configMap.end(), 
                [&](auto e)->bool { return e.first == opt; }
            );
            if( found == classToParse->configMap.end() ) { // "@param not found
                string opt2 = opt.substr(1);
                boost::to_upper(opt2);
                auto found2 = contents.find(opt2);
                if( found2 != string::npos ) {
                    size_t secondNL = contents.find("\\opt", found2);
                    size_t firstNL = contents.rfind("\\opt", found2);
                    contents.erase(firstNL, secondNL - firstNL);
                }
            }
        }
    }

    template<typename T> 
    void replacer(T classToParse, int depth, vector<string> howToParseAll) {
        ifstream stream( "templates/" + howToParseAll.at(depth) + ".txt" );
        string contents;
        for (char ch; stream.get(ch); contents.push_back(ch)) {}
        replace( contents, "CLASS", classToParse->name );
        for( int i = 0; i < classToParse->configMap.size(); i++ ) {
            string replaceValue = classToParse->configMap.at(i).first.substr(1);
            boost::to_upper(replaceValue);
            replace( contents, replaceValue, classToParse->configMap.at(i).second );
        }
        deleteOptional( contents, classToParse );
        fullTex += contents;
        printParams(classToParse);
        printReturn(classToParse);
        if( depth != 2 ) {
            for( auto& elem : classToParse->inner ) {
                replacer(elem, depth + 1, howToParseAll);
            }
        }
        stream.close();
    }

    void classpage() {
        vector<string> howToParseAll{"classPage", "functionPage", "methodPage"};
        for( const auto& elem : config::classes ) {
            replacer(elem, 0, howToParseAll);
        }
    }

    void startDoc() {
        WriteHeader();

        frontpage();

        classpage();

        endDoc();

        while(true){
            auto found = fullTex.find( "@link{" );
            if( found != string::npos ) {
                replaceLinks( fullTex, found );
            } else {
                found = fullTex.find( "@inline{" );
                if( found != string::npos ) {
                    replaceInlines( fullTex, found, "javascript" );
                } else {
                    break;
                }
            }
        }

        ofstream out("./output/output.tex", std::ios_base::app);
        out << fullTex;
        out.close();
        cout << "\n\n\n";
        cout << fullTex << endl;
        cout << "\n\n\n";
    }
};