#include "os_disk_strategy.hpp"

#include "../os/os.h"

#include <array>
#include <cstring>


license::hw_identifier::OsDiskStrategy::OsDiskStrategy()
{

}

license::hw_identifier::OsDiskStrategy::~OsDiskStrategy()
{

}

LCC_API_HW_IDENTIFICATION_STRATEGY license::hw_identifier::OsDiskStrategy::identification_strategy() const
{
	return LCC_API_HW_IDENTIFICATION_STRATEGY::STRATEGY_OS_DISK;
}

std::vector<license::hw_identifier::HwIdentifier> license::hw_identifier::OsDiskStrategy::alternative_ids() const
{
	DiskInfo disk_info;
	FUNCTION_RETURN result = getOsDiskInfo(disk_info);

	if (result == FUNC_RET_OK && disk_info.sn_initialized) {
		HwIdentifier pc_id;
		pc_id.set_identification_strategy(identification_strategy());
		pc_id.set_data(disk_info.disk_serial.data(), disk_info.disk_serial.size());
		return {pc_id};
	}

	return {};
}
