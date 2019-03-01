#include <iostream>
#include <fstream>
#include <algorithm>
#include <memory>

using namespace std;

constexpr size_t CHUNK_MAX_SIZE = 1024 * 1024 * 8;

inline bool is_valid_file(ifstream &file)
{
    return (file && file.peek() != EOF);
}

inline void write_out(const int *const buffer, size_t &n, ofstream &output)
{
    for (size_t i = 0; i < n; i++) {
        output << buffer[i] << "\n";
    }

    n = 0;
}

size_t sort_chunks(const char *filename)
{
    ifstream file(filename, ifstream::binary);
    if (!file.is_open()) {
        return 0;
    }

    size_t file_cnt = 0;
    size_t max = 0;
    int *buffer = new int[CHUNK_MAX_SIZE * sizeof(int)];

    while (file >> buffer[max++]) {
        if (max == CHUNK_MAX_SIZE) {
            ofstream out("chunk." + to_string(file_cnt), std::ios::binary);
            ++file_cnt;
            sort(&buffer[0], &buffer[max]);
            write_out(buffer, max, out);
        }
    }

    sort(&buffer[0], &buffer[--max]);
    ofstream out("chunk." + to_string(file_cnt), std::ios::binary);
    write_out(buffer, max, out);

    delete []buffer;
    return ++file_cnt;
}

inline bool is_lower_than(ifstream &a, ifstream &b)
{
    int ia, ib;
    auto len_a = a.tellg();
    auto len_b = b.tellg();

    a >> ia;
    b >> ib;

    if (!a.good()) {
        b.seekg(len_b);
        return false;
    }

    if (!b.good()) {
        a.seekg(len_a);
        return true;
    }

    a.seekg(len_a);
    b.seekg(len_b);

    return (ia < ib) ? true : false;
}

void merge(size_t n_chunk_files)
{
    ofstream out("chunk.result", std::ios::binary);
    int *buffer = new int[CHUNK_MAX_SIZE * sizeof(int)];

    auto chunk_files = make_unique<ifstream[]>(sizeof(ifstream) * n_chunk_files);
    for (size_t i = 0; i < n_chunk_files; i++) {
        chunk_files[i].open("chunk." + to_string(i), ifstream::binary);
    }

    size_t idx = 0;
    while (true) {
        bool exit = true;
        int less = 0;

        for (size_t i = 0; i < n_chunk_files; i++) {
            if (is_valid_file(chunk_files[i])) {
                exit = false;
                less = i;
                break;
            }
        }

        if (exit) {
            --idx;
            write_out(buffer, idx, out);
            break;
        }

        for (size_t i = less + 1; i < n_chunk_files; i++) {
            if (!is_valid_file(chunk_files[i])) {
                continue;
            }

            if (is_lower_than(chunk_files[i], chunk_files[less])) {
                less = i;
            }
        }

        chunk_files[less] >> buffer[idx++];
        if (idx == CHUNK_MAX_SIZE) {
            write_out(buffer, idx, out);
        }
    }

    delete[] buffer;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        return 1;
    }

    auto files = sort_chunks(argv[1]);
    merge(files);

    return 0;
}
