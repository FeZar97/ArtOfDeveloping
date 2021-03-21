#pragma once

#include "date.h"
#include "database.h"

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

enum class LogicalOperation {
	Or,
	And
};
// -----------------------

class Node {
public:
	virtual bool Evaluate(const Date& date, const string& event);
};

class EmptyNode : public Node {
public:
	bool Evaluate(const Date& date, const string& event) override;
};

class DateComparisonNode : public Node {
	const Comparison cmp;
	const Date date;
public:
	DateComparisonNode(const Comparison& cmp_, const Date& date_);
	bool Evaluate(const Date& date, const string& event) override;
};

class EventComparisonNode : public Node {
	const Comparison cmp;
	const string event;
public:
	EventComparisonNode(const Comparison& cmp_, const string& event_);
	bool Evaluate(const Date& date, const string& event) override;
};

class LogicalOperationNode : public Node {
	LogicalOperation op;
	shared_ptr<Node> leftOp;
	shared_ptr<Node> rightOp;

public:
	LogicalOperationNode(const LogicalOperation& op_, shared_ptr<Node> leftOp_, shared_ptr<Node> rightOp_);
	bool Evaluate(const Date& date, const string& event) override;
};