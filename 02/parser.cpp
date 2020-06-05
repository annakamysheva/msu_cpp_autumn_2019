#include "parser.h"

OnTokenNum number_callback;
OnToken string_callback;
OnStart start_callback;
OnEnd end_callback;

void register_on_number_callback(OnTokenNum callback){
  number_callback = callback;
}
void register_on_string_callback(OnToken callback){
  string_callback = callback;
}
void register_start_callback(OnStart callback){
  start_callback = callback;
}
void register_end_callback(OnEnd callback){
  end_callback = callback;
}

using namespace std;

void parse(const string &text) {

    string string_token = "";
    string num_token = "";
    int i = 0;
    start_callback();

    if (!(start_callback && end_callback \
    && number_callback && string_callback)){
        return;
    } 

    while (i < text.length()){
        if (isdigit(text[i])){
            while (isdigit(text[i])){
                num_token += text[i];
                ++i;
            }
            number_callback(num_token);
            ++i;
            num_token = "";
        }
        else if(isalpha(text[i])){
            while (isalpha(text[i])){
                string_token += text[i];
                ++i;
            }
            string_callback(string_token);
            ++i;
            string_token = "";
        }
        else{
            i++;
        }
    };
    end_callback();
}
