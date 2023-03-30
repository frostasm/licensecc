/*
 * default_strategy.hpp
 *
 *  Created on: Jan 2, 2020
 *      Author: devel
 */

#ifndef SRC_LIBRARY_PC_IDENTIFIER_DEFAULT_STRATEGY_HPP_
#define SRC_LIBRARY_PC_IDENTIFIER_DEFAULT_STRATEGY_HPP_
#include "identification_strategy.hpp"

namespace license {
namespace hw_identifier {

class DefaultStrategy : public IdentificationStrategy {
public:
	static std::vector<LCC_API_HW_IDENTIFICATION_STRATEGY> available_strategies();

	DefaultStrategy(const std::vector<LCC_API_HW_IDENTIFICATION_STRATEGY> &strategies = available_strategies());
	virtual ~DefaultStrategy();
	virtual LCC_API_HW_IDENTIFICATION_STRATEGY identification_strategy() const;
	virtual FUNCTION_RETURN generate_pc_id(HwIdentifier &pc_id) const;
	virtual std::vector<HwIdentifier> alternative_ids() const;
	virtual LCC_EVENT_TYPE validate_identifier(const HwIdentifier &identifier) const;
private:
	std::vector<LCC_API_HW_IDENTIFICATION_STRATEGY> strategies;
};
}  // namespace hw_identifier
} /* namespace license */

#endif /* SRC_LIBRARY_PC_IDENTIFIER_DEFAULT_STRATEGY_HPP_ */
