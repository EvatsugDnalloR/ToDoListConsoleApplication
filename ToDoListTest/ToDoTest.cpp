#include "pch.h"
#include "../ToDoListConsoleApplication/ToDo.h"

/**
 * Test if ToDo struct can be properly printed.
 */
TEST(ToDoTest, OperatorOverload)
{
    const ToDo todo1("Finish the code", true);
    const ToDo todo2("Write tests", false);

    // Verify the output format
    std::ostringstream oss1;
    oss1 << todo1;
    EXPECT_EQ(oss1.str(), "Finish the code [ Done ]");

    std::ostringstream oss2;
    oss2 << todo2;
    EXPECT_EQ(oss2.str(), "Write tests [  ]");
}