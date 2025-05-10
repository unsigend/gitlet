/**
 * This project is part of the gitlet project.
 * The gitlet project is a simple implementation of git command line tool.
 * Under MIT License
 * Copyright (c) 2025, 2026 QIU YIXIANG
 */


/**
 * @file argparse.cpp
 * @brief Implementation of the argparse utility module.
 * @author QIU YIXIANG
 * @copyright (C) 2025, 2026 QIU YIXIANG
 */

#include <argparse/argparse.hpp>

#define ARGPARSE_SHORT_OPTION_PREFIX    '-'
#define ARGPARSE_LONG_OPTION_PREFIX     "--"

namespace __argparse__{
    bool _is_valid_short_option(const std::string& short_option) noexcept {
        return short_option.size() == 2 && short_option[0] == ARGPARSE_SHORT_OPTION_PREFIX;
    }
    bool _is_valid_long_option(const std::string& long_option) noexcept {
        return long_option.size() > 2 && long_option.substr(0, 2) == ARGPARSE_LONG_OPTION_PREFIX;
    }
}
namespace argparse{

    Argparse::Argparse() : _arguments_list() { }
    Argparse::~Argparse() { }

    Argparse::argument::argument(const std::string& short_option, const std::string& long_option,
        const std::string& description, argument_type type) :
        _short_option(short_option), _long_option(long_option),
        _description(description), _type(type), _value("") { }

    Argparse::argument::~argument() { }

    std::string Argparse::_map_short_to_long(const std::string& short_option) const {
        auto iter = this->_short_to_long_map.find(short_option);
        if (iter != this->_short_to_long_map.end()) {
            return iter->second;
        }else{
            return std::string();
        }
    }

    std::pair<bool, std::string> Argparse::_has_option(const std::string& option) const {
        if (__argparse__::_is_valid_short_option(option)){
            // if is a short option
            auto long_option = this->_map_short_to_long(option);
            if (long_option.empty())
                return std::make_pair(false, std::string());
            auto iter = this->_arguments_list.find(long_option);
            if (iter != this->_arguments_list.end()){
                return std::make_pair(true, long_option);
            }
            return std::make_pair(false, std::string());
        }else if (__argparse__::_is_valid_long_option(option)){
            // if is a long option
            auto iter = this->_arguments_list.find(option);
            if (iter != this->_arguments_list.end()){
                return std::make_pair(true, option);
            }
            return std::make_pair(false, std::string());
        }
        return std::make_pair(false, std::string());
    }

    void Argparse::add_option(const std::string& long_option, const std::string& description,
        argument_type type) {
        this->add_option("", long_option, description, type);
    }

    void Argparse::add_option(const std::string& short_option, const std::string& long_option,
        const std::string& description, argument_type type) {
        // the long option must be valid
        if (__argparse__::_is_valid_long_option(long_option)){
            if (!short_option.empty()){
                if (__argparse__::_is_valid_short_option(short_option)){
                    this->_short_to_long_map[short_option] = long_option;
                    this->_arguments_list.emplace(
                        std::make_pair(long_option, argument(short_option, long_option, description, type)));
                }else{
                    throw std::invalid_argument("ARGPARSE ERROR: Invalid short option: " + short_option);
                }
            }else{
                this->_arguments_list.emplace(
                    std::make_pair(long_option, argument("", long_option, description, type)));
            }
        }else{
            throw std::invalid_argument("ARGPARSE ERROR: Invalid long option: " + long_option);
        }
    }

    bool Argparse::has_option(const std::string& option) const {
        return this->_has_option(option).first;
    }

    std::string Argparse::get_argument(const std::string& option) const {
        std::pair<bool, std::string> result = this->_has_option(option);
        if (result.first){
            return this->_arguments_list.find(result.second)->second._value;
        }
        return std::string();
    }
}