#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>

namespace MyArgParse{

	typedef enum arg_type
	{
		ARG,
		OPT,
		SPLT,
		HLP
	}			e_arg_type;

	typedef struct s_argument
	{
		std::string name;
		std::string define;
		std::string	value;
		int			priority;
		bool		required;
		char		split;
		e_arg_type	type;

	}				t_argument;

	class ArgParser
	{
		private:
			int		_argc;
			char	**_argv;

			int		args_added;
			int		args_required;

			std::map<std::string, std::string> args;
			std::vector<t_argument> arguments;

			void _addBase(const std::string& name, const std::string& define, bool required, e_arg_type type);

		public:
			ArgParser(void);
			ArgParser(int argc, char **argv);
			~ArgParser() {}

			std::map<std::string, std::string> parse();

			void addArgument(const std::string& name, const std::string& define, bool required);
			void addOption(const std::string& name, const std::string& define, bool required);
			void addHelp(const std::string& name, const std::string& define, bool required);
			void addSplitArgument(const std::string& name, const std::string& define, int count, char split, bool required);

			class InvalidArgument: public std::exception
			{
				const char *what() const throw() {return "Invalid argument";}
			};
			void testInvalidArgument() { throw InvalidArgument(); }
			
	};
}