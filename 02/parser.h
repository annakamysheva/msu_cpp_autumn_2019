#include <iostream>
#include <string>
#include <cctype>
#pragma once 

using OnTokenNum = void (*)(std::string token);
using OnToken = void (*)(std::string token);
using OnStart = void (*)();
using OnEnd = void (*)();

void parse(const std::string& text);
void register_on_number_callback(OnTokenNum callback);
void register_on_string_callback(OnToken callback);
void register_start_callback(OnStart callback);
void register_end_callback(OnEnd callback);


