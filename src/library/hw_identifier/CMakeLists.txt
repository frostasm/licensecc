add_library(hw_identifier OBJECT
	hw_identifier_facade.hpp
	hw_identifier_facade.cpp
	default_strategy.hpp
	default_strategy.cpp
	ethernet.hpp
	ethernet.cpp
	disk_strategy.hpp
	disk_strategy.cpp
	os_disk_strategy.hpp
	os_disk_strategy.cpp
	identification_strategy.hpp
	identification_strategy.cpp
	hw_identifier.hpp
	hw_identifier.cpp
	motherboard_strategy.hpp
	motherboard_strategy.cpp
)

if(CODE_COVERAGE AND UNIX)
	  target_compile_options(hw_identifier PUBLIC -O0 -g --coverage)
endif(CODE_COVERAGE AND UNIX)
