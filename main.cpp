#include<string>
#include<iostream>
#include<array>
#include"SFML/Graphics/Image.hpp"
using namespace std;

array<string, 2> parse_arguments(char** argv);
void convert(const array<string, 2>& args);
int main(int argc, char** argv)
{
	if (argc != 3)
	{
		cout << "incorrect number of arguments!" << endl;
		cout << "example: ic -ofile.tga -ifile.png";
		exit(-1);
	}
	auto args = parse_arguments(argv);
	convert(args);


	return 0;
}
array<string, 2> parse_arguments(char** argv)
{
	string extension[] = { "bmp", "png", "tga", "jpg", "gif", "psd", "hdr", "pic" };

	auto get_extension = [](const string& str)
	{
		auto dot = str.find(".");
		if (dot == string::npos)
		{
			cout << "incorrect file:" << str << "!";
			exit(-1);
		}
		return str.substr(dot+1);
	};
	auto is_correct = [&](const string& ext)
	{
		for (int i = 0; i < 8; i++)
			if (ext == extension[i])
				return true;

		return false;
	};
	auto show_correct_exts = [&]()
	{
		cout << "provided file has incorrect extension!" <<endl
		     <<"correct extensions:";
		for (int i = 0; i < 8; i++)
		{
			auto last = i != 7 ? ", " : "";
			cout << "." << extension[i] << last;
		}
	};
	auto check_extension = [&](const string& str)
	{
		auto ext = get_extension(str);
		if (!is_correct(ext))
		{
			show_correct_exts();
			exit(-1);
		}
	};

	string file_to_open, file_to_write;
	for (int i = 1; i < 3; i++)
	{
		auto arg = string(argv[i]);
		if (arg.substr(0, 2) == "-o" and file_to_open.empty())
		{
			check_extension(arg);
			file_to_open = arg.substr(2);
		}
		else if (arg.substr(0, 2) == "-i" and file_to_write.empty())
		{
			//check_extension(arg);
			file_to_write = arg.substr(2);
		}
		else
		{
			cout << "incorrect argument:" << arg << endl;
			cout << "example: tgac -ofile.tgf -ifile.png";
			exit(-1);
		}
	}
	return array<string, 2>{file_to_open, file_to_write};
}
void convert(const array<string, 2>& args)
{
	sf::Image open;
	if (!open.loadFromFile(args[0]))
	{
		cout << "can't load " << args[0] << "!";
		exit(-1);
	}

	if (open.saveToFile(args[1]))
	{
		cout << "saved " << args[1] << " successfully!" << endl;
	}
	else
	{
		cout << "failed to save " << args[1]<<"!" << endl;
	}

}