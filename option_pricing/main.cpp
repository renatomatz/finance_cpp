#include <boost/program_options.hpp>
#include"option_pricing.cpp"

namespace po = boost::program_options;

int main(int argc, char* argv[]) 
{
    try {

        po::options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce this help menu")
            ("S", po::value<double>(), "present stock price")
            ("U", po::value<double>(), "stock up change")
            ("D", po::value<double>(), "stock down change")
            ("delta_t", po::value<double>(), "time step change in fraction of a year")
            ("R", po::value<double>(), "interest rate")
            ("K", po::value<double>(), "strike price")
            ("style", po::value<string>(), "option kind, either call or put")
            ("kind", po::value<string>(), "option style, either amercian or european")
        ;

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            cout << desc << "\n";
            return 0;
        }

        OptionPricing option();

        if (vm.count("S")) {
            option.setS(vm["S"].as<double>());
        }
        else {
            cerr << "Parameter 'S' must be specified\n";
            return 1;
        }

        if (vm.count("U")) {
            option.setU(vm["U"].as<double>());
        }
        else {
            cerr << "Parameter 'U' must be specified\n";
            return 1;
        }

        if (vm.count("D")) {
            option.setD(vm["D"].as<double>());
        }
        else {
            cerr << "Parameter 'D' must be specified\n";
            return 1;
        }

        if (vm.count("delta_t")) {
            option.setdelta_t(vm["delta_t"].as<double>());
        }
        else {
            cerr << "Parameter 'delta_t' must be specified\n";
            return 1;
        }

        if (vm.count("R")) {
            option.setR(vm["R"].as<double>());
        }
        else {
            cerr << "Parameter 'R' must be specified\n";
            return 1;
        }

        if (vm.count("R")) {
            option.setR(vm["R"].as<double>());
        }
        else {
            cerr << "Parameter 'R' must be specified\n";
            return 1;
        }

        OptionKind kind;
        OptionStyle style;

        if (vm.count("kind")) {
            kind = OptionKindStringMap[vm["kind"].as<string>()];
        }
        else {
            cerr << "Parameter 'kind' must be specified\n";
            return 1;
        }

        if (vm.count("style")) {
            style = OptionStyleMap[vm["style"].as<string>()];
        }
        else {
            cerr << "Parameter 'style' must be specified\n";
            return 1;
        }

        option.PriceOption(kind, style, VERBOSE);

    }
    catch(exception& e) {
        cerr << "error: " << e.what() << "\n";
        return 1;
    }
    catch(...) {
        cerr << "Unknown exceeption\n";
    }

    return 0;
}
