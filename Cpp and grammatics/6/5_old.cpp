#include <iostream>
#include <vector>

using namespace std;

class FileWrapper
{
    FILE * file;
    int index;
    static vector<int> ref_count;
public:
    FileWrapper(const char * s)
    {
        file = fopen(s, "w");
        index = ref_count.size();
        ref_count.push_back(1);
    }
    FileWrapper & operator<< (char c)
    {
        fprintf(file, "%c", c);
        return *this;
    }
    FileWrapper(const FileWrapper & fw)
    {
        file = fw.file;
        index = fw.index;
        ref_count[index]++;
    }
    FileWrapper(FileWrapper && fw)
    {
        file = fw.file;
        index = fw.index;
        fw.file = nullptr;
    }
    FileWrapper & operator= (FileWrapper &fw)
    {
        swap(file, fw.file);
        swap(index, fw.index);
        return *this;
    }
    FileWrapper & operator= (FileWrapper && fw)
    {
        file = move(fw.file);
        index = move(fw.index);
        fw.file = nullptr;
        return *this;
    }
    ~FileWrapper()
    {
        if (ref_count[index] == 1 && file != nullptr) {
            fclose(file);
        }
        ref_count[index]--;
    }
};

vector<int> FileWrapper::ref_count{};
