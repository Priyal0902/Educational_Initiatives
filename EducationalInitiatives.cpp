#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <regex>

using namespace std;

class Task {
public:
  Task(const string& taskDescription)
    : description(taskDescription), completed(false), dueDate(""), tags("") {}

  void markCompleted() {
    completed = true;
  }

  void markPending() {
    completed = false;
  }

  void setDueDate(const string& date) {
    dueDate = date;
  }

  void setTags(const string& taskTags) {
    tags = taskTags;
  }

  bool isCompleted() const {
    return completed;
  }

  string getDescription() const {
    return description;
  }

  string getDueDate() const {
    return dueDate;
  }

  string getTags() const {
    return tags;
  }

private:
  string description;
  bool completed;
  string dueDate;
  string tags;
};

class TaskBuilder {
public:
  TaskBuilder(const string& taskDescription) : task(taskDescription) {}

  TaskBuilder& setDueDate(const string& date) {
    task.setDueDate(date);
    return *this;
  }

  TaskBuilder& setTags(const string& tags) {
    task.setTags(tags);
    return *this;
  }

  Task build() {
    return task;
  }

private:
  Task task;
};

class TaskList {
public:
  void addTask(const Task& task) {
    tasks.push_back(task);
  }

  void markTaskAsCompleted(const string& description) {
    for (auto& task : tasks) {
      if (task.getDescription() == description) {
        task.markCompleted();
        return;
      }
    }
    cout << "Task not found.\n";
  }

  void deleteTask(const string& description) {
    auto it = remove_if(tasks.begin(), tasks.end(),
      [description](const Task& task) {
        return task.getDescription() == description;
      }
    );
    if (it != tasks.end()) {
      tasks.erase(it, tasks.end());
    } else {
      cout << "Task not found.\n";
    }
  }

  void showAllTasks() const {
    for (const auto& task : tasks) {
      displayTask(task);
    }
  }

  void showCompletedTasks() const {
    for (const auto& task : tasks) {
      if (task.isCompleted()) {
        displayTask(task);
      }
    }
  }

  void showPendingTasks() const {
    for (const auto& task : tasks) {
      if (!task.isCompleted()) {
        displayTask(task);
      }
    }
  }

private:
  vector<Task> tasks;

  void displayTask(const Task& task) const {
    cout << task.getDescription() << " - ";
    if (task.isCompleted()) {
      cout << "Completed";
    } else {
      cout << "Pending";
    }
    if (!task.getDueDate().empty()) {
      cout << ", Due: " << task.getDueDate();
    }
    if (!task.getTags().empty()) {
      cout << ", Tags: " << task.getTags();
    }
    cout << endl;
  }
};

// Function to validate a date in the format YYYY-MM-DD
bool isValidDate(const string& date) {
  regex dateRegex("\\d{4}-\\d{2}-\\d{2}");
  return regex_match(date, dateRegex);
}

int main() {
  TaskList taskList;
  bool running = true;

  while (running) {
    cout << "What would you like to do:\n";
    cout << "1. Create a new Task\n";
    cout << "2. Mark a Task as Completed\n";
    cout << "3. Delete a Task\n";
    cout << "4. Show All Tasks\n";
    cout << "5. Show Completed Tasks\n";
    cout << "6. Show Pending Tasks\n";
    cout << "7. Quit\n";

    int choice;
    cin >> choice;
    cin.ignore(); 

    switch (choice) {
      case 1: {
        string taskDescription;
        cout << "Enter task description: ";
        getline(cin, taskDescription);

        TaskBuilder builder(taskDescription);

        string dueDate;
        cout << "Enter due date (optional, format: YYYY-MM-DD): ";
        getline(cin, dueDate);
        if (!dueDate.empty() && isValidDate(dueDate)) {
          builder.setDueDate(dueDate);
        }

        string tags;
        cout << "Enter tags (optional): ";
        getline(cin, tags);
        Task newTask = builder.setTags(tags).build();
        taskList.addTask(newTask);
        break;
      }
      case 2: {
        string description;
        cout << "Enter task description to mark as completed: ";
        getline(cin, description);
        taskList.markTaskAsCompleted(description);
        break;
      }
      case 3: {
        string description;
        cout << "Enter task description to delete: ";
        getline(cin, description);
        taskList.deleteTask(description);
        break;
      }
      case 4:
        taskList.showAllTasks();
        break;
      case 5:
        taskList.showCompletedTasks();
        break;
      case 6:
        taskList.showPendingTasks();
        break;
      case 7:
        running = false;
        break;
      default:
        cout << "Invalid choice! Please select a valid option.\n";
    }
  }

  return 0;
}

