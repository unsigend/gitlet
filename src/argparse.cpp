/**
 * Part of the Implementation of gitlet project
 * Under the MIT License
 * Copyright (c) 2025, 2026 QIU YIXIANG
 */


#include <argparse.hpp>

#define SHORT_OPTION_PREFIX     '-'
#define LONG_OPTION_PREFIX      "--"

namespace gitlet{
    namespace argparse{

        // constructor implementation
        Parser::Parser(int argc, char ** argv, const std::string & prog_name, const std::string & description)
            : _argv(argv), _prog_name(prog_name), _description(description), _option_list() {
                if (argc < 1) {
                    throw std::invalid_argument("INTERNAL ERROR: argc must be greater than 0");
                }
                this->_argc = static_cast<uint32_t>(argc);
                (void)this->_argv;
        }

        Parser::~Parser() { }

        // private method implementation
        void Parser::_check_option(const std::string& short_option, const std::string& long_option) {
            if (short_option.empty() || short_option[0] != SHORT_OPTION_PREFIX){
                throw std::invalid_argument("INTERNAL ERROR: short_option must start with '-'");
            }
            if (!long_option.empty() && long_option.substr(0, 2) != LONG_OPTION_PREFIX){
                throw std::invalid_argument("INTERNAL ERROR: long_option must start with '--'");
            }
            if (this->_option_list.find(short_option) != this->_option_list.end()) {
                throw std::invalid_argument("INTERNAL ERROR: short option already exists");
            }
        }

        // public method implementation
        void Parser::add_option(const std::string& short_option, const std::string& description, 
            arg_type type) {
            this->add_option(short_option, "", description, type);
        }
        void Parser::add_option(const std::string& short_option, const std::string& long_option, 
            const std::string& description, arg_type type) {
            // Make sure that short_option and long_option are valid
            this->_check_option(short_option, long_option);

            // construct the option object and add it to the hash table
            option opt;
            opt._short_option = short_option;
            opt._long_option = long_option;
            opt._description = description;
            opt._type = type;
            this->_option_list[short_option] = opt;
        }
    }
}