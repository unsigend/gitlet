/**
 * Part of the Implementation of gitlet project
 * Under the MIT License
 * Copyright (c) 2025, 2026 QIU YIXIANG
 */

// header file for argparse module in gitlet

#ifndef GITLET_ARGPARSE_HPP
#define GITLET_ARGPARSE_HPP
#include <general/external.hpp>

namespace gitlet{
    namespace argparse{
        // option : argument
        class Parser{
            public:
                enum arg_type{
                    required_argument,
                    optional_argument,
                    no_argument
                };
            private:
                typedef struct _option{
                    std::string _short_option;
                    std::string _long_option;
                    std::string _description;
                    arg_type _type;
                    std::string _value;
                } option;

                uint32_t _argc;
                char ** _argv;
                std::string _prog_name;
                std::string _description;
                std::unordered_map<std::string, option> _option_list;
            private:
                void _check_option(const std::string& short_option, const std::string& long_option);
                void _check_add_option(const std::string& short_option, const std::string& long_option);
            public:
                Parser(int argc, char ** argv, const std::string & prog_name, const std::string & description);
                ~Parser();
                void add_option(const std::string& short_option, const std::string& description, 
                    arg_type type = required_argument);
                void add_option(const std::string& short_option, const std::string& long_option, 
                    const std::string& description, arg_type type = required_argument);
                bool has_option(const std::string& short_option);
        };
    }
}

#endif