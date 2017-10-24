/*
 * Created: 24-10-2017
 * Author: Jonas R. Glesaaen (jonas@glesaaen.com)
 */

// Needed to define all OpenQCD global arrays
#define MAIN_PROGRAM

#include "openqcd_to_qdp.hpp"
#include <iomanip>

using namespace fastsum;

const std::string xml_geometry_tag = "/HMC/ProgramInfo/Setgeom";
const std::string xml_lattice_size_tag = "latt_size";

int main(int argc, char **argv)
{
  QDP_Instance_Wrapper qdp_instance{argc, argv};

  if (QDP_Instance_Wrapper::MPI::comm_size() > 1 or NPROC != 1) {
    std::cerr << "Error: This program only works in serial" << std::endl;
    return 1;
  }

  Program_Parameters params;

  try {
    params = parse_input_arguments(argc, argv);
  } catch (std::exception &err) {
    std::cerr << "Error: " << err.what() << "\n" << std::endl;
    print_help_message();
    return 1;
  }

  OpenQCD::Initialise();
  init_qdp_lattice_geometry();

  try {
    import_openqcd_config(params.input_file);
  } catch (std::exception &err) {
    std::cerr << err.what() << std::endl;
    return 1;
  }

  OpenQCD_Gauge_Field openqcd_gauge_field{udfld()};

  std::cout << "OpenQCD config imported, average plaquette: "
            << std::setprecision(16) << average_plaquette(openqcd_gauge_field)
            << std::endl;

  QDP_Gauge_Field qdp_gauge_field(4);

  try {
    copy(openqcd_gauge_field, qdp_gauge_field);
    write_qdp_gauge_field(qdp_gauge_field, params.output_file);
  } catch (std::exception &err) {
    std::cerr << err.what() << std::endl;
    return 1;
  }

  std::cout << "QDP config exported, average plaquette:     "
            << std::setprecision(16) << average_plaquette(qdp_gauge_field)
            << "\n";

  std::cout << "Converted: " << params.input_file << " -> " << params.output_file << std::endl;
}

namespace fastsum {

void init_qdp_lattice_geometry()
{
  QDP::multi1d<int> nrow(4);
  nrow[0] = NPROC1 * L1;
  nrow[1] = NPROC2 * L2;
  nrow[2] = NPROC3 * L3;
  nrow[3] = NPROC0 * L0;

  QDP::Layout::setLattSize(nrow);
  QDP::Layout::create();
}

void print_help_message()
{
  std::cout << "Usage:\n"
            << "openqcd_to_qdp [input_filename] [output_filename]" << std::endl;
}

Program_Parameters parse_input_arguments(int argc, char **argv)
{
  if (argc < 3)
    throw std::runtime_error{"Not enough arguments"};

  auto result = Program_Parameters{{argv[1]}, {argv[2]}};

  std::ifstream ifs{result.input_file};
  if (!ifs)
    throw std::runtime_error{"Cannot open \"" + result.input_file +
                             "\" for reading"};
  ifs.close();

  std::ofstream ofs{result.output_file};
  if (!ofs)
    throw std::runtime_error{"Cannot open \"" + result.output_file +
                             "\" for writing"};
  ofs.close();

  return result;
}

} // namespace fastsum
