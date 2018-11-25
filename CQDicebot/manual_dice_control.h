#pragma once

class manual_dice;

#define TYPE_KEY_MANUALDICE std::pair<int64_t, int64_t>
#define TYPE_MAP_MANUALDICE std::map<TYPE_KEY_MANUALDICE, manual_dice> 
#define TYPE_PAIR_MANUALDICE std::pair<TYPE_KEY_MANUALDICE, manual_dice> 

class manual_dice_manager
{
	bool is_no_sql_mode;
public:
	static manual_dice_manager * instance;
	TYPE_MAP_MANUALDICE * map_manualdicemap;
	manual_dice_manager();
	~manual_dice_manager();
	manual_dice * create_manual_dice(const int64_t i_QQID, const int64_t i_QQGroupID, const std::string & command);
	manual_dice * roll_manual_dice(const int64_t i_QQID, const int64_t i_QQGroupID, const std::string & command);
	manual_dice * kill_manual_dice(const int64_t i_QQID, const int64_t i_QQGroupID, const std::string & command);
	manual_dice * add_manual_dice(const int64_t i_QQID, const int64_t i_QQGroupID, const std::string & command);
	manual_dice * killall_manual_dice(const int64_t i_QQID, const int64_t i_QQGroupID);
	static int sqlite3_callback_query_manualdice(void * data, int argc, char ** argv, char ** azColName);
};
