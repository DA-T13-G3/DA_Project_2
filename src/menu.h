//
// Created by gustavobastos on 28/03/26.
//

#ifndef DA_PROJECT_1_MENU_H
#define DA_PROJECT_1_MENU_H

#include "parser.h"
#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

using namespace std;
void nl();
void clear_terminal() ;
void printf_center(const std::string & s, int width,const string& after);
string repeat(const string &str, int n) ;


class  Menu {
    int screen_width=100;
    string bar= repeat("-",screen_width-1)+"\n";
    params1 params1_data;
    params2 params2_data;
    params params_data;
    string output_path = "";

    bool no_params1=true;
    bool no_params2=true;
    bool no_output = true;
public:

    bool run();
    void load_data_ranges();
    void load_data_algorithm();
    void print_liveRanges();
    void print_algorithm();
    void select_output();

    params getParams();
    string getOutput();

    template<typename Func>
    void basic_view_page(const string& title,Func print_data) ;

    template<typename T>
    void list_view_page(const string& title,const vector< T>&data,string(*print_data)(const T&));

private:
    void printn_c(const string &str) ;
    void print_c(const string &str) ;
};




template<typename Func>
void Menu::basic_view_page(const string& title,Func print_data) {



    string line;
    int input;
    string error="\n";

    bool exit=false;
    while (!exit) {
        clear_terminal();
        printn_c(bar);
        printn_c(title);
        printn_c(bar);
        printf("%s", error.c_str());
        nl();

        print_data();

        printf("\n");

        print_c("Press 0 to go back to menu: ");
        try {
            getline(std::cin,line);
            if (line.size()<=1) {
                input=atoi(line.c_str());
                if (line!="0" and input==0) {

                    error="Error: Please enter a valid input\n";
                    input=7;
                }
            }
            else {
                error="Error: Please enter a valid input\n";
                input=7;
            }
        }
        catch (...) {
            error="Error: Please enter a valid input\n";
        }
        if (input == 0) {
            exit=true;
        }


    }

}

template<typename T>
void Menu::list_view_page(const string& title,const vector< T>&data,string(*print_data)(const T&)) {
    basic_view_page<>(title,[&]() {
        int i=0;
        for (const T& d :data) {
            printf(("\t\t"+to_string(i)+" - "+ print_data(d)+"\n\n").c_str());
            i++;
        }
    }
    );
}

#endif //DA_PROJECT_1_MENU_H