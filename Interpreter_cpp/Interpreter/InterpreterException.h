
// (c) David Sykes 2013
// One more time, for the kids!


class InterpreterException: public std::runtime_error
{
    public:
        InterpreterException(std::string const& msg):
            std::runtime_error(msg)
        {}
};


