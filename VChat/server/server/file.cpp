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

namespace server {
namespace io {
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
                    const string &content){
                        return OK;
                    }
    tuple<int, vector<string> &&> list_dir(const string &dir);
    int                           deleteFile(const string &filename);
    int                           createDir(const string &dirname);
    int                           deleteDir(const string &dirname);
    tuple<int, uint64_t>          get_file_size(const string &filename);
    int  rename_file(const string &src, const string &dst);
    
    bool fileisExists(const string &filename) {
        return access(filename.c_str(), F_OK) == 0;
    }

}// namespace io
}// namespace server