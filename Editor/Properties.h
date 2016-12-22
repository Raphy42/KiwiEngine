//
// Created by Raphael DANTZER on 12/17/16.
//

#ifndef KIWIENGINE_PROPERTIES_H
#define KIWIENGINE_PROPERTIES_H

#include <boost/serialization/vector.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/unordered_map.hpp>

namespace Kiwi {
    namespace Editor {
        class Properties {
        public:
            Properties() = default;
            Properties(std::vector<std::string> lastFiles, std::string current, std::unordered_map<std::string, bool> windows) :
                    _lastFiles(lastFiles),
                    _currentFile(current),
                    _windowState(windows)
            {
            }

            const std::vector<std::string> &getLastFiles() const {
                return _lastFiles;
            }

            void setLastFiles(const std::vector<std::string> &lastFiles) {
                _lastFiles = lastFiles;
            }

            const std::string &getCurrentFile() const {
                return _currentFile;
            }

            void setCurrentFile(const std::string &currentFile) {
                _currentFile = currentFile;
            }

            void addLastFile(std::string filename) {
                _lastFiles.push_back(filename);
            }

            bool getState(std::string window) {
                if (_windowState.size() == 0) {
                    _windowState["tools"] = false;
                    _windowState["properties"] = false;
                }
                return _windowState.at(window);
            }

            void setState(std::string window, bool state) {
                _windowState[window] = state;
            }

            void toggleState(std::string string) {
                _windowState[string] = !_windowState[string];
            }

        private:
            friend class boost::serialization::access;

            template<class Archive>
            void serialize(Archive &ar, const unsigned int version) {
                ar & boost::serialization::make_nvp("last_files", _lastFiles); //not using the macro here
                ar & boost::serialization::make_nvp("current_file", _currentFile); //i dont want _tags
                ar & boost::serialization::make_nvp("windows", _windowState);
            }

            std::vector<std::string>                    _lastFiles;
            std::string                                 _currentFile;
            std::unordered_map<std::string, bool>       _windowState;
        };
    }
}


#endif //KIWIENGINE_PROPERTIES_H
