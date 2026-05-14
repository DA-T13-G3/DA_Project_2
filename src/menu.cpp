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

void Menu::run() {

    string line;
    int input;
    string error="\n";
    bool exit=false;
    while (!exit) {
        clear_terminal();
        printn_c(bar);
        printn_c("Assignment Tool");
        printn_c(bar);
        printf((error).c_str());


        printn_c("menu");
        nl();
        printn_c("1-Load data (live ranges)        ");
        nl();
        printn_c("2-Load data (register parameters)");
        nl();
        printn_c("3-View list of live ranges       ");
        nl();
        printn_c("4-View register parameters       ");
        nl();
        printn_c("5-Do the registers' allocation   ");
        nl();
        printn_c("0-Exit                          ");
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
               // load_data();
                break;
            case 2:
               // list_of_submissions();
                break;
            case 3:
               // list_of_reviewers();
                break;
            case 4:
              //  current_parameters();
                break;
            case 5:
              //
               // list_of_assignments();
                break;
            case 7:

                break;
        }


    }

}


void Menu::load_data() {

    string input;
    string error="\n";
    bool exit=false;
    while (!exit) {
        clear_terminal();

        printn_c(bar);
        printn_c("Load data");
        printn_c(bar);
        printf((error).c_str());

        printf(repeat("\n",12).c_str());
        print_c("Write the input filepath (or press 0 to go back to menu):");

        try {
            getline(std::cin,input);
        }
        catch (...) {
            error="Error: Please enter a valid input\n";

        }
        if (input=="0") {
            exit=true;
            break;
        }
        try {
            if (input!="") {
              //  cur_params=parse(input);
                no_data=false;
            }
        }
        catch (...) {
            error="Error: parsing failed\n";
        }


    }



}
/*
string print_submission(const submission& s) {
    string res;
    res="Submission:  Id="+(to_string(s.id))+" / Title="+s.title +" / Authors="+s.name+"\n";
    res=res +"\t\t Email="+s.email+" / Primary Domain="+to_string(s.primary)+" / Secondary Domain="+to_string(s.secondary);
    return res;
}

string print_reviewer(const reviewer& r) {
    string res;
    res="Reviewer:  Id="+(to_string(r.id))+" / Name="+r.name +" Email="+r.email+"\n";
    res=res +"\t\t / Primary Domain="+to_string(r.primary)+" / Secondary Domain="+to_string(r.secondary);
    return res;
}

void Menu::list_of_submissions() {
    list_view_page("Submission List ",cur_params.submissions,print_submission);
}

void Menu::list_of_reviewers() {
    list_view_page("Reviewer List ",cur_params.reviewers,print_reviewer);
}

void Menu::current_parameters() {

    vector<string> params={
        "#Parameters",
    "MinReviewsPerSubmission = "+to_string(cur_params.MinReviewsPerSubmission) ,
    "MaxReviewsPerReviewer = "+to_string(cur_params.MaxReviewsPerReviewer),
    "PrimaryReviewerExpertise = "+to_string(cur_params.PrimaryReviewerExpertise),
    "SecondaryReviewerExpertise = "+to_string(cur_params.SecondaryReviewerExpertise),
    "PrimarySubmissionDomain = "+to_string(cur_params.PrimarySubmissionDomain),
    "SecondarySubmissionDomain = "+to_string(cur_params.SecondarySubmissionDomain),
    "#Control",
    "GenerateAssignments = "+to_string(cur_params.GenerateAssignments),
    "RiskAnalysis = "+to_string(cur_params.RiskAnalysis),
    "OutputFileName = "+cur_params.OutputFileName
    };

    basic_view_page("Current Parameters", [&](){
        if (!no_data) {
            for (const string& s :params) {
                printf(("\t\t"+s+"\n\n").c_str());
            }
        }
    }
    );

}



void Menu::list_of_assignments() {

    basic_view_page("Assignments", [&](){
        if (!no_data) {
            assignment_command(cur_params,cur_params.OutputFileName);
            FILE * file=fopen(cur_params.OutputFileName.c_str(),"r");
            char* line;
            size_t size=0;
            while (getline(&line,&size,file)!=-1) {
                printf(line);
            }
        }

    }
    );

}*/




