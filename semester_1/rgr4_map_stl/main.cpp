#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
struct Mark {
    std::string subject_;
    size_t mark_;
    Mark() : subject_(""), mark_(0) {}
    Mark(const std::string& s, size_t m) {
        if (m == 0 || m > 10) {
            throw "Invalid mark! Must be between 1 and 10.";
        }
        subject_ = s;
        mark_ = m;
    }
};
struct StudentData {
    std::string name_;
    size_t number_;
    std::vector<Mark> marks_;
    StudentData() : name_(""), number_(0), marks_() {}
};
void isOpen(std::fstream& file) {
    if (!(file.is_open())) {
        throw "File cannot be open!";
    }
}
void isEmpty(std::fstream& file) {
    if (file.peek() == std::fstream::traits_type::eof()) {
        throw "File is empty!";
    }
}
void safeInputDouble(double& value) {
    if (!(std::cin >> value)) {
        throw "Invalid input!";
    }
}
void safeInputString(std::string& value) {
    if (!(std::cin >> value)) {
        throw "Invalid input!";
    }
}
void loadFromFile(const std::string& filename, std::map<size_t, StudentData>& students) {
    std::fstream fin(filename, std::ios::in);
    isOpen(fin);
    isEmpty(fin);
    while (true) {
        StudentData st;
        if (!(fin >> st.name_ >> st.number_)) break;
        std::string subj;
        size_t mark;
        while (fin.peek() != '\n' && fin >> subj >> mark) {
            st.marks_.push_back(Mark(subj, mark));
        }
        students[st.number_] = st;
    }
}
void printInlineByRecordBook(const std::map<size_t, StudentData>& students) {
    std::map<size_t, StudentData>::const_iterator it;
    for (it = students.begin(); it != students.end(); ++it) {
        const StudentData& student = it->second;
        std::cout << student.name_ << " " << student.number_;
        std::vector<Mark>::const_iterator mit;
        for (size_t i = 0; i < student.marks_.size(); ++i) {
            std::cout << " " << student.marks_[i].subject_
                << " " << student.marks_[i].mark_;
        }
        std::cout << std::endl;
    }
}
size_t totalScore(const StudentData& st) {
    return std::accumulate(st.marks_.begin(), st.marks_.end(), 0,
        [](size_t sum, const Mark& m) { return sum + m.mark_; });
}
double averageMark(const StudentData& st) {
    if (st.marks_.empty()) return 0.0;
    return static_cast<double>(totalScore(st)) / st.marks_.size();
}
void printSortedByNameAndAverage(const std::map<size_t, StudentData>& students) {
    std::vector<StudentData> list;
    std::map<size_t, StudentData>::const_iterator it;
    for (it = students.begin(); it != students.end(); ++it) {
        list.push_back(it->second);
    }
    std::sort(list.begin(), list.end(),
        [](const StudentData& a, const StudentData& b) {
            if (a.name_ == b.name_) {
                return averageMark(a) > averageMark(b);
            }
            return a.name_ < b.name_;
        });
    for (size_t i = 0; i < list.size(); ++i) {
        std::cout << (i + 1) << " " << list[i].name_ << " "
            << list[i].number_ << " "
            << averageMark(list[i]) << std::endl;
    }
}
void normalizeLimits(double& min, double& max) {
    if (max < min) { 
        std::swap(min, max); 
    }
}
void printByAverageRange(const std::map<size_t, StudentData>& students) {
    double min, max;
    std::cout << "Enter lower limit: ";
    safeInputDouble(min);
    std::cout << "Enter upper limit: ";
    safeInputDouble(max);
    normalizeLimits(min, max);
    std::vector<StudentData> filtered;
    std::map<size_t, StudentData>::const_iterator it;
    for (it = students.begin(); it != students.end(); ++it) {
        double avg = averageMark(it->second);
        if (avg >= min && avg <= max) {
            filtered.push_back(it->second);
        }
    }
    std::sort(filtered.begin(), filtered.end(),
        [](const StudentData& a, const StudentData& b) {
            return averageMark(a) > averageMark(b);
        });
    std::cout << "Студенты со средним баллом в диапазоне [" << min << ", " << max << "]:" << std::endl;
    for (size_t i = 0; i < filtered.size(); ++i) {
        std::cout << filtered[i].name_ << " "
            << filtered[i].number_ << " "
            << averageMark(filtered[i]) << std::endl;
    }
}
void printStudentsBySubject(const std::map<size_t, StudentData>& students) {
    std::string targetSubject;
    std::cout << "Enter subject: ";
    safeInputString(targetSubject);
    std::cout << "Students who took the subject " << targetSubject << ":" << std::endl;
    std::map<size_t, StudentData>::const_iterator it;
    for (it = students.begin(); it != students.end(); ++it) {
        const StudentData& student = it->second;
        for (size_t i = 0; i < student.marks_.size(); ++i) {
            if (student.marks_[i].subject_ == targetSubject) {
                std::cout << student.name_ << " "
                    << student.number_ << std::endl;
                break;
            }
        }
    }
}
void countStudentsPerSubject(const std::map<size_t, StudentData>& students) {
    std::map<std::string, size_t> subjectCounts;
    std::map<size_t, StudentData>::const_iterator it;
    for (it = students.begin(); it != students.end(); ++it) {
        const StudentData& student = it->second;
        std::vector<std::string> seenSubjects;
        for (size_t i = 0; i < student.marks_.size(); ++i) {
            const std::string& subj = student.marks_[i].subject_;
            if (std::find(seenSubjects.begin(), seenSubjects.end(), subj) == seenSubjects.end()) {
                subjectCounts[subj]++;
                seenSubjects.push_back(subj);
            }
        }
    }
    std::cout << "Number of students in each subject: " << std::endl;
    std::map<std::string, size_t>::const_iterator sit;
    for (sit = subjectCounts.begin(); sit != subjectCounts.end(); ++sit) {
        std::cout << sit->first << ": " << sit->second << std::endl;
    }
}
void printSubjectAverages(const std::map<size_t, StudentData>& students) {
    std::map<std::string, std::vector<size_t>> subjectMarks;
    std::map<size_t, StudentData>::const_iterator it;
    for (it = students.begin(); it != students.end(); ++it) {
        const StudentData& student = it->second;
        for (size_t i = 0; i < student.marks_.size(); ++i) {
            const std::string& subj = student.marks_[i].subject_;
            size_t mark = student.marks_[i].mark_;
            subjectMarks[subj].push_back(mark);
        }
    }
    std::vector<std::pair<std::string, double>> subjectAverages;
    std::map<std::string, std::vector<size_t>>::const_iterator sit;
    for (sit = subjectMarks.begin(); sit != subjectMarks.end(); ++sit) {
        const std::string& subj = sit->first;
        const std::vector<size_t>& marks = sit->second;
      
        double avg = 0.0;
        if (!marks.empty()) {
            double sum = std::accumulate(marks.begin(), marks.end(), 0.0);
            avg = sum / static_cast<double>(marks.size());
        }
        subjectAverages.push_back({ subj, avg });
    }
    std::sort(subjectAverages.begin(), subjectAverages.end(),
        [](const std::pair<std::string, double>& a, const std::pair<std::string, double>& b) {
            return a.second > b.second;
        });
    std::cout << "Average score for each subject:\n";
    for (size_t i = 0; i < subjectAverages.size(); ++i) {
        std::cout << subjectAverages[i].first << ": "
            << subjectAverages[i].second << std::endl;
    }
}
void printMaxTotalScoreStudents(const std::map<size_t, StudentData>& students) {
    size_t maxSum = 0;
    std::map<size_t, StudentData>::const_iterator it;
    for (it = students.begin(); it != students.end(); ++it) {
        const StudentData& st = it->second;
        size_t total = 0;
        for (size_t i = 0; i < st.marks_.size(); ++i) {
            total += st.marks_[i].mark_;
        }
        if (total > maxSum) {
            maxSum = total;
        }
    }
    std::cout << "Students with the maximum score (" << maxSum << "):" <<std::endl;
    for (it = students.begin(); it != students.end(); ++it) {
        const StudentData& st = it->second;
        size_t total = 0;
        for (size_t i = 0; i < st.marks_.size(); ++i) {
            total += st.marks_[i].mark_;
        }
        if (total == maxSum) {
            std::cout << st.name_ << " " << st.number_ << " Сумма: " << total << std::endl;
        }
    }
}
void printStudentsWithBadMarks(const std::map<size_t, StudentData>& students) {
    std::cout << "Students with unsatisfactory grades (1, 2, 3):" << std::endl;
    std::map<size_t, StudentData>::const_iterator it;
    for (it = students.begin(); it != students.end(); ++it) {
        const StudentData& st = it->second;
        bool hasBadMark = false;
        for (size_t i = 0; i < st.marks_.size(); ++i) {
            size_t mark = st.marks_[i].mark_;
            if (mark >= 1 && mark <= 3) {
                hasBadMark = true;
                break;
            }
        }
        if (hasBadMark) {
            std::cout << st.name_ << " " << st.number_ << std::endl;
        }
    }
}
int main() {
    std::map<size_t, StudentData> students;
    std::string filename;
    try {
        std::cout << "Enter the name of the data file: ";
        safeInputString(filename);
        loadFromFile(filename, students);
        std::cout << "1. All students by record number:" << std::endl;
        printInlineByRecordBook(students);
        std::cout << std::endl;
        std::cout << "2. Students in alphabetical order (average score in descending order if there is a match):\n";
        printSortedByNameAndAverage(students);
        std::cout << std::endl;
        std::cout << "3. Students in the given GPA range:" << std::endl;
        printByAverageRange(students);
        std::cout << std::endl;
        std::cout << "4. Students who took the specified subject:" << std::endl;
        printStudentsBySubject(students);
        std::cout << std::endl;
        std::cout << "5. Number of students in each subject:" << std::endl;
        countStudentsPerSubject(students);
        std::cout << std::endl;
        std::cout << "6. Average score for each subject (descending):" << std::endl;
        printSubjectAverages(students);
        std::cout << std::endl;
        std::cout << "7. Students with the maximum total score:" << std::endl;
        printMaxTotalScoreStudents(students);
        std::cout << std::endl;
        std::cout << "8. Students with unsatisfactory grades (1, 2, 3):" << std::endl;
        printStudentsWithBadMarks(students);
        std::cout << std::endl;
    }
    catch (const char* msg) {
        std::cout << msg << std::endl;
    }
    return 0;
}

