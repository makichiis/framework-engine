#include <cli/get_args.hpp>
#include <cli/clipp.h>

#include <iostream>
#include <cstdlib>

FCLIArguments get_args(int argc, char* argv[]) {
    std::string sample_name;
    std::string location;
    std::string project_name;
    bool list_samples = false;
    bool empty = false;

    auto cli = (
        clipp::option("--sample", "-s") & clipp::opt_value("sample name", sample_name),
        clipp::option("--location", "-p") & clipp::opt_value("location", location),
        clipp::option("--name", "-n") & clipp::opt_value("project name", project_name),
        clipp::option("--list-samples", "-l").set(list_samples),
        clipp::option("--empty", "-e").set(empty)
    );

    if (!clipp::parse(argc, argv, cli)) {
        std::cout << "Usage:\n"
                  << "  --sample - what sample to use\n"
                  << "  --location <path> - optional, defaults to <local>/<project name>\n"
                  << "  --name <string> - project name, defaults to framework_project\n"
                  << "  --list-samples - show available samples.\n"
                  << "  --empty - Initialize empty project.\n";

        std::abort();
    }

    FCLIArguments args = { sample_name, location, project_name, list_samples, empty };

    if (args.project_name.empty())
        args.project_name = "framework_project";

    if (args.location.empty()) 
        args.location = "./" + args.project_name;

    return std::move(args);
}
