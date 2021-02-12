#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
	NEW,          // новая
	IN_PROGRESS,  // в разработке
	TESTING,      // на тестировании
	DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {

	map<string, TasksInfo> personsTask;

public:
	const TasksInfo& GetPersonTasksInfo(const string& person) const {
		if (personsTask.count(person)) {
			return personsTask.at(person);
		}
		else {
			return {};
		}
	}

	void AddNewTask(const string& person) {
		personsTask[person][TaskStatus::NEW]++;
	}

	tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {

		if (!personsTask.count(person)) {
			return {};
		}
		
		TasksInfo currentPersonTasks = personsTask[person],
			newTasks, oldTasks = currentPersonTasks,
			dumpedTasks = personsTask[person];
		
		if (currentPersonTasks.empty()) {
			return {};
		}
		
		int uncompletedTasksNb = 0;
		for (auto iter = currentPersonTasks.begin(); iter != currentPersonTasks.end(); iter++) {
			if (iter->first != TaskStatus::DONE) {
				uncompletedTasksNb += iter->second;
			}
		}
		if (task_count > uncompletedTasksNb) {
			task_count = uncompletedTasksNb;
		}
		
		TaskStatus curTaskStatus = TaskStatus::NEW,
			nextTaskStatus;
		
		while (task_count && curTaskStatus != TaskStatus::DONE) {
		
			bool existsTaskCurType = dumpedTasks.count(curTaskStatus);
			nextTaskStatus = TaskStatus(int(curTaskStatus) + 1);
		
			// if exist tasks of current type
			if (existsTaskCurType) {
		
				// number of task with current type
				int curTypeTasksNb = dumpedTasks[curTaskStatus];
		
				// take min of two values
				int availableTasksToPerform = min(curTypeTasksNb, task_count);
		
				if (availableTasksToPerform == 0) {
					curTaskStatus = nextTaskStatus;
					continue;
				}
		
				task_count -= availableTasksToPerform;
		
				newTasks[nextTaskStatus] += availableTasksToPerform;
				oldTasks[curTaskStatus] -= availableTasksToPerform;
		
				currentPersonTasks[curTaskStatus] -= availableTasksToPerform;
				currentPersonTasks[nextTaskStatus] += availableTasksToPerform;
			}

			curTaskStatus = nextTaskStatus;
		}
		
		if (oldTasks[TaskStatus::DONE] == dumpedTasks[TaskStatus::DONE]) {
			oldTasks[TaskStatus::DONE] = 0;
		}
		
		bool existNullValues;
		
		// erase null value keys in newTasks
		existNullValues = true;
		while (existNullValues) {
			existNullValues = false;
			for (auto iter = newTasks.begin(); iter != newTasks.end(); iter++) {
				if (iter->second == 0) {
					newTasks.erase(iter);
					existNullValues = true;
					break;
				}
			}
		}
		
		// erase null value keys in oldTasks
		existNullValues = true;
		while (existNullValues) {
			existNullValues = false;
			for (auto iter = oldTasks.begin(); iter != oldTasks.end(); iter++) {
				if (iter->second == 0) {
					oldTasks.erase(iter);
					existNullValues = true;
					break;
				}
			}
		}
		
		// erase null value keys in currentPersonTasks
		existNullValues = true;
		while (existNullValues) {
			existNullValues = false;
			for (auto iter = currentPersonTasks.begin(); iter != currentPersonTasks.end(); iter++) {
				if (iter->second == 0) {
					currentPersonTasks.erase(iter);
					existNullValues = true;
					break;
				}
			}
		}
		
		// save changes in global map
		personsTask[person] = currentPersonTasks;
		
		return { newTasks, oldTasks };
	}
};

void PrintTasksInfo(TasksInfo tasks_info) {
	cout << "(" << tasks_info[TaskStatus::NEW] << ", " << tasks_info[TaskStatus::IN_PROGRESS] << ", " 
		 << tasks_info[TaskStatus::TESTING] << ", " << tasks_info[TaskStatus::DONE] << ")" << endl;
}

int main() {
	TeamTasks tasks;
	TasksInfo updated_tasks, untouched_tasks;

	for (int i = 0; i < 5; i++) {
		tasks.AddNewTask("Alice");
	}
	cout << "Alice tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));

	cout << "----------------------------------\n";

	tie(updated_tasks, untouched_tasks) =
		tasks.PerformPersonTasks("Alice", 5);
	cout << "Updated Alice tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Alice tasks: ";
	PrintTasksInfo(untouched_tasks);

	cout << "----------------------------------\n";

	tie(updated_tasks, untouched_tasks) =
		tasks.PerformPersonTasks("Alice", 5);
	cout << "Updated Alice tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Alice tasks: ";
	PrintTasksInfo(untouched_tasks);

	cout << "----------------------------------\n";

	tie(updated_tasks, untouched_tasks) =
		tasks.PerformPersonTasks("Alice", 1);
	cout << "Updated Alice tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Alice tasks: ";
	PrintTasksInfo(untouched_tasks);

	cout << "----------------------------------\n";

	for (int i = 0; i < 5; i++) {
		tasks.AddNewTask("Alice");
	}
	cout << "Alice tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));

	cout << "----------------------------------\n";

	tie(updated_tasks, untouched_tasks) =
		tasks.PerformPersonTasks("Alice", 2);
	cout << "Updated Alice tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Alice tasks: ";
	PrintTasksInfo(untouched_tasks);

	cout << "----------------------------------\n";

	cout << "Alice tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));

	cout << "----------------------------------\n";

	tie(updated_tasks, untouched_tasks) =
		tasks.PerformPersonTasks("Alice", 4);
	cout << "Updated Alice tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Alice tasks: ";
	PrintTasksInfo(untouched_tasks);

	cout << "----------------------------------\n";

	cout << "Alice tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));

	cout << "----------------------------------\n";

	return 0;
}