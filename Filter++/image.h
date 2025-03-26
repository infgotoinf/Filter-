#pragma once

#ifndef IMAGE_H
#define IMAGE_H

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

struct Image
{
    fs::path path;
    std::fstream data;
    bool inDestructorDelete;

    Image(fs::path path, bool inDestructorDelete)
        : path(path), inDestructorDelete(inDestructorDelete)
    {}
    Image()
    {
        FILE* f;
        inDestructorDelete = true;
        tmpfile_s(&f);
        data = std::fstream(f);
    }
    ~Image() {
        if (inDestructorDelete)
            std::remove(path.string().c_str());
        data.close();
    }
    Image& operator=(Image const& other)
    {
        this->path = other.path;
        this->inDestructorDelete = other.inDestructorDelete;
        this->data = other.data;
        return *this;
    }

    void operator()(fs::path path, bool inDestructorDelete){
        this->path = path; this->inDestructorDelete = inDestructorDelete;
    }

    void open() {
        data.open(path, std::ios::in);
    }
    void create() {
        data.open(path, std::ios::out);
    }
    void smartCreate() {
        if (fs::exists(path)) std::remove(path.string().c_str());
        create();
    }
};

#endif IMAGE_H