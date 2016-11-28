//
// Created by Raphaël Dantzer on 23/11/16.
//

#ifndef KIWIENGINE_VIRTUALFILESYSTEM_H
#define KIWIENGINE_VIRTUALFILESYSTEM_H

#include <memory>
#include <fstream>
#include <boost/filesystem.hpp>
#include <unordered_map>

namespace Kiwi {
    namespace Core {
        namespace Filesystem {
            class VirtualFilesystem {
            public:
                VirtualFilesystem();

                bool bind(std::string wd);

                std::string load(const char *filename) const;

                std::unordered_map<std::string, std::string>
                loadMultiplesFromDirectory(const char *directory, std::vector<std::string> filenames) const;

                std::vector<std::string> loadAllFromCurrentDirectory(void) const;

                std::vector<std::string> loadAllFromDirectory(const char *directory) const;

            private:
                std::string fileRead(const char *filename) const;

                boost::filesystem::path _root;
                boost::filesystem::path _projectRoot;
            };
        }
    }
}

#endif //KIWIENGINE_VIRTUALFILESYSTEM_H
