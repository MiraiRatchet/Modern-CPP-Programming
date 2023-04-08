// Copyright(c) 2023 Klimova Mary
#include "App.hpp"

namespace {
constexpr int neededArgumentsNumber = 6;
bool rightNumberOfCmdLineArgs(int argc) {
    if (argc != neededArgumentsNumber) {
        std::cout << "Wrong number of input arguments" << std::endl;
        return false;
    }
    return true;
}
}  // namespace

int App::Run(int argc, char** argv) {
    std::unordered_map<std::string, std::string> arguments = {{"-nbasics", ""}, {"-tcrew", ""}, {"-tbasics", ""}, {"-takas", ""}, {"-dir", ""}};
    // не очень понимаю, как можно избавиться от хардкода в данном месте
    if (parseCmd(arguments, argc, argv)) {
        return 2;
    }
    DirectorInfo directorInfo;
    std::cout << "Searching for the director..." << std::endl;
    if (App::directorsInfoCheck(arguments["-nbasics"], arguments["-dir"], directorInfo)) {
        return 3;
    }
    std::cout << "Director found! Checking titles..." << std::endl;

    checkIfIsDirector(arguments["-tcrew"], directorInfo);

    if (directorInfo.directorsTitles.size() == 0) {
        std::cout << "No known titles for this director in IMDB" << std::endl;
        return 4;
    }
    std::cout << "This director has " << directorInfo.directorsTitles.size() << " titles. Checking..." << std::endl;

    std::cout << "Filtering adult movies and other types of media..." << std::endl;
    checkIfIsAdult(arguments["-tbasics"], directorInfo);
    std::cout << "Found " << directorInfo.directorsTitles.size() << " inique titles." << std::endl;

    std::cout << "Checking if there are russian movies..." << std::endl;

    checkRussianRegion(arguments["-takas"], directorInfo);
    std::cout << std::endl;
    return 0;
}

const int App::directorsInfoCheck(std::string nameBasicsFilename, std::string director, DirectorInfo& directorInfo) {
    auto IMDBNameBasicsStream = std::make_unique<std::ifstream>(nameBasicsFilename);
    std::string line {""};
    getline(*IMDBNameBasicsStream, line);
    directorInfo.directorName = "";
    while (director != directorInfo.directorName && !(*IMDBNameBasicsStream).eof()) {
        getline(*IMDBNameBasicsStream, directorInfo.directorId, '\t');
        getline(*IMDBNameBasicsStream, directorInfo.directorName, '\t');
        getline(*IMDBNameBasicsStream, line);
    }
    if (directorInfo.directorName != director) {
        std::cout << "Person not found in IMDB database" << std::endl;
        return 1;
    }
    return 0;
}

int App::checkIfIsDirector(std::string titleCrewFilename, DirectorInfo& directorInfo) {
    auto IMDBTitleCrewStream = std::make_unique<std::ifstream>(titleCrewFilename);
    if (!(*IMDBTitleCrewStream).is_open()) {
        return 1;
    }
    std::string tline {""}, dline {""};
    getline(*IMDBTitleCrewStream, tline);
    while (!(*IMDBTitleCrewStream).eof()) {
        getline(*IMDBTitleCrewStream, tline, '\t');
        getline(*IMDBTitleCrewStream, dline, '\t');
        if (dline == directorInfo.directorId) {
            directorInfo.directorsTitles.push_back(tline);
        }
        getline(*IMDBTitleCrewStream, tline);
    }
    return 0;
}

int App::checkIfIsAdult(std::string titleBasicsFilename, DirectorInfo& directorInfo) {
    auto IMDBTitleBasicsStream = std::make_unique<std::ifstream>(titleBasicsFilename);
    if (!(*IMDBTitleBasicsStream).is_open()) {
        return 1;
    }
    std::string line {""};
    int i {0};
    getline(*IMDBTitleBasicsStream.get(), line);
    while (i < directorInfo.directorsTitles.size() && !(*IMDBTitleBasicsStream).eof()) {
        getline(*IMDBTitleBasicsStream, line, '\t');
        auto it = std::find(directorInfo.directorsTitles.begin(), directorInfo.directorsTitles.end(), line);
        if (it != directorInfo.directorsTitles.end()) {
            std::string titleType = "";
            bool isAdult = false;
            getline(*IMDBTitleBasicsStream, titleType, '\t');
            getline(*IMDBTitleBasicsStream, line, '\t');
            getline(*IMDBTitleBasicsStream, line, '\t');
            *IMDBTitleBasicsStream >> isAdult;
            if (titleType != "movie" || isAdult) {
                directorInfo.directorsTitles.erase(it);
                getline(*IMDBTitleBasicsStream, line);
                continue;
            }
            ++i;
        }
        getline(*IMDBTitleBasicsStream, line);
    }
    return 0;
}

int App::checkRussianRegion(std::string titleAkasFilename, DirectorInfo& directorInfo) {
    auto IMDBTitleAkasStream = std::make_unique<std::ifstream>(titleAkasFilename);
    if (!(*IMDBTitleAkasStream).is_open()) {
        return 1;
    }
    int i {0};
    std::string line {""};
    getline(*IMDBTitleAkasStream, line);
    getline(*IMDBTitleAkasStream, line, '\t');
    while (i < directorInfo.directorsTitles.size() && !(*IMDBTitleAkasStream).eof()) {
        auto it = std::find(directorInfo.directorsTitles.begin(), directorInfo.directorsTitles.end(), line);
        if (it != directorInfo.directorsTitles.end()) {
            while (line == *it) {
                std::string movieTitle;
                getline(*IMDBTitleAkasStream, line, '\t');
                getline(*IMDBTitleAkasStream, movieTitle, '\t');
                getline(*IMDBTitleAkasStream, line, '\t');
                if (line == "RU" || line == "SUHH") {
                    std::cout << movieTitle << std::endl;
                }
                getline(*IMDBTitleAkasStream, line);
                getline(*IMDBTitleAkasStream, line, '\t');
            }
            ++i;
            continue;
        }
        getline(*IMDBTitleAkasStream, line);
        getline(*IMDBTitleAkasStream, line, '\t');
    }
    return 0;
}

int App::parseCmd(std::unordered_map<std::string, std::string>& arguments, int argc, char** argv) {
    if (!rightNumberOfCmdLineArgs(argc)) {
        return 2;
    }
    auto args = std::span(argv, static_cast<size_t>(argc));
    std::string prefix {""};
    std::string value {""};
    for (int i = 1; i < argc; ++i) {
        std::stringstream arg(args[i]);
        getline(arg, prefix, '=');
        if (auto search = arguments.find(prefix); search != arguments.end()) {
            getline(arg, value);
            arguments[prefix] = value;
            continue;
        }
        std::cout << "Wrong input arguments" << std::endl;
        return 1;
    }
    auto i = arguments["-dir"].find("_");
    while (i != std::string::npos) {
        arguments["-dir"].replace(i, 1, " ");
        i = arguments["-dir"].find("_");
    }
    return 0;
}
