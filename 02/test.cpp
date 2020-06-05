#include "parser.h"

using namespace std;

void Starting(){
    cout << "Let's begin." << endl;
}

void Ending(){
    cout << "I'm done. See you next time." << endl;
}

void Found_num_token(string s){
    cout << "Omg, new num for you ^_^  :  " << s << endl; 
}

void Found_str_token(string s){
    cout << "Omg, new string for you ^_^  :  " << s << endl; 
}


int main(){

    register_on_number_callback(Found_num_token);
    register_on_string_callback(Found_str_token);
    register_start_callback(Starting);
    register_end_callback(Ending);

    //test 1
    string s_1 = "aba \t\n 23 tt 3";
    parse(s_1);

    //test 2
    string s_2 = "\t\n";
    parse(s_2);

    return 0;
}