#pragma once 
#include <iostream>

enum class Error
{
	NoError,
	CorruptedArchive
};

class Serializer
{
public:
	explicit Serializer(std::ostream& out)
		: out_(out)
	{
	}

	template <class T>
	Error save(T& object)
	{
		return object.serialize(*this);
	}

	template <class... ArgsT>
	Error operator()(ArgsT&&... args)
	{
		return process(std::forward<ArgsT>(args)...);
	}


private:

	static constexpr char Separator = ' ';
	std::ostream& out_;

	Error process(bool argument)
	{
		out_ << (argument ? "true" : "false") << Separator;
		return Error::NoError;
	}

	Error process(uint64_t argument)
	{
		out_ << argument << Separator;
		return Error::NoError;
	}

	template <class T, class... ArgsT>
	Error process(T&& arg, ArgsT&&... args)
	{
		if (process(std::forward<T>(arg)) == Error::NoError)
			return process(std::forward<ArgsT>(args)...);
		else
			return Error::CorruptedArchive;
	}
		
};

class Deserializer
{
public:
	explicit Deserializer(std::istream& in)
		:in_(in)
	{
	}

	template <class T>
	Error load(T& object)
	{
		return object.serialize(*this);
	}

	template <class... ArgsT>
	Error operator()(ArgsT&&... args)
	{
		return process(std::forward<ArgsT>(args)...);
	}

private:

	std::istream& in_;
	static constexpr char Separator = ' ';

	template <class T, class... ArgsT>
	Error process(T&& arg, ArgsT&&... args)
	{
		if (process(std::forward<T>(arg)) == Error::NoError)
			return process(std::forward<ArgsT>(args)...);
		else
			return Error::CorruptedArchive;
	}

	Error process(bool& argument)
	{
		std::string text;
		in_ >> text;
		if (text == "true")
			argument = true;
		else
			if (text == "false")
				argument = false;
			else
				return Error::CorruptedArchive;
		return Error::NoError;
	}

	Error process(uint64_t& argument)
	{
		std::string text;
		in_ >> text;
		for (std::string::iterator it = text.begin(); it != text.end(); ++it)
		{
			if ((*it >= '0') && (*it <= '9'))
				argument = argument * 10 + *it - '0';
			else
				return Error::CorruptedArchive;
		}
		return Error::NoError;
	}
};