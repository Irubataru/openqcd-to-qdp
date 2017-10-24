
/*
 * Created: 24-10-2017
 * Modified: Tue 24 Oct 2017 14:32:22 BST
 * Author: Jonas R. Glesaaen (jonas@glesaaen.com)
 */

#include "qdp_archive.hpp"

namespace fastsum {

namespace {

void fill_xml_header(QDP::XMLWriter &header)
{
  QDP::push(header, "HMC");
  QDP::push(header, "ProgramInfo");
  QDP::push(header, "Setgeom");

  QDP::write(header, "latt_size", QDP::Layout::lattSize());
  QDP::write(header, "logical_size", QDP::Layout::logicalSize());
  QDP::write(header, "subgrid_size", QDP::Layout::subgridLattSize());
  QDP::write(header, "total_volume", QDP::Layout::vol());
  QDP::write(header, "subgrid_volume", QDP::Layout::sitesOnNode());

  QDP::pop(header);
  QDP::pop(header);
  QDP::pop(header);
}
}

void write_qdp_gauge_field(QDP_Gauge_Field &gauge_field, std::string filename)
{
  QDP::XMLBufferWriter header{};
  fill_xml_header(header);

  QDP::QDPFileWriter lime_writer{header, filename, QDP::QDPIO_SINGLEFILE,
                                 QDP::QDPIO_SERIAL, QDP::QDPIO_OPEN};

  if (lime_writer.bad())
    throw std::runtime_error{"Error in outfile " + filename};

  QDP::XMLBufferWriter xml_record{};

  // Push an empty Params tag
  QDP::push(xml_record, "Params");
  QDP::pop(xml_record);

  QDP::write(lime_writer, xml_record, gauge_field);
  QDP::close(lime_writer);
}

} // namespace fastsum
