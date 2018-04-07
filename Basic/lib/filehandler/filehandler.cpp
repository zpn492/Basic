#include "filehandler.h"

bool filehandler::exists_file(const char *filename, Logger &logger)
    {
    std::ifstream tfile(filename);
        if(tfile.is_open())
            {
            tfile.close();
            return true;
            }
	logger.setColor(FRED);
	printf("File not found, %s\n", filename);
	logger.resetColor();
    return false;
    };

/* Read an entire file into a string */
std::string filehandler::get_file_contents(const char *filename, Logger &logger)
	{   
	if(!filehandler::exists_file(filename, logger))
		return std::string("");
	std::ifstream in(filename, std::ios::in | std::ios::binary);
	if (in)
		{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
		}
	throw(errno);
	};

bool filehandler::create_file(const char *filename, Logger &logger)
    {
	if(!filehandler::exists_file(filename, logger))
		{
		std::ofstream mfile;
		mfile.open(filename);
		mfile.close();
		logger.setColor(FGREEN);
		printf("Create file, %s\n", filename);
		logger.resetColor();
		return true;
		}
	return false;
    };

bool filehandler::delete_file(const char *filename, Logger &logger)
    {
	if(remove(filename) != 0)
		{
		return false;
		}
		logger.setColor(FYELLOW);
		printf("Delete file, %s\n", filename);
		logger.resetColor();
	return true;
    };

std::vector<std::string> filehandler::split_string(std::string &stemp, char delimeter)
    {
    std::vector<std::string> tokens;
    size_t pos;
    while((pos = stemp.find(delimeter))!=std::string::npos)
        {
        std::string ss = stemp.substr(0, pos);
        stemp = stemp.erase(0, pos + 1);
        tokens.push_back(ss);
        }
        tokens.push_back(stemp);
    return tokens;
    };

std::vector<std::string> filehandler::divide_string(std::string s1, int times)
	{	
	std::vector<std::string> data1, data2;
	std::string s2="";
	
	int t = s1.length();
	
	s2 = s1.substr(s1.length()/2+1);	
	s1 = s1.substr(0, s1.length()/2+1);
	
	// Make sure splitting by chunks won't mess up input data
	// find \n
	// if \n != last char
	if(s1[s1.length()-1] != '\n')
		{
		s2 = s1.substr(s1.find_last_of('\n')+1) + s2;
		s1 = s1.substr(0, s1.find_last_of('\n'));
		}
	
	if(times != 1 && t > 10000)
		{
		data1 = divide_string(s1, times-1);
		data2 = divide_string(s2, times-1);
		}
	else
		{
		data1.push_back(s1);
		data2.push_back(s2);
		}
	
	data1.insert(data1.end(), data2.begin(), data2.end());
	
	return data1;
	}

void filehandler::write_file(const char *filename, std::string text)
    {
    std::ofstream outf;
    outf.open(filename);

    outf << text.c_str();
    outf.close();
    };

void filehandler::print_file(const char *filename, Logger &logger)
    {
    if(!filehandler::exists_file(filename, logger))
        return;
    std::ifstream mfile(filename);
    std::string line;

    while(getline(mfile, line))
        printf("%s \n", line.c_str());

    mfile.close();
    };

std::string filehandler::int_to_string(int value)
    {
    std::ostringstream oss;
    oss << value;
    return oss.str();
    };
	
void filehandler::replace(std::string &s, char before, char after)
	{
	std::replace(s.begin(), s.end(), before, after);
	}