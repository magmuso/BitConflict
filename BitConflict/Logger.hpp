#pragma once
#include <ostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

#ifdef DEBUG
#include <iostream>
#endif

class Logger
{
public:
	Logger()
	{
#ifdef DEBUG
		add_output(&std::cout);
		add_output_file("debug.txt");
#endif
	}


	~Logger()
	{
		for (auto i = output_files.begin(); i != output_files.end(); i++)
		{
			i->close();
		}
	}

	void add_output(std::ostream * stream)
	{
		output_streams.push_back(stream);
	}

	void add_output_file(const std::string & file)
	{
		try{
			std::ofstream f_handle;
			f_handle.open(file.c_str(), std::ios_base::app);
			output_files.push_back(std::move(f_handle));
		}
		catch (...)
		{
			debug("Could not open file" + file);
		}
	}

	template<typename... Args>
	void info(const Args&... args)
	{
		print_official_line(" INFO: ", args...);
	}

	template<typename... Args>
	void debug(const Args&... args)
	{
#ifdef DEBUG
		print_official_line(" DEBUG: ", args...);
#endif
	}

	template<typename... Args>
	void warn(const Args&... args)
	{
		print_official_line(" WARNING: ", args...);
	}

	template<typename... Args>
	void error(const Args&... args)
	{
		print_official_line(" ERROR: ", args...);
		flush_outputs();
	}

	void flush_outputs()
	{
		for (auto i = output_streams.begin(); i != output_streams.end(); i++)
		{
			(*i)->flush();
		}
		for (auto i = output_files.begin(); i != output_files.end(); i++)
		{
			i->flush();
		}
	}
private:
	std::vector<std::ostream *> output_streams;
	std::vector<std::ofstream> output_files;
	std::stringstream buffer;

	template<typename... Args>
	void print_official_line(const std::string & str, const Args&... args)
	{
		print_datetime();
		print(str, args...);
	}

	void print()
	{
		buffer << std::endl;
		// flush the buffer into the logs
		auto string = buffer.str();

		for (auto i = output_streams.begin(); i != output_streams.end(); i++)
		{
			if ((*i) != nullptr) (*(*i)) << string;
		}

		for (auto i = output_files.begin(); i != output_files.end(); i++)
		{
			if (!(i->bad())) (*i) << string;
		}
		buffer.str(std::string());
	}

	template<typename First, typename... Args>
	void print(const First & first, const Args&... args)
	{
		buffer << first;
		print(args...);
	}

	void print_datetime()
	{
		std::time_t raw_time;
		struct std::tm timeinfo;
		std::time(&raw_time);
#ifdef POSIX
		std::gmtime_r(&raw_time, &timeinfo);
#else
		gmtime_s(&timeinfo, &raw_time);
#endif
		char time_buffer[20];
		std::strftime(time_buffer, 20, "%Y-%m-%d %H:%M:%S", &timeinfo);
		// TO BE IMPLEMENTED
		buffer << time_buffer;
	}
};
extern Logger * g_logger;