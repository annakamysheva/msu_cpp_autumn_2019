#include <iostream> 
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <exception> 

template<class T>
std::string args_to_str(T&& val)
{
    std::stringstream out;
    out << val;
    return out.str();
}

template<class... ArgsT>
std::string format(const std::string& str, ArgsT&&... args)
{
    std::stringstream out;
    int num;
    std::vector<std::string> args_new = {args_to_str(std::forward<ArgsT>(args))... };
    int size = str.size();
    int args_size = args_new.size();
    bool open = false;
    bool close = false;
    
    for (int i = 0; i < size; i++)
    {
        if (close)
        {
            if (str[i] == '}')
            {
                out << args_new[num];
                close = false;
                open=false;
                continue;
            }
            else
            {
                if (!std::isdigit(str[i]))
                {
                    throw std::runtime_error("No closing bracket");
                }
            }
        }
		
        if (!open)
        {
			if (str[i] == '{')
				{
					open = true;
					num=0;
				}
			else if (str[i] == '}')
				{
					throw std::runtime_error("No opening bracket");
				}
			else
				{
					out << str[i];
				}
            
        }
        else
        {
 
			if (std::isdigit(str[i]))
            {
                num*=10;
                num+=str[i] - '0';
                if(num < args_size)
                {
                	close = true;
                    open = false;
                }
                else
                {
                    throw std::runtime_error("More arguments expexted");
                }
            }
			else if(str[i] == '{')
			{
				throw std::runtime_error("No closing bracket");
			}
            else
            {
                throw std::runtime_error("Only numeric argument required");
            }  
			
        }
        
    }

    return out.str();
}