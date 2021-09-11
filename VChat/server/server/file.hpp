/**
 * @file file.hpp
 * @author xmmmmmovo (13256172360@163.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef FILE_HPP
#define FILE_HPP
#include "core.hpp"

namespace server {
namespace io {
    using namespace std;
    tuple<int, string &&> get_content(const string &filename);
    int                   write_content(const string &filename, string &content);
    int rename_save(const string &name, const string &tmp_name,
                    const string &content = "");
    tuple<int, vector<string> &&> list_dir(const string &dir);
    int                           deleteFile(const string &filename);
    int                           createDir(const string &dirname);
    int                           deleteDir(const string &dirname);
    tuple<int, uint64_t>          get_file_size(const string &filename);
    int  rename_file(const string &src, const string &dst);
    bool fileisExists(const string &filename);
}// namespace io
}// namespace server

#endif// FILE_HPP