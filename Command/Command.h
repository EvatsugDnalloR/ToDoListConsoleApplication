#pragma once

class Command
{
	bool executed_;

public:
	explicit Command(const bool executed);
    virtual ~Command() = default;

    // Copy constructor
    Command(const Command& other) = default;

    // Copy assignment operator
    Command& operator=(const Command& other);

    // Move constructor
    Command(Command&& other) noexcept;

    // Move assignment operator
    Command& operator=(Command&& other) noexcept;

	[[nodiscard]] bool GetExecuted() const;

	virtual void Execute();

	virtual void Revert();
};
