#include <cstdio>
#include <iostream>

using namespace std;

class FWHelper
{
public:
    FILE * file;
    int ref_count;
    FWHelper(const char * s)
    {
        file = fopen(s, "w");
        ref_count = 1;
    }
    void unlink()
    {
        if (ref_count == 1) {
            fclose(file);
        }
        ref_count--;
    }
};


class FileWrapper
{
    FWHelper *fw_file;
public:
    FileWrapper(const char * s)
    {
        fw_file = new FWHelper(s);
    }
    FileWrapper & operator<< (char c)
    {
        fprintf(fw_file->file, "%c", c);
        return *this;
    }
    FileWrapper(const FileWrapper & fw)
    {
        fw_file = fw.fw_file;
        fw_file->ref_count++;
    }
    FileWrapper(FileWrapper && fw)
    {
        fw_file = fw.fw_file;
        fw.fw_file = nullptr;
    }
    FileWrapper & operator= (FileWrapper &fw)
    {
        if (&fw == this) {
            return *this;
        }
        if (fw_file) {
            fw_file->unlink();
            if (!fw_file->ref_count) {
                delete fw_file;
            }
        }
        fw_file = fw.fw_file;
        fw_file->ref_count++;
        return *this;
    }
    FileWrapper & operator= (FileWrapper && fw)
    {
        if (fw_file) {
            fw_file->unlink();
            if (!fw_file->ref_count) {
                delete fw_file;
            }
        }
        fw_file = move(fw.fw_file);
        fw.fw_file = nullptr;
        return *this;
    }
    ~FileWrapper()
    {
        if (fw_file) {
            fw_file->unlink();
            if (!fw_file->ref_count) {
                delete fw_file;
            }
        }
    }
};
