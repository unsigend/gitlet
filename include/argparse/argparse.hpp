/**
 * Part of the Implementation of gitlet project
 * Under the MIT License
 * Copyright (c) 2025, 2026 QIU YIXIANG
 */

#ifndef ARGPARSE_ARGPARSE_HPP
#define ARGPARSE_ARGPARSE_HPP
// the argparse header file is originally designed for gitlet project

#include <string>
#include <exception>
#include <unordered_map>

namespace argparse{
    /**
     * @brief A class to parse command line arguments.
     * 
     * It provides a simple interface to parse command line arguments
     * and store them in a hash map with long options as keys. And store the 
     * value as a struct argument. Which means the value can be any type of data.
     * And must be converted to the type by user.
     */
    class Argparse{
        public: 
            /**
             * @category struct
             * @brief argument_type is an enum class to define the type of argument.
             * 
             * It can be required_argument, optional_argument or no_argument.
             * It is undefined if try to get a value from no_argument.
             */
            enum argument_type {
                required_argument,
                optional_argument,
                no_argument
            };
        public:
            Argparse();
            ~Argparse();

            /**
             * @brief Check whether the option is exist in the arguments list.
             * 
             * @option: the option to check, may be short or long option
             * @return true: if the option is exist
             * @return false: if the option is not exist
             */
            bool has_option(const std::string& option) const;

            /**
             * @brief Get the argument of the option.
             * 
             * @option: the option to get, may be short or long option
             * @return  the argument of the option 
             *          will return empty string if the option is not exist
             *          or the argument type is no_argument
             */
            std::string get_argument(const std::string& option) const;

            /**
             * @brief Add an option to the arguments list.
             * 
             * @long_option: the long option
             * @description: the description of the option
             * @type: the type of the option
             */
            void add_option(const std::string& long_option, const std::string& description, 
                argument_type type = required_argument);

            /**
             * @brief Add an option to the arguments list.
             * 
             * @short_option: the short option
             * @long_option: the long option
             * @description: the description of the option
             * @type: the type of the option
             */
            void add_option(const std::string& short_option, const std::string& long_option,
                const std::string& description, argument_type type = required_argument);

            void parser(int argc, char* argv[]);

        private:
            class argument{
                public:
                    std::string _short_option;
                    std::string _long_option;
                    std::string _description;
                    argument_type _type;
                    std::string _value;

                    argument(const std::string& short_option, const std::string& long_option,
                        const std::string& description, argument_type type);
                    ~argument();
            };

            std::unordered_map<std::string, argument> _arguments_list;
            std::unordered_map<std::string, std::string> _short_to_long_map;
        
        private:
            /**
             * @category private
             * @brief Map the short option to long option.
             *        if the short option is not found in map table, return an empty string.
             * @return long_option
             */
            std::string _map_short_to_long(const std::string& short_option) const;

            /**
             * @category private
             * @brief Check if the option is exist in the arguments list.
             *        if the option is not found in map table, return a pair of false and empty string.
             *        if the option is found, return a pair of true and long option.
             * @return pair<bool, long_option>
             */
            std::pair<bool, std::string> _has_option(const std::string& option) const;
    };
}

namespace __argparse__{

    /**
     * @brief Check if the short option is valid.
     *        The short option must be a string with length 2 and the first character is '-'.
     */
    bool _is_valid_short_option(const std::string& short_option) noexcept;

    /**
     * @brief Check if the long option is valid.
     *        The long option must be a string with length > 2 and the first two characters are '--'.
     */
    bool _is_valid_long_option(const std::string& long_option) noexcept;
}


#endif