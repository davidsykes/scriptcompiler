#include "..\Parameters.h"
#include "TDDAssert.h"
#include <string>


class Argvs
{
public:
	Argvs(const char *param1):m_argv(0){m_args.push_back(param1);}
	Argvs(const char *p1,const char *p2):m_argv(0){m_args.push_back(p1);m_args.push_back(p2);}
	Argvs(const char *p1,const char *p2,const char *p3):m_argv(0){m_args.push_back(p1);m_args.push_back(p2);m_args.push_back(p3);}
	~Argvs()
	{
		if (m_argv)
		{
			for(unsigned int i=0; i<m_args.size();++i)
				delete m_argv[i];
			delete m_argv;
		}
	}

	Argvs& Add(const char *param)
	{
		m_args.push_back(param);
		return *this;
	}

	char **Argv()
	{
		if (!m_argv)
		{
			m_argv = new char *[m_args.size()+2];
			m_argv[0] = NewString("arg 0");
			for(unsigned int i=0; i<m_args.size();++i)
				m_argv[i+1] = NewString(m_args[i].c_str());
			m_argv[m_args.size()+1] = 0;
		}
		return m_argv;
	}
private:
	char *NewString(const char *text)
	{
		char *s = new char[strlen(text)+1];
		strcpy_s(s, strlen(text)+1, text);
		return s;
	}
	std::vector<std::string> m_args;
	char **m_argv;
};

void TestInvalidInput()
{
	try
	{
		Parameters sp1(":fr", Argvs("param").Argv(), 1);	//	: at beginning
		AssertTrue(false);
	}
	catch (std::exception){}
	try
	{
		Parameters sp2("fr+", Argvs("param").Argv(), 1);	//	Invalid character
		AssertTrue(false);
	}
	catch (std::exception){}
	try
	{
		Parameters sp3("frf", Argvs("param").Argv(), 1);	//	Repeated parameter
		AssertTrue(false);
	}
	catch (std::exception){}
	try
	{
		Parameters sp3("f", Argvs("-param").Argv(), 1);		//	Switch too long
		AssertTrue(false);
	}
	catch (std::exception){}
	try
	{
		Parameters sp3("f", Argvs("-p").Argv(), 1);			//	Switch not specified
		AssertTrue(false);
	}
	catch (std::exception){}
}


void TestSimpleParameter()
{
	Parameters sp("", Argvs("param").Argv(), 1);
	AssertTrue(sp.Count() == 1);
	AssertEqual("param", sp[0]);
}

void TestMultipleParameters()
{
	Parameters sp("", Argvs("param1","param2","param3").Argv(), 1);
	AssertTrue(3 == sp.Count());
	AssertEqual("param1", sp[0]);
	AssertEqual("param2", sp[1]);
	AssertEqual("param3", sp[2]);
}

void TestIncompleteOption()
{
	try
	{
		Parameters sp("t:", Argvs("-t").Argv(), 1);
		AssertTrue(false);
	}
	catch (std::exception)
	{
	}
}

void TestSimpleOption()
{
	Parameters sp("t", Argvs("-t").Argv(), 1);
	AssertTrue(sp.GetFlag('t'));
	AssertTrue(!sp.GetFlag('z'));
}

void TestSimpleOptionValue()
{
	Parameters sp("t:", Argvs("-t", "value").Argv(), 1);
	AssertTrue(!sp.GetFlag('t'));
	AssertEqual(sp.GetOption('t'), "value");
}

void TestDoubleOptionValid()
{
	Parameters sp("t:", Argvs("-t", "12.3").Argv(), 1);
	AssertTrue(12.3 == sp.GetDouble('t'));
	AssertTrue(0 == sp.GetDouble('z'));
}

void TestDuplicatedOptionDifferent()
{
	try
	{
		Parameters sp("t:", Argvs("-t","t","param").Add("-t").Add("s").Argv(), 1);
		AssertTrue(false);
	}
	catch (std::exception)
	{
	}
}

void TestDuplicatedOptionSame()
{
	Parameters sp("t:", Argvs("-t","t","param").Add("-t").Add("t").Argv(), 1);
	AssertEqual(sp.GetOption('t'), "t");
}

void TestParameters()
{
	TestInvalidInput();
	TestSimpleParameter();
	TestMultipleParameters();
	TestIncompleteOption();
	TestSimpleOption();
	TestSimpleOptionValue();
	TestDoubleOptionValid();
	TestDuplicatedOptionDifferent();
	TestDuplicatedOptionSame();
}