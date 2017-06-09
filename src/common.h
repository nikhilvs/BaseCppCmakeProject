/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   common.h
 * Author: osboxes
 *
 * Created on 08 June 2017, 19:04
 */

#ifndef COMMON_H
#define COMMON_H

#include <sys/stat.h>
//#include <unistd.h>
#include <string>
#include <fstream>
#include <string>
#include <boost/filesystem.hpp>
#include "spdlog/spdlog.h"



namespace fs = boost::filesystem;
static std::string loggerName="common";
class Common {
    auto logger;
public:

    Common(){
        logger = spdlog::get(loggerName);
    }
   
    static bool fexists(const std::string& name) {
        std::ifstream infile(name);
        return infile.good();
    }

    static bool dcreate(const std::string& name) {
        return fs::create_directories(name);
    }

    static bool fcreate(const std::string& name) {
        std::ofstream outfile(name);
        return true;
    }
};


#endif /* COMMON_H */

