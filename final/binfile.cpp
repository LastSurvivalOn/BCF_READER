#include "custfile.h"
namespace uni {

binfile::binfile(std::string name) {
    this->name = name;
    std::vector<std::string> cols{};
    std::vector<std::vector<std::string>> rows{};
    std::vector<cell_config> cf{};
    file.open(name + ".bcf", std::ios::binary | std::ios::in| std::ios::out);
    /*(!this->file.is_open()) {
        std::cerr << "ERROR! Cannot open " << name << std::endl;
    }*/
    //if (!this->is_empty(this->file)) {
    this->read();
    //}
    //else {
    //	this->rewrite();
    //}
    this->file.close();
}

void binfile::rewrite() {
    if (!file.is_open()) {
        file.open(name + ".bcf", std::ios::binary | std::ios::out);
    }

    if (file.is_open()) {
        file.seekp(0, std::ios::beg);
        this->file << *this;
        file.close();
    }
}
void binfile::new_col(std::string name) {
    cols.push_back(name);
    for (int i = 0; i < rows.size(); i++) {
        rows[i].push_back("-");
    }
    rewrite();
}
void binfile::add_row(std::vector<std::string> data) {
    if (data.size() != cols.size()) {
        std::cerr << "ERROR! rows add" << std::endl;
        return;
    }
    rows.push_back(data);
    for (std::string value : data) {
        file.write(value.c_str(), value.size());
        file.write("\t", 1);
    }
    file.write("\n", 1);
    rewrite();
}
void binfile::add_row(std::string data, int col) {
    if (col >= 0 && col < cols.size()) {
        std::vector<std::string> row;
        for (int i = 0; i < cols.size(); i++) {
            row.push_back("-");
        }
        row[col] = data;
        rows.push_back(row);
        file.write(data.c_str(), data.size());
        file.write("\t", 1);
    }
    else {
        std::cerr << "ERROR! data rows add" << std::endl;
    }
    rewrite();
}
void binfile::delete_row(int row) {
    if (row >= 0 && row < rows.size()) {
        rows.erase(rows.begin() + row);
        rewrite();
    }
    else {
        std::cerr << "ERROR! del row" << std::endl;
    }
}
void binfile::delete_col(int col) {
    if (col >= 0 && col < cols.size()) {
        cols.erase(cols.begin() + col);
        for (std::vector<std::string>& value : rows) {
            value.erase(value.begin() + col);
        }
        rewrite();
    }
    else {
        std::cerr << "ERROR! del col" << std::endl;
    }
}
void binfile::rename_col(std::string data, int col) {
    if (col >= 0 && col < cols.size()) {
        cols[col] = data;
        rewrite();
    }
    else {
        std::cerr << "ERROR! ren col" << std::endl;
    }
}
void binfile::edit_row(int row, int col, std::string data) {
    //std::cout << rows.size() << cols.size() << std::endl;
    if ((col >= 0 && col < cols.size()) && (row >= 0 && row < rows.size())) {
        rows[row][col] = data;
        rewrite();
    }
    else {
        std::cerr << "ERROR! edit row" << std::endl;
    }
}
void binfile::edit_row(int row, std::vector<std::string> data) {
    if (row >= 0 && row < rows.size()) {
        rows[row] = data;
        rewrite();
    }
    else {
        std::cerr << "ERROR! edit row data" << std::endl;
    }
}
binfile::~binfile() {
    if (file.is_open()) {
        file.close();
    }
}
void binfile::clear() {
    if (file.is_open()) {
        file.close();
    }
    file.open(name + ".bcf", std::ios::binary | std::ios::out | std::ios::trunc);
    if (file.is_open()) {
        file.close();
    }
    else {
        std::cerr << "ERROR! clear all" << std::endl;
    }
    file.open(name + ".bcf", std::ios::binary | std::ios::out | std::ios::in |
                                 std::ios::app);
    rows.clear();
    cols.clear();
    cf.clear();
}
/*void binfile::read() {
    cols.clear();
    rows.clear();
    file.seekg(0, std::ios::beg);
    int i = 0;
    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> tokens;
        size_t start = 0, end = 0;
        while ((end = line.find("\t", start)) != std::string::npos) {
            tokens.push_back(line.substr(start, end - start));
            start = end + 1;
        }
        if (i == 0) {
            tokens.push_back(line.substr(start));
            tokens.pop_back();
            cols = tokens;
            i++;
            continue;
        }
        tokens.push_back(line.substr(start));
        tokens.pop_back();
        rows.push_back(tokens);
    }
}*/
/*void binfile::read() {
    cols.clear();
    rows.clear();
    if (!file.is_open()) {
        file.open(name + ".bcf", std::ios::binary | std::ios::in);
        if (!file.is_open()) {
            //std::cerr << "ERROR! Cannot open " << name << std::endl;
            return;
        }
    }
    std::cout<<cf.size();
    file.seekg(0, std::ios::beg);
    file >> *this;
    std::cout<<cf.size();
    file.close();
}*/
void binfile::read() {
    if (file.is_open()) {
        cols.clear();
        rows.clear();
        //cf.clear();
        file.seekg(0, std::ios::beg);
        file >> *this;
        // Не закривати файл тут
    }
}
void binfile::output() {
    rewrite();
    if (cols.empty()) { std::cerr << "EMPTY!" << std::endl; }
    else {
        std::cout << "=";
        for (int i = 0; i < cols.size() * 10; i++)
            std::cout << "=";
        std::cout << std::endl;
        std::cout << "|";
        for (auto col : cols) {
            std::cout << std::setw(8) << col << " |";
        }
        std::cout << std::endl;
        std::cout << "=";
        for (int i = 0; i < cols.size() * 10; i++)
            std::cout << "=";
        std::cout << std::endl;
        for (auto row : rows) {
            std::cout << "|";
            for (auto data : row)
                std::cout << std::setw(8) << data << " |";
            std::cout << std::endl;
        }
        std::cout << "=";
        for (int i = 0; i < cols.size() * 10; i++)
            std::cout << "=";
    }
}

void binfile::clear_file() {
    if (file.is_open()) {
        file.close();
    }
    file.open(name + ".bcf", std::ios::binary | std::ios::out | std::ios::trunc);
    if (file.is_open()) {
        file.close();
    }
    else {
        std::cerr << "ERROR! clear f" << std::endl;
    }
    file.open(name + ".bcf", std::ios::binary | std::ios::out | std::ios::in | std::ios::app);
}

void binfile::clear_chache() {
    cols.clear();
    rows.clear();
    cf.clear();
}
binfile& binfile::operator--() {
    if (!rows.empty() && !cols.empty()) {
        rows.pop_back();
        rewrite();
    }
    return *this;
}
binfile& binfile::operator++() {
    if (!rows.empty()&&!cols.empty()) {
        std::vector<std::string> temp;
        for (int i = 0; i < cols.size(); i++) temp.push_back("-");
        rows.push_back(temp);
        rewrite();
    }
    return *this;
}
std::string binfile::get_name() {
    return this->name;
}
binfile::binfile(const binfile& file) {
    this->cols.clear();
    this->rows.clear();
    this->cf.clear();
    this->name = file.name;
    this->cols = file.cols;
    this->rows = file.rows;
    this->cf=file.cf;
    rewrite();
}
int binfile::get_cols_size() {
    return cols.size();
}
int binfile::get_rows_size() {
    return rows.size();
}
void binfile::close() {
    if (file.is_open()) {
        file.close();
    }
}
std::vector<std::string>& binfile::get_cols(){
    return this->cols;
}
std::vector<std::vector<std::string>>& binfile::get_rows(){
    return this->rows;
}
void binfile::set_name(std::string name) {
    this->name = name;
}
void binfile::set_cols(std::vector<std::string> c) {
    this->cols = c;
}
void binfile::set_rows(std::vector<std::vector<std::string>> r) {
    this->rows = r;
}
void binfile::set_cf(std::vector<cell_config>c){
    this->cf=c;
}

/*void binfile::push_conf(cell_config c){
    for(auto& f:this->cf){
        if(f==c){
            if(c.color!=f.color&&c.color!="#ffffff") f.color=c.color;
            if(c.fcol!=f.fcol&&c.fcol!="#000000") f.fcol=c.fcol;
            if(c.font!=f.font&&c.font!="Segoe UI") f.font=c.font;
            if(c.size!=f.size&&c.size!=0) f.size=c.size;
            return;
        }
    }
    this->cf.push_back(c);
    this->rewrite();
}*/

void binfile::push_conf(cell_config c) {

    for (auto &f : this->cf) {
        if (f == c) {
            if (c.color != f.color && c.color != "#ffffff")
                f.color = c.color;
            if (c.fcol != f.fcol && c.fcol != "#000000")
                f.fcol = c.fcol;
            if (c.font != f.font && c.font != "Segoe UI")
                f.font = c.font;
            if (c.size != f.size && c.size != 9)
                f.size = c.size;
            if (c.bold != f.bold)
                f.bold = c.bold;
            if (c.cursive != f.cursive)
                f.cursive = c.cursive;
            if (c.italic != f.italic)
                f.italic = c.italic;
            this->rewrite();
            return;
        }
    }

    this->cf.push_back(c);
    this->rewrite();

}

void binfile::push_conf(cell_config c, bool b, bool i, bool u) {

    for (auto &f : this->cf) {
        if (f == c) {
            if (c.color != f.color && c.color != "#ffffff")
                f.color = c.color;
            if (c.fcol != f.fcol && c.fcol != "#000000")
                f.fcol = c.fcol;
            if (c.font != f.font && c.font != "Segoe UI")
                f.font = c.font;
            if (c.size != f.size&&c.size!=9)
                f.size = c.size;
            if (c.bold != f.bold)
                f.bold = b;
            if (c.cursive != f.cursive)
                f.cursive = u;
            if (c.italic != f.italic)
                f.italic = i;
            this->rewrite();
            return;
        }
    }

    this->cf.push_back(c);
    this->rewrite();

}

std::vector<cell_config> binfile::get_config(){
    return this->cf;
}

void binfile::write_last(std::string l){
    std::ofstream f("last_file.txt", std::ios::trunc);
    f<<l;
    f.close();
}

std::string binfile::out_last(){
    std::ifstream f("last_file.txt");
    std::string l;
    f >> std::quoted(l);
    f.close();
    return l;
}

}
