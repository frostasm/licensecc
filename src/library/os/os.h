/*
 * os-dependent.hpp
 *
 *  Created on: Mar 29, 2014
 *
 */

#ifndef OS_DEPENDENT_HPP_
#define OS_DEPENDENT_HPP_

#include <string>

#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
// definition of size_t
#include <stdlib.h>
#include <vector>
#ifdef __unix__
#include <unistd.h>
#include <stdbool.h>
#endif

#include <licensecc/datatypes.h>
#include "../base/base.h"

typedef struct {
	int id;
	char device[MAX_PATH];
	unsigned char disk_sn[8];
	std::string disk_serial; // full serial number of disk, used with os_disk strategy
	bool sn_initialized;
	char label[255];
	bool label_initialized;
	bool preferred;
} DiskInfo;

struct MotherboardInfo {
	std::string product_uuid;
	std::string product_serial;
	std::string board_serial;
	void clear() {
		product_uuid.clear();
		product_serial.clear();
		board_serial.clear();
	}
	bool empty() const {
		return product_uuid.empty() && product_serial.empty() && board_serial.empty();
	}
};

FUNCTION_RETURN getMotherboardInfo(MotherboardInfo& motherboardInfo);
FUNCTION_RETURN getOsDiskInfo(DiskInfo& diskInfo);
FUNCTION_RETURN getDiskInfos(std::vector<DiskInfo>& diskInfos);
FUNCTION_RETURN getUserHomePath(char[MAX_PATH]);
FUNCTION_RETURN getModuleName(char buffer[MAX_PATH]);
FUNCTION_RETURN getMachineName(unsigned char identifier[6]);
/**
 * Get an identifier of the machine in an os specific way.
 * In Linux it uses:
 * http://stackoverflow.com/questions/328936/getting-a-unique-id-from-a-unix-like-system
 *
 * <ul>
 * <li>Dbus if available</li>
 * </ul>
 * Can be used as a fallback in case no other methods are available.
 * Windows:
 * HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\ CurrentVersion\ProductId
 * http://sowkot.blogspot.it/2008/08/generating-unique-keyfinger-print-for.html
 * http://stackoverflow.com/questions/2842116/reliable-way-of-generating-unique-hardware-id
 *
 *
 * @param identifier
 * @return
 */
FUNCTION_RETURN getOsSpecificIdentifier(unsigned char identifier[6]);

std::string os_readlink(std::string const& path, bool * const ok = nullptr);
std::string os_realpath(std::string const& path, bool * const ok = nullptr);

#ifdef _WIN32
#define SETENV(VAR, VAL) _putenv_s(VAR, VAL);
#define UNSETENV(P) _putenv_s(P, "");
#else
#define SETENV(VAR, VAL) setenv(VAR, VAL, 1);
#define UNSETENV(P) unsetenv(P);
#endif

#endif /* OS_DEPENDENT_HPP_ */
