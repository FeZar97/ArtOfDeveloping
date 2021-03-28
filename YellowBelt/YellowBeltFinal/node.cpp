#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const string& event) const {
	return true;
}

DateComparisonNode::DateComparisonNode(const Comparison& cmp_, const Date& date_) : cmp(cmp_), date(date_) {
}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
	switch (cmp) {
		case Comparison::Less:
			return date < this->date;
		case Comparison::LessOrEqual:
			return ( (date < this->date) || (date == this->date));
		case Comparison::Greater:
			return date > this->date;
		case Comparison::GreaterOrEqual:
			return ((date > this->date) || (date == this->date));
		case Comparison::Equal:
			return date == this->date;
		case Comparison::NotEqual:
			return !(date == this->date);
		default:
			return true;
	}
}

EventComparisonNode::EventComparisonNode(const Comparison& cmp_, const string& event_): cmp(cmp_), event(event_) {
}

bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
	switch (cmp) {
	case Comparison::Less:
		return event < this->event;
	case Comparison::LessOrEqual:
		return event <= this->event;
	case Comparison::Greater:
		return event > this->event;
	case Comparison::GreaterOrEqual:
		return event >= this->event;
	case Comparison::Equal:
		return event == this->event;
	case Comparison::NotEqual:
		return event != this->event;
	default:
		return true;
	}
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation& op_, shared_ptr<Node> leftOp_, shared_ptr<Node> rightOp_):
	op(op_), leftOp(leftOp_), rightOp(rightOp_) {
}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
	switch (op) {
	case LogicalOperation::Or:
		return leftOp->Evaluate(date, event) || rightOp->Evaluate(date, event);
	case LogicalOperation::And:
		return leftOp->Evaluate(date, event) && rightOp->Evaluate(date, event);
	default:
		return true;
	}
}
