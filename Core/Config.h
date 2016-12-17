//
// Created by Raphael DANTZER on 11/27/16.
//

#ifndef KIWIENGINE_CONFIG_H
#define KIWIENGINE_CONFIG_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <iostream>

namespace Kiwi {
    namespace Core {

        class Config {
        public:
            Config() = default;

            Config(std::string source) : _filename(source) {}

            virtual ~Config() {};

            virtual void save() = 0;

        protected:
            std::string _filename;
            boost::property_tree::ptree _ptree;
        };

        class INIConfig : public Config {
        public:
            INIConfig() = default;


            INIConfig(std::string source) : Config(source) {
                boost::property_tree::ini_parser::read_ini(source, _ptree);
            }

            virtual void save() override {
                boost::property_tree::write_ini(_filename, _ptree);
            }

            template<typename T = std::string>
            T get(const char *key) const {
                try {
                    T value = _ptree.get<T>(key);
                    return (value);
                } catch (const std::exception &e) {
                    std::cerr << e.what() << std::endl;
                }
                return T();
            }
        };

        class JSONConfig : public Config {
        public:
            JSONConfig() = default;

            JSONConfig(std::string source) : Config(source) {
                boost::property_tree::json_parser::read_json(source, _ptree);
            }

            virtual void save() override {
                boost::property_tree::write_json(_filename, _ptree);
            }

            template<typename T>
            T get(const char *key) const {
                try {
                    T value = _ptree.get<T>(key);
                    return (value);
                } catch (const std::exception &e) {
                    std::cerr << e.what() << std::endl;
                }
                return T();
            }

            template<typename T>
            std::vector<T> getVector(const char *key) const {
                std::vector<T> data;

                try {
                    std::for_each(
                            _ptree.get_child(key).begin(),
                            _ptree.get_child(key).end(), [&data](const boost::property_tree::ptree::value_type &v) {
                                assert(v.first.empty());
                                data.push_back(v.second.get_value<T>());
                            });
                } catch (const boost::property_tree::ptree_bad_path &e) {
                    std::cerr << e.what() << std::endl;
                    return std::vector<T>();
                }
                return data;
            }

            template<typename T>
            std::vector<T> getMatrix(const char *key) const {
                std::vector<T> ret;

                try {
                    for (const auto &row : _ptree.get_child(key)) {
                        for (const auto &cell : row.second) {
                            ret.push_back(cell.second.get_value<T>());
                        }
                    }
                } catch (const boost::property_tree::ptree_bad_path &e) {
                    std::cerr << e.what() << std::endl;
                }
                return ret;
            }

            template<typename T>
            void writeMatrix(const char *key, const std::vector<T> data, int size = 4, bool write = false) {
                boost::property_tree::ptree matrix;
                int i = 0;
                std::vector<T> row;

                std::for_each(data.begin(), data.end(), [&size, &i, &matrix, &row](const T &value) {
                    row.push_back(value);
                    ++i;
                    if (i == size) {
                        matrix.push_back(std::make_pair("", row));
                        i = 0;
                    }
                });
                _ptree.get_child(key).push_back(std::make_pair("", matrix));
                if (write)
                    save();
            }

            template <typename T>
            void appendValues(const char *key, const std::vector<T> data, bool write = false) {
                boost::property_tree::ptree array, element;

                try {
                    array = _ptree.get_child(key);
                } catch (const boost::property_tree::ptree_bad_path &e) {
                    std::cerr << e.what() << std::endl;
                }
                for (const auto &it : data)
                    array.put("", it);
                _ptree.push_back(std::make_pair(key, array));
                if (write)
                    save();
            }

            template<typename T>
            void appendValue(const char *key, const T data, bool write = false) {
                appendValues<T>(key, {data}, write);
            }
        };
    }
}

#endif //KIWIENGINE_CONFIG_H
