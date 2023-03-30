#include "motherboard_strategy.hpp"

#include "../os/os.h"
#include "../base/logger.h"
#include "../base/string_utils.h"


#include <array>
#include <cstring>

license::hw_identifier::MotherboardStrategy::MotherboardStrategy()
{

}

license::hw_identifier::MotherboardStrategy::~MotherboardStrategy()
{

}

LCC_API_HW_IDENTIFICATION_STRATEGY license::hw_identifier::MotherboardStrategy::identification_strategy() const
{
	return LCC_API_HW_IDENTIFICATION_STRATEGY::STRATEGY_MOTHERBOARD;
}

std::vector<license::hw_identifier::HwIdentifier> license::hw_identifier::MotherboardStrategy::alternative_ids() const
{
	using namespace std;

	MotherboardInfo mbInfo;
	FUNCTION_RETURN result = getMotherboardInfo(mbInfo);
#ifndef NDEBUG
	LOG_DEBUG("Motherboard product_uuid: \"%s\", product_serial: \"%s\", board_serial: \"%s\"",
			  mbInfo.product_uuid.c_str(), mbInfo.product_serial.c_str(), mbInfo.board_serial.c_str());
#endif

	vector<HwIdentifier> pc_ids;
	if (result == FUNC_RET_OK) {
		const vector<string> ids{
			mbInfo.product_uuid,
			mbInfo.product_serial,
			mbInfo.board_serial,
		};

		for (const string &id: ids) {
			if (!id.empty()) {
				HwIdentifier pc_id;
				pc_id.set_identification_strategy(identification_strategy());
				pc_id.set_data(id.data(), id.size());
				pc_ids.push_back(pc_id);
			}
		}
	}

	return pc_ids;
}
