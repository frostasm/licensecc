/*
 * default_strategy.cpp
 *
 *  Created on: Jan 1, 2020
 *      Author: devel
 */

#include <vector>
#include "../os/execution_environment.hpp"
#include "default_strategy.hpp"

using namespace std;
namespace license {
namespace hw_identifier {

std::vector<LCC_API_HW_IDENTIFICATION_STRATEGY> DefaultStrategy::available_strategies() {
	const os::ExecutionEnvironment exec;
	LCC_API_VIRTUALIZATION_SUMMARY virtualization = exec.virtualization();
	vector<LCC_API_HW_IDENTIFICATION_STRATEGY> strategies_to_try;
	if (virtualization == LCC_API_VIRTUALIZATION_SUMMARY::CONTAINER) {
		if (exec.is_docker()) {
			strategies_to_try = LCC_DOCKER_STRATEGIES;
		} else {
			strategies_to_try = LCC_LXC_STRATEGIES;
		}
	} else if (virtualization == LCC_API_VIRTUALIZATION_SUMMARY::VM) {
		if (exec.is_cloud()) {
			strategies_to_try = LCC_CLOUD_STRATEGIES;
		} else {
			strategies_to_try = LCC_VM_STRATEGIES;
		}
	} else {
		strategies_to_try = LCC_BARE_TO_METAL_STRATEGIES;
	}
	return strategies_to_try;
}

DefaultStrategy::DefaultStrategy(const std::vector<LCC_API_HW_IDENTIFICATION_STRATEGY> &strategies)
	: strategies(strategies.empty() ? available_strategies() : strategies)
{
}

DefaultStrategy::~DefaultStrategy() {}

LCC_API_HW_IDENTIFICATION_STRATEGY DefaultStrategy::identification_strategy() const { return STRATEGY_DEFAULT; }

FUNCTION_RETURN DefaultStrategy::generate_pc_id(HwIdentifier& pc_id) const {
	FUNCTION_RETURN ret = FUNC_RET_NOT_AVAIL;
	for (auto it : strategies) {
		LCC_API_HW_IDENTIFICATION_STRATEGY strat_to_try = it;
		unique_ptr<IdentificationStrategy> strategy_ptr = IdentificationStrategy::get_strategy(strat_to_try);
		ret = strategy_ptr->generate_pc_id(pc_id);
		if (ret == FUNC_RET_OK) {
			break;
		}
	}
	return ret;
}

std::vector<HwIdentifier> DefaultStrategy::alternative_ids() const {
	vector<HwIdentifier> identifiers;
	for (auto it : strategies) {
		LCC_API_HW_IDENTIFICATION_STRATEGY strat_to_try = it;
		unique_ptr<IdentificationStrategy> strategy_ptr = IdentificationStrategy::get_strategy(strat_to_try);
		vector<HwIdentifier> alt_ids = strategy_ptr->alternative_ids();
		identifiers.insert(alt_ids.begin(), alt_ids.end(), identifiers.end());
	}
	return identifiers;
}
/**
* default strategy should never be used to validate an identifier. The strategy that was used in the first place to generate it
* should handle it. DefaultStrategy is just a switch.
*/
LCC_EVENT_TYPE DefaultStrategy::validate_identifier(const HwIdentifier& identifier) const {
	// 
	return IDENTIFIERS_MISMATCH;
}

}  // namespace hw_identifier
} /* namespace license */
