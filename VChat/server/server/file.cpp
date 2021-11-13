/**
 * @file file.cpp
 * @author xmmmmmovo (13256172360@163.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "file.hpp"
#include "core.hpp"
#include <dirent.h>

namespace server::io {
using namespace std;

tuple<int, string &&> get_content(const string &filename) {
    string content;
    int    fd = open(filename.c_str(), O_RDONLY);
    if (fd < 0) { return make_tuple(IO, string("")); }
    core::defer d1([=] { close(fd); });
    char        buf[4096];
    while (true) {
        int r = read(fd, buf, sizeof buf);
        if (r < 0) {
            return make_tuple(IO, content);
        } else if (r == 0) {
            break;
        }
        content.append(buf, r);
    }
    return make_tuple(OK, content);
}

int write_content(const string &filename, const string &content) {
    int fd = open(filename.c_str(), O_WRONLY | O_CREAT | O_TRUNC,
                  S_IRUSR | S_IWUSR);
    if (fd < 0) { return IO; }
    core::defer d1([=] { close(fd); });
    int         r = write(fd, content.data(), content.size());
    if (r < 0) { return IO; }
    return OK;
}

int rename_save(const string &name, const string &tmp_name,
                const string &content) {
    return OK;
}

tuple<int, vector<string> &&> list_dir(const string &dir) {
    vector<string> res;
    DIR           *d = opendir(dir.c_str());
    if (d == nullptr) { return make_tuple(IO, res); }
    dirent *entry;
    while ((entry = readdir(d)) != nullptr) { res.emplace_back(entry->d_name); }
    closedir(d);
    return make_tuple(OK, res);
}

int deleteFile(const string &filename) {
    if (unlink(filename.c_str()) != 0) { return IO; }
    return OK;
}

int createDir(const string &dirname) {
    if (mkdir(dirname.c_str(), 0755) != 0) { return IO; }
    return OK;
}

int deleteDir(const string &dirname) {
    if (rmdir(dirname.c_str()) != 0) { return IO; }
    return OK;
}

tuple<int, uint64_t> get_file_size(const string &filename) {
    struct stat sbuf {};
    if (stat(filename.c_str(), &sbuf) != 0) { return make_tuple(IO, 0); }
    return make_tuple(OK, sbuf.st_size);
}

int rename_file(const string &src, const string &dst) {
    if (rename(src.c_str(), dst.c_str()) != 0) { return IO; }
    return OK;
}

bool fileisExists(const string &filename) {
    return access(filename.c_str(), F_OK) == 0;
}

}// namespace server::io