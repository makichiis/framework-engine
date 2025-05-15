#include <cli/get_args.hpp>

#include <filesystem>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    FCLIArguments args = get_args(argc, argv);
    std::vector<std::string> available_samples;

    namespace fs = std::filesystem; 
    std::string samples_dir = "./samples/";
    if (fs::exists(samples_dir) && fs::is_directory(samples_dir)) {
        for (const auto& entry : fs::directory_iterator(samples_dir)) {
            std::cout << entry.path().string() << '\n';
            if (entry.is_directory()) {
                available_samples.push_back(entry.path().filename().string());
            }
        }
    }

    if (args.list_samples) {
        std::cout << "Available samples:\n";
        for (auto&& p : available_samples) {
            std::cout << p << '\n';
        }

        return 0;
    }

    std::filesystem::path directory_target = (std::filesystem::path(args.location));
    std::filesystem::path sample_source = std::filesystem::path("./samples");

    if (!args.sample_name.empty()) {
        if (std::find(available_samples.begin(), available_samples.end(), args.sample_name) == available_samples.end()) {
            std::cerr << "Invalid sample. Available samples:\n";
            for (auto&& sample : available_samples)
                std::cout << sample << '\n';

            return 1;
        }

        directory_target = args.project_name;
        sample_source /= args.sample_name;
    } else {
        sample_source /= "empty";
    }

    namespace fs = std::filesystem;

    fs::create_directories(directory_target);

    std::cout << "Scaffolding project...\n";

    for (const auto& entry : fs::recursive_directory_iterator(sample_source)) {
        std::cout << entry.path().filename().string() << '\n';
        const auto& path = entry.path();
        auto relative_path = fs::relative(path, sample_source);
        auto target_path = directory_target / relative_path;

        if (entry.is_directory()) {
            fs::create_directories(target_path);
        } else if (entry.is_regular_file()) {
            fs::copy_file(path, target_path, fs::copy_options::overwrite_existing);
        }

        fs::path scaffold_path = "./scaffold";
        if (!fs::exists(scaffold_path) || !fs::is_directory(scaffold_path)) {
            std::cerr << "Scaffold directory not found.\n";
            return 1;
        }
        for (const auto& scaffold_entry : fs::recursive_directory_iterator(scaffold_path)) {
            auto scaffold_rel = fs::relative(scaffold_entry.path(), scaffold_path);
            auto scaffold_target = directory_target / scaffold_rel;
            if (scaffold_entry.is_directory()) {
            fs::create_directories(scaffold_target);
            } else if (scaffold_entry.is_regular_file()) {
            fs::copy_file(scaffold_entry.path(), scaffold_target, fs::copy_options::overwrite_existing);
            }
        }

        std::cout << "Assembling framework core...\n";

        fs::path core_path = "../framework-core";
        if (!fs::exists(core_path)) {
            std::cerr << "Error: ../framework-core not found. Aborting.\n";
            return 1;
        } else {
            fs::path target_core = directory_target / "lib" / "framework-core";
            fs::create_directories(target_core);
            for (const auto& core_entry : fs::recursive_directory_iterator(core_path)) {
                auto core_rel = fs::relative(core_entry.path(), core_path);
                auto core_target = target_core / core_rel;
                if (core_entry.is_directory()) {
                    fs::create_directories(core_target);
                } else if (core_entry.is_regular_file()) {
                    fs::copy_file(core_entry.path(), core_target, fs::copy_options::overwrite_existing);
                }
            }
        }

        std::cout << "Project built to " << directory_target.filename().string() << '\n';
    }
    
    return 0;
}
