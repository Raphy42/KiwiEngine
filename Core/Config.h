//
// Created by Raphael DANTZER on 11/27/16.
//

#ifndef KIWIENGINE_CONFIG_H
#define KIWIENGINE_CONFIG_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <string>
#include <iostream>

namespace Kiwi {
    namespace Core {
        class Config {
        public:
            Config(std::string source) {
                boost::property_tree::ini_parser::read_ini(source, _ptree);
            }

            template <typename T>
            T get(const char *key) const {
                try {
                    T value = _ptree.get<T>(key);
                    return (value);
                } catch (const std::exception &e) {
                    std::cerr << e.what() << std::endl;
                }
                return T();
            }

        private:
            boost::property_tree::ptree _ptree;
        };
    }
}

#endif //KIWIENGINE_CONFIG_H
