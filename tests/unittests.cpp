// Copyright(c) 2023 Klimova Mary
#include <gtest/gtest.h>
#include "App.hpp"

TEST(parseCmdTest, CheckArgsSuccess) {
    std::unordered_map<std::string, std::string> arguments = {{"-nbasics", ""}, {"-tcrew", ""}, {"-tbasics", ""}, {"-takas", ""}, {"-dir", ""}};
    std::unordered_map<std::string, std::string> expected = {
        {"-nbasics", "namebasics"}, {"-tcrew", "titlecrew"}, {"-tbasics", "titlebasics"}, {"-takas", "titleakas"}, {"-dir", "Steven Spielberg"}};
    const int argc = 6;
    char** argv = new char*[argc];
    // сложность вижу, пока не знаю как исправить
    argv[0] = "progpath";
    argv[5] = "-nbasics=namebasics";
    argv[1] = "-dir=Steven_Spielberg";
    argv[2] = "-takas=titleakas";
    argv[3] = "-tcrew=titlecrew";
    argv[4] = "-tbasics=titlebasics";
    EXPECT_EQ(App::parseCmd(arguments, argc, argv), 0);
    for (int i = 0; i < argc; ++i) {
        delete[] argv[i];
    }
    delete[] argv;
}

TEST(parseCmdTest, CheckArgsFail) {
    std::unordered_map<std::string, std::string> arguments = {{"-nbasics", ""}, {"-tcrew", ""}, {"-tbasics", ""}, {"-takas", ""}, {"-dir", ""}};
    const int argc = 6;
    char** argv = new char*[argc];
    argv[0] = "progpath";
    argv[5] = "-nbasics=namebasics";
    argv[1] = "-dir=Steven_Spielberg";
    argv[2] = "-ta=titleakas";
    argv[3] = "-tcrew=titlecrew";
    argv[4] = "-tbs=titlebasics";
    EXPECT_EQ(App::parseCmd(arguments, argc, argv), 1);
    for (int i = 0; i < argc; ++i) {
        delete[] argv[i];
    }
    delete[] argv;
}

TEST(parseCmdTest, CheckArgsNumberFail) {
    std::unordered_map<std::string, std::string> arguments = {{"-nbasics", ""}, {"-tcrew", ""}, {"-tbasics", ""}, {"-takas", ""}, {"-dir", ""}};
    const int argc = 3;
    char** argv;
    EXPECT_EQ(App::parseCmd(arguments, argc, argv), 2);
}

TEST()