//
// Created by gustavobastos on 28/03/26.
//

#include "menu.h"

#include <cstdlib>

void nl() {
    printf("\n");
}
void clear_terminal() {
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";
    std::cout << "\033[2J\033[H";

    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";

}

string repeat(const string &str, int n) {
    std::string p;
    for (unsigned int i = 0; i < n; i++) {
        p+=str;;
    }
    return p;
}

void printf_center(const std::string & s, int width,const string& after="\n") {

    int padding = (width - s.size()) / 2;




    // Se a largura for maior que a string, imprime espaços à esquerda
    if (padding > 0) {

        string p=repeat(" ",padding);
        printf("%s%s%s",p.c_str() , s.c_str(),after.c_str());
    } else {
        printf("%s", s.c_str());
    }
}

void Menu::printn_c(const string &str) {
    printf_center(str, screen_width);

}
void Menu::print_c(const string &str) {
    printf_center(str, screen_width,"");

}

bool Menu::run() {

    string line;
    int input;
    string error="\n";
    bool exit=false;
    while (!exit) {
        clear_terminal();
        printn_c(bar);
        printn_c("Register Allocation Tool");
        printn_c(bar);
        printf("%s", error.c_str());


        printn_c("Menu");
        nl();
        printn_c("1-Load data (live ranges)        ");
        nl();
        printn_c("2-Load data (register parameters)");
        nl();
        printn_c("3-View list of live ranges       ");
        nl();
        printn_c("4-View register parameters       ");
        nl();
        printn_c("5-Choose output directory        ");
        nl();
        printn_c("6-Do the registers' allocation   ");
        nl();
        printn_c("0-Exit                           ");
        nl();
        print_c("Select one of the following options (write a number):");
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
            input=7;
        }

        switch (input) {
            case 0:
                exit=true;
                break;
            case 1:
                load_data_ranges();
                break;
            case 2:
                load_data_algorithm();
                break;
            case 3:
                print_liveRanges();
                break;
            case 4:
                print_algorithm();
                break;
            case 5:
                select_output();
                break;
            case 6:
                if (no_params1 && no_params2){
                    printf("Live ranges and register parameters missing/invalid.");
                } else if (no_params1){
                    printf("Live ranges missing/invalid.");
                } else if (no_params2){
                    printf("Register parameters missing/invalid.");
                } else {
                    if (no_output){
                        printf("Output path missing/invalid.");
                    } else {
                        params_data = parse(params1_data, params2_data);
                        return true;
                    }
                    
                }
                break;
            case 7:

                break;
        }


    }
    return false;

}


void Menu::load_data_ranges() {

    string input;
    string error="\n";
    bool exit=false;
    while (!exit) {
        clear_terminal();

        printn_c(bar);
        printn_c("Load live ranges");
        printn_c(bar);
        printf("%s", error.c_str());

        printf("%s", repeat("\n",12).c_str());
        print_c("Write the input filepath (or press 0 to go back to menu):");

        try {
            getline(std::cin,input);
        }
        catch (...) {
            error="Error: Please enter a valid input\n";
            continue;
        }
        if (input=="0") {
            exit=true;
            break;
        }
        try {
            if (input!="") {
                params1 p1;
                parse1(input, p1);
                if (!p1.valid){
                    throw runtime_error("Error: parsing failed\n");
                }
                params1_data=p1;
                no_params1=false;
                exit = true;
            }
        }
        catch (const runtime_error& e) {
            error=e.what();
        }
        catch (...) {
            error="Error: An unexpected error occurred.\n";
        }
    }
}

void Menu::load_data_algorithm() {

    string input;
    string error="\n";
    bool exit=false;
    while (!exit) {
        clear_terminal();

        printn_c(bar);
        printn_c("Load algorithm data");
        printn_c(bar);
        printf("%s", error.c_str());

        printf("%s", repeat("\n",12).c_str());
        print_c("Write the input filepath (or press 0 to go back to menu):");

        try {
            getline(std::cin,input);
        }
        catch (...) {
            error="Error: Please enter a valid input\n";
            continue;
        }
        if (input=="0") {
            exit=true;
            break;
        }
        try {
            if (input!="") {
                params2 p2;
                parse2(input, p2);
                if (!p2.valid){
                    throw runtime_error("Error: parsing failed\n");
                }
                params2_data=p2;
                no_params2=false;
                exit = true;
            }
        }
        catch (const runtime_error& e) {
            error=e.what();
        }
        catch (...) {
            error="Error: An unexpected error occurred.\n";
        }
    }
}

string print_range(const web& w){
    string output;
    set<int> startSet(w.start.begin(), w.start.end());
    set<int> endSet(w.end.begin(), w.end.end());
    bool first = true;
    for (int line : w.lines) {
        if (!first) output += ",";
        output += to_string(line);
        if (startSet.count(line)) output += "+";
        if (endSet.count(line)) output += "-";
        first = false;
    }
    return output;
}

void Menu::print_liveRanges(){
    if (!params1_data.valid){
        printf("Invalid Live ranges.");
        return;
    }
    basic_view_page("Live Ranges", [&](){
        for (auto w : params1_data.webs){
            printf("web%s: %s\n", w.id.c_str(), print_range(w).c_str());
        }
    });
    
}

void Menu::print_algorithm(){
    if (!params2_data.valid){
        printf("Invalid Register parameters.");
        return;
    }
    basic_view_page("Register parameters", [&](){
        printf("Registers: %d\n\n", params2_data.regs);
    
        string alg_name;
        switch (params2_data.alg.type){
            case basic:
                alg_name = "basic";
                break;
            case spilling:
                alg_name = "spilling";
                break;
            case splitting_:
                alg_name = "splitting";
                break;
            case free_:
                alg_name = "free";
                break;
            default:
                alg_name = "Unknown algorithm type";
                break;
        }
        printf("Algorithm type: %s; Algorithm value: %d\n", alg_name.c_str(), params2_data.alg.val);
    });
    
}

void Menu::select_output(){
    string input;
    string error="\n";
    bool exit=false;
    while (!exit) {
        clear_terminal();

        printn_c(bar);
        printn_c("Choose output file");
        printn_c(bar);
        if (output_path == ""){
            printf("Current output file: {None}\n");
        } else {
            printf("Current output file: %s\n", output_path.c_str());
        }
        printf("%s", error.c_str());
        

        printf("%s", repeat("\n",12).c_str());
        print_c("Write the relative output filepath and file name (or press 0 to go back to menu):");

        try {
            getline(std::cin,input);
        }
        catch (...) {
            error="Error: Please enter a valid input\n";
            continue;
        }
        if (input=="0") {
            exit=true;
            break;
        }
        try {
            if (input!="") {

                ofstream output(input);
                if (!output.good()) {
                    throw runtime_error("Error: Unable to locate/create file\n");
                } else {
                    output.close();
                    output_path = input;
                    no_output = false;
                    exit = true;
                }

            }
        }
        catch (const runtime_error& e) {
            error=e.what();
        }
        catch (...) {
            error = "Error: An unexpected error occurred.\n";
        }
    }
}

params Menu::getParams(){
    return params_data;
}
string Menu::getOutput(){
    return output_path;
}


