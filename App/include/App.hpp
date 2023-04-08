// Copyright(c) 2023 Klimova Mary

#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <span>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct DirectorInfo {
    std::string directorId;
    std::string directorName;
    std::vector<std::string> directorsTitles;
};

class App {
 public:
    static const int directorsInfoCheck(std::string nameBasicsFilename, std::string director, std::unique_ptr<DirectorInfo>& directorInfo);

    static int checkIfIsDirector(std::string titleCrewFilename, std::unique_ptr<DirectorInfo>& directorInfo);

    static int checkIfIsAdult(std::string titleBasicsFileame, std::unique_ptr<DirectorInfo>& directorInfo);

    static int checkRussianRegion(std::string titleAkasFilename, std::unique_ptr<DirectorInfo>& directorInfo);

    static int parseCmd(std::unordered_map<std::string, std::string>* cmdLineArguments, int argc, char** argv);

    static int Run(int argc, char** argv);
};
