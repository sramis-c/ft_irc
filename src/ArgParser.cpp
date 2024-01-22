#include "ArgParser.hpp"

namespace MyArgParse
{
	ArgParser::ArgParser(int argc, char **argv)
	{
		this->_argc = argc;
		this->_argv = argv;
		this->args_added = 0;
		this->args_required = 0;
	}

	/**
	 * Internal function to create a single arg, and add to the arguments list
	 * @param std::string name: The identificator of the argument
	 * @param std::string define: The description of the argument
	 * @param bool required: Defines if an argument is mandatory necesary
	 * @param e_arg_type type: Type of argument defined in e_arg_type enum
	*/
	void ArgParser::_addBase(const std::string& name, const std::string& define, bool required, e_arg_type type)
	{
		t_argument singleArg;

		singleArg.name = name;
		singleArg.define = define;
		singleArg.type = type;
		singleArg.required = required;
		singleArg.priority = this->args_added + 1;
		this->arguments.push_back(singleArg);
	}

	/**
	 * Create single argument an add to the list of arguments
	 * @param std::string name: The identidicator of the argument
	 * @param std::string define: The description of the argument
	 * @param bool required: Defines if the argument is mandatory necesary
	*/
	void ArgParser::addArgument(const std::string& name, const std::string& define, bool required)
	{
		this->args_added++;
		this->args_required += required;
		this->_addBase(name, define, required, ARG);
	}

	void ArgParser::addOption(const std::string& name, const std::string& define, bool required)
	{
		this->args_added++;
		this->args_required += required;
		this->_addBase(name, define, required, OPT);
	}

	void ArgParser::addSplitArgument(const std::string& name, const std::string& define, int count, char split, bool required)
	{
		static bool first = 1;
		static int	internal_count = 0;
		if(first)
		{
			first = 0;
			this->args_added++;
			this->args_required += required;
		}
		(void) name;
		(void) define;
		(void) count;
		(void) split;
		(void) required;

		internal_count++;
		if(count == internal_count)
		{
			first = 1;
			internal_count = 0;
		}
	}
	/**
	 * @return Map of strings:strings
	*/
	std::map<std::string, std::string> ArgParser::parse()
	{
		std::vector<t_argument>::iterator it = this->arguments.begin();
		std::cout << "args required	: "<< args_required << std::endl;
		std::cout << "args added 	: "<< args_added << std::endl;
		if (this->_argc != (args_required + 1))
			throw InvalidArgument();
		for (int i = 1; i < this->_argc; i++)
		{
			std::string arg = this->_argv[i];
			std::cout << it->name << std::endl;
			this->args[it->name] = _argv[i];
			++it;
		}
		return (this->args);
	}
};
