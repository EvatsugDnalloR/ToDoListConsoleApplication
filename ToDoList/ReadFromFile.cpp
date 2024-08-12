#include "ReadFromFile.h"

/**
 * The method that convert all the ToDos in the {input} string converted from
 *      the txt file to several To_Do objects, and put them all in a vector
 *      such that they can be iterated through.
 * @param input     the input string that contain all the ToDos
 * @pre {input} string should follow the correct format to initialise all
 *      the To_Do object, or it can be an empty string
 * @return  a vector that contains all the To_Do objects, or an empty vector if
 *      the {input} string is empty
 * @throw runtime_error     if {input} stream doesn't follow the correct format, more
 *      details in the {PushToDo} function
 * @post either the vector that contains all the To_Do objects has been returned,
 *      or a runtime_error has been thrown
 */
std::vector<ToDo> ReadFromFile::GetToDos(std::string input)
{
    if (input.empty())
    {
        return std::vector<ToDo>{};
    }

    std::istringstream input_ref(std::move(input));
    std::string line;
    std::vector<ToDo> todo_vector;

    while (std::getline(input_ref, line))
    {
        PushToDo(line, todo_vector);
    }

    return todo_vector;
}

/**
 * Auxiliary method that try to turn a line of the string obtained from
 *      the txt file into a To_Do object, and insert it into the
 *      vector object that should be returned by GetToDos.
 * @param line  a line from the {input} string from GetToDos
 * @param todo_vector   the vector that should get the To_Do object
 *      converted from the line string, parsed as a reference such that
 *      the modification inside of this function can be reflected back to
 *      the {GetToDos} function
 * @pre the {line} string is following the correct format to initiate a To_Do object
 * @throw runtime_error     if '#' character is not in {line} string
 * @throw runtime_error     if nothing after the '#' character
 * @throw runtime_error     if the character after '#' is not '0' or '1',
 *      which indicates the {done} boolean of a To_o object
 * @post either the To_Do object converted from {line} string is inserted to
 *      the {todo_vector}, or a runtime_error has been thrown
 */
void ReadFromFile::PushToDo(std::string line, std::vector<ToDo>& todo_vector)
{
    const size_t pos = line.find('#');
    if (pos == std::string::npos)
    {
        throw std::runtime_error("Missing '#' character");
    }

    const std::string msg = line.substr(0, pos);
    if (line.size() <= pos + 1)
    {
        throw std::runtime_error("Missing status value after '#' character");
    }

    const char status_char = line[pos + 1];
    if (status_char != '0' && status_char != '1')
    {
        throw std::runtime_error("Invalid status value after '#' character");
    }

    const bool done = (status_char == '1');
    const ToDo to_do{ msg, done };
    todo_vector.push_back(to_do);
}

/**
 * The method that reads the txt file and convert it to a string object.
 * @param filename  the name of the txt file, normally should be "specification.txt",
 *      here parsed by parameter for testing different files
 * @return  if {filename} exists, then return the content of the {filename} txt
 *      as a string object, otherwise create a txt file of name {filename}, and
 *      return an empty string
 */
std::string ReadFromFile::FileToString(const std::string& filename)
{
    std::ifstream infile(filename);

    /*
     * If file doesn't exist, create it, a blank txt file
     *  and return an empty string.
     */
    if (!infile)
    {
        std::ofstream outfile(filename);
        return "";
    }

    /*
     * Read the contents of the existing file.
     */
    std::string content((std::istreambuf_iterator<char>(infile)),
        std::istreambuf_iterator<char>());
    return content;
}