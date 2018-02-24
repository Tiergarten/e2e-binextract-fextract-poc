struct entry_point_tracker {
	ADDRINT entry_point, exit_point;
	unsigned int passed_entry_point;
};

#define IF_IN_MODULE(addr, tracker) \
	if (addr >= tracker.entry_point && addr <= tracker.exit_point)