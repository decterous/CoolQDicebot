#include "stdafx.h"
#include "utility.h"
#include "nick_manager.h"
#include "dice_spliter.h"
#include "dice_protocol.h"
#include "protocol_roll_dice.h"

//regular dice, with detailed info

protocol_roll_dice::protocol_roll_dice()
{
	this->regex_detail_command = new std::regex("^s *");
	this->identifier = new std::string("r");
	this->regex_filter_full_dice = new std::regex("^ *(\\+|\\-)?((\\d*d\\d+((k|kl)\\d+)?)|\\d+)((\\+|\\-|\\*|/)((\\d*d\\d+((k|kl)\\d+)?)|\\d+))* *");
}


protocol_roll_dice::~protocol_roll_dice()
{
	delete this->regex_detail_command;
	delete this->identifier;
	delete this->regex_filter_full_dice;
}

std::string protocol_roll_dice::resolve_request(
	std::string message,
	const int32_t i_AuthCode,
	const int64_t uint64_fromGroupOrDiscuss,
	const int64_t uint64_fromQQ,
	bool isfromGroup)
{
	bool detailed_roll_message = false;
	std::smatch match_list_command_detail;
	std::regex_search(message, match_list_command_detail, *this->regex_detail_command);
	if (match_list_command_detail.begin() != match_list_command_detail.end()) {
		detailed_roll_message = true;
		message = match_list_command_detail.suffix().str();
	}

	std::smatch match_list_command_full_dice_roll_match;
	std::regex_search(message, match_list_command_full_dice_roll_match, *this->regex_filter_full_dice);
	if (match_list_command_full_dice_roll_match.begin() != match_list_command_full_dice_roll_match.end()) {
		std::string str_roll_message = match_list_command_full_dice_roll_match.suffix().str();
		std::string str_roll_source = match_list_command_full_dice_roll_match.str();
		remove_space_and_tab(str_roll_source);
		std::string str_roll_output;
		if (base_split_dice(str_roll_source, str_roll_output, detailed_roll_message)) {
			std::ostringstream ostrs_output_stream(std::ostringstream::ate);

			std::string str_nickname;
			(nickname_manager::instance)->get_nickname(i_AuthCode, uint64_fromGroupOrDiscuss, uint64_fromQQ, str_nickname, isfromGroup);

			ostrs_output_stream << " * " << str_nickname << " " << str_roll_message << " ����: ";
			ostrs_output_stream << str_roll_output;
			return ostrs_output_stream.str();
		}
	}
	return std::string();
}