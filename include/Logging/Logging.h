#ifndef LOGGING_H
#define LOGGING_H

#include<iostream>
#include<string>

namespace Logging
{

	inline void log(std::string caller, std::string str)
	{
		std::cout << caller << ": " << str << '\n';
	}

	/*template<class... Types>
	inline void log(std::string caller, std::string str, Types... extra)
	{
		std::cout << caller << ": " << str << " ";

		for(auto&& arg : { extra... })
		{
			std::cout << arg << " ";
		}

		std::cout << '\n';
	}*/


	// TODO: Work on this
	
	#define ASSERT_LEVEL_FATAL 		0
	#define ASSERT_LEVEL_NON_FATAL 	1

	inline bool assertLog(bool exp)
	{
		if(exp)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

}

#endif