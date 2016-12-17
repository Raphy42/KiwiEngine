//
// Created by Raphael DANTZER on 12/17/16.
//

#ifndef KIWIENGINE_PROPERTIES_H
#define KIWIENGINE_PROPERTIES_H

#include <boost/serialization/vector.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/string.hpp>

namespace Kiwi {
    namespace Editor {
        class Properties {
        public:
            Properties() = default;
            Properties(std::vector<std::string> lastFiles, std::string current) :
                    _lastFiles(lastFiles),
                    _currentFile(current)
            {}

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

        private:
            friend class boost::serialization::access;

            template<class Archive>
            void serialize(Archive &ar, const unsigned int version) {
                ar & boost::serialization::make_nvp("last_files", _lastFiles); //not using the macro here
                ar & boost::serialization::make_nvp("current_file", _currentFile); //i dont want _tags
            }

            std::vector<std::string>        _lastFiles;
            std::string                     _currentFile;
        };
    }
}


#endif //KIWIENGINE_PROPERTIES_H
