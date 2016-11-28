//
// Created by Raphaël Dantzer on 23/11/16.
//

#include "VirtualFilesystem.h"
#include <boost/range/iterator_range.hpp>
#include <iostream>
#include <unordered_map>

namespace fs = boost::filesystem;

Kiwi::Core::Filesystem::VirtualFilesystem::VirtualFilesystem() {
    _root = fs::current_path();
    _projectRoot = fs::current_path();
}

bool
Kiwi::Core::Filesystem::VirtualFilesystem::bind(std::string wd) {
    auto path = fs::path(wd);
    auto root = _root.append(wd);

    std::cout << root.c_str() << std::endl;
    if (fs::exists(root)) {
        if (fs::is_directory(root))
            _root = root;
        else
            return false;
    } else {
        return false;
    }
    return true;
}

std::string
Kiwi::Core::Filesystem::VirtualFilesystem::load(const char *filename) const {
    return fileRead(filename);
}

std::unordered_map<std::string, std::string>
Kiwi::Core::Filesystem::VirtualFilesystem::loadMultiplesFromDirectory(const char *directory,
                                                                      std::vector<std::string> filenames) const {
    std::unordered_map<std::string, std::string> sources;
    fs::path cwd = _root;
    cwd.append(directory);

    for (fs::directory_iterator it(cwd); it != fs::directory_iterator(); ++it) {
        fs::path path = it->path();
        if (fs::is_regular_file(path)) //double check because IO may fail anyway
            sources.emplace(std::pair<std::string, std::string>(path.filename().string(), fileRead(path.c_str())));
        else
            std::cerr << "Unable to open file: " << path.c_str() << std::endl; //todo remove
    }
    return sources;
}


std::vector<std::string>
Kiwi::Core::Filesystem::VirtualFilesystem::loadAllFromCurrentDirectory(void) const {
    std::vector<std::string> sources;
    fs::path cwd = _root;

    for (fs::directory_iterator it(cwd); it != fs::directory_iterator(); ++it) {
        fs::path path = it->path();
        if (fs::is_regular_file(path)) //double check because IO may fail anyway
            sources.push_back(fileRead(path.c_str()));
        else
            std::cerr << "Unable to open file: " << path.c_str() << std::endl; //todo remove
    }
    return sources;
}


std::vector<std::string>
Kiwi::Core::Filesystem::VirtualFilesystem::loadAllFromDirectory(const char *directory) const {
    std::vector<std::string> sources;
    fs::path cwd = _root;

    cwd = cwd.append(directory);
    for (auto &file : boost::make_iterator_range(fs::directory_iterator(cwd), {})) {
        std::cout << file.path().c_str() << std::endl;
        sources.push_back(fileRead(file.path().c_str()));
    }
    return sources;
}


std::string
Kiwi::Core::Filesystem::VirtualFilesystem::fileRead(const char *filename) const {
    std::ifstream f(filename);
    std::string str;

    if (!f.is_open())
        throw std::runtime_error("Unable to open file");
    f.seekg(0, std::ios::end);
    str.reserve(static_cast<unsigned long>(f.tellg()));
    f.seekg(0, std::ios::beg);
    str.assign(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>());
    f.close();
    return str;
}


