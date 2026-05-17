//
// Created by gustavobastos on 28/03/26.
//

/**
 * @file Menu.h
 * @brief Console-based user interface for the allocation tool.
 *
 * Provides an interactive menu system that allows the user to:
 * - Load input data
 * - View live ranges and algorithm parameters
 * - Select and view selected output file
 * - Execute allocation generation
 */

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

 /**
 * @class Menu
 * @brief Handles the interactive console menu.
 *
 * Manages user interaction and navigation between different views,
 * including data loading, visualization, and allocation execution.
 */
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

    /**
     * @brief Starts the main menu loop.
     */
    bool run();

    /**
     * @brief Loads input data from input file 1.
     */
    void load_data_ranges();

    /**
     * @brief Loads input data from input file 2.
     */
    void load_data_algorithm();

    /**
     * @brief Displays the list of variable live ranges.
     */
    void print_liveRanges();

    /**
     * @brief Displays the algorithm parameters.
     */
    void print_algorithm();

    /**
     * @brief Allows for selection of output file.
     */
    void select_output();

    /**
     * @brief Accessor to retrieve the fully consolidated and parsed runtime parameters.
     * @return The final 'params' execution payload structure.
     */
    params getParams();

    /**
     * @brief Accessor to retrieve the verified target output directory file path destination.
     * @return A string representation of the target output file.
     */
    string getOutput();

    /**
     * @brief Generic page with custom content.
     *
     * @param title Page title
     * @param print_data Function that prints the content
     */
    template<typename Func>
    void basic_view_page(const string& title,Func print_data) ;

    /**
     * @brief Displays a list-based page.
     *
     * @param title Page title
     * @param data Vector of elements
     * @param print_data Function that converts elements to string
     */
    template<typename T>
    void list_view_page(const string& title,const vector< T>&data,string(*print_data)(const T&));

private:
    /**
     * @brief Prints centered text with newline.
     */
    void printn_c(const string &str) ;

    /**
     * @brief Prints centered text without newline.
     */
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