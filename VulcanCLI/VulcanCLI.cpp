// VulcanCLI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <filesystem>
#include "../VulcanCore/Forge.h"
#include "lib/tabulate.hpp"

void exportFunction(std::filesystem::path& forgePath, uint64_t& uid, std::filesystem::path& binaryPath) {
    std::fstream fileStream(forgePath, std::ios::in | std::ios::binary);

    VulcanCore::Forge forge(fileStream);

    char* out;
    auto outLen = forge.Read(fileStream, uid, out);

    std::ofstream outStream(binaryPath, std::ios::binary);
    outStream.write(out, outLen);

    delete[] out;
}

void importFunction(std::filesystem::path& forgePath, uint64_t& uid, std::filesystem::path& binaryPath) {

}


template< typename T >
std::string int_to_hexString(T i)
{
    std::stringstream stream;
    stream << "0x"
        << std::setfill('0') << std::setw(sizeof(T) * 2)
        << std::hex << i;
    return stream.str();
}

std::string humanSize(uint64_t bytes) // stolen
{
    const char* suffix[] = { "B", "KB", "MB", "GB", "TB" };
    char length = sizeof(suffix) / sizeof(suffix[0]);

    int i = 0;
    double dblBytes = bytes;

    if (bytes > 1024) {
        for (i = 0; (bytes / 1024) > 0 && i < length - 1; i++, bytes /= 1024)
            dblBytes = bytes / 1024.0;
    }

    static char output[200];
    if (i == 0) {
        sprintf(output, "%d %s", (int)dblBytes, suffix[i]);
    }
    else {
        sprintf(output, "%.02lf %s", dblBytes, suffix[i]);
    }
    return std::string(output);
}
std::string formatMagic(ubiU64 magic) {
    // TODO: he he returns the magic otherwise use crc32 or something idk he he
    return int_to_hexString(magic);

}
void listFunction(std::filesystem::path& forgePath) {
    std::fstream fileStream(forgePath, std::ios::in | std::ios::binary);

    VulcanCore::Forge forge(fileStream);

    tabulate::Table entries_table;

    entries_table.add_row({"Name", "UID", "Magic", "Size"});
    entries_table[0].format()
        .padding_top(1)
        .padding_bottom(1);

    for (int i = 0; i < forge.Entries.size(); i++) {
        auto e = forge.Entries[i];
        auto em = forge.EntryMetaDatas[i];

        entries_table.add_row({em.Name, int_to_hexString(e.Uid), formatMagic(em.Type), humanSize(em.Size)});
    }

    entries_table.print(std::cout);
}

int main(int argc, char* argv[])
{
    if (argc < 3 || argc == 4 || argc > 5) {
        printf("Wrong amount of arguments has been provided.\nUsage:\n");
        printf("VulcanCLI.exe <Forge file path> export <uid> <output entry file>\n");
        printf("VulcanCLI.exe <Forge file path> import <uid> <input entry file>\n");
        printf("VulcanCLI.exe <Forge file path> list\n");

        return -1;
    }

    std::filesystem::path forgePath(argv[1]);
    if (!std::filesystem::exists(forgePath)) {
        printf("The following file does not exist:\n%s\n", argv[1]);

        return -1;
    }
    if (forgePath.extension() != ".forge") {
        printf("The following file is not a FORGE file:\n%s\n", argv[1]);

        return -1;
    }

    std::string action(argv[2]);
    if (action != "export" && action != "import" && action != "list") {
        printf("The following action is not valid: %s\n", action.c_str());

        return -1;
    }

    if (action == "export" || action == "import") {
        std::string uidString(argv[3]);
        uint64_t uid = std::stoll(uidString, nullptr, 0);

        std::filesystem::path binaryPath(argv[4]);


        if (action == "export") {
            exportFunction(forgePath, uid, binaryPath);
        }
        else if (action == "import") {
            importFunction(forgePath, uid, binaryPath);
        }
    }
    else if (action == "list") {
        listFunction(forgePath);
    }
    return 0;
}