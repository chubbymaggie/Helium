#ifndef _EXLAGO_MEMLAYOUT_H
#define _EXALGO_MEMLAYOUT_H

#include <vector>
#include "meminfo.h"
#include "moduleinfo.h"
#include <fstream>
#include <string>

struct func_composition_t {

	std::string module_name;
	uint32_t func_addr;
	std::vector<pc_mem_region_t *> region;

};

std::vector<pc_mem_region_t *> get_mem_regions_from_memtrace(std::vector<std::ifstream *> &memtrace, moduleinfo_t * head);
std::vector<func_composition_t *> create_func_composition(std::vector<pc_mem_region_t *> &regions, moduleinfo_t * head);

void print_app_pc_info(std::ofstream &file, std::vector<func_composition_t *> &funcs);

#endif