/*
 * os_disk_strategy.hpp
 *
 *  Created on: Mar 30, 2023
 *      Author: frostasm
 */

#ifndef SRC_LIBRARY_PC_IDENTIFIER_MOTHERBOARD_STRATEGY_HPP_
#define SRC_LIBRARY_PC_IDENTIFIER_MOTHERBOARD_STRATEGY_HPP_

#include "identification_strategy.hpp"

namespace license {
namespace hw_identifier {

// operating system rootfs block device (disk) serial number
class MotherboardStrategy : public IdentificationStrategy {
public:
	MotherboardStrategy();
	virtual ~MotherboardStrategy();
	virtual LCC_API_HW_IDENTIFICATION_STRATEGY identification_strategy() const;
	virtual std::vector<HwIdentifier> alternative_ids() const;
};

}  // namespace hw_identifier
} /* namespace license */

#endif /* SRC_LIBRARY_PC_IDENTIFIER_MOTHERBOARD_STRATEGY_HPP_ */
