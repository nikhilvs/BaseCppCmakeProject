/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: osboxes
 *
 * Created on 08 June 2017, 12:18
 */

#include <cstdlib>
#include "main.h"
#include <iostream>
#include <boost/algorithm/string.hpp>

void print_version();



void print_version(){
 
    std::cout<<"Version :"<<VERSION_MAJOR<<"."<<VERSION_MINOR<<"."<<VERSION_PATCH<<std::endl;
}


void initLogger(){
    std::vector<spdlog::sink_ptr> sinks;
    //enable logger in async mode with queue size
    spdlog::set_async_mode(8192);
    sinks.push_back(std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>());
    
    //toggles file logger
#ifdef FILE_LOGGER
    //check file exist or create it
    if(!Common::fexists(LOGGER_FILE_PATH)){
        std::cout<<"file not exists"<<std::endl;
        std::vector<std::string> strs;
        boost::split(strs,LOGGER_FILE_PATH,boost::is_any_of("/"));
        strs.pop_back();
        std::string path="";
        for(auto &s:strs){
            path.append(s).append("/");
        }
        Common::dcreate(path);
        Common::fcreate(LOGGER_FILE_PATH);
    }
    sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(LOGGER_FILE_PATH,23, 59));
 #endif   
    
    auto combined_logger = std::make_shared<spdlog::logger>(loggerName, begin(sinks), end(sinks));
    combined_logger->set_level(spdlog::level::info);
    spdlog::register_logger(combined_logger);
    combined_logger->info("Hello spd");
    
}
void initSystem(){
    
    //enable logger 
    auto logger = spdlog::get(loggerName);
    logger->info("System Initiated ...");
    logger->debug("System Initiated ...");
    logger->error("System Initiated ...");
    
}

void cleanup(){
    spdlog::drop_all();
}


/*
 * 
 */
int main(int argc, char** argv) {

    print_version();
    initLogger();
    std::cout<<"Hello Hubble"<<std::endl;
    
    initSystem();
    cleanup();
    return 0;
}

