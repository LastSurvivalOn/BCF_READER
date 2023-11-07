#ifndef CUSTFILE_H
#define CUSTFILE_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <QFont>
#include <QColor>
#include <sstream>
namespace uni
{

struct cell_config{
    int row, col;
    std::string font, fcol, color;
    int size;
    bool bold, cursive, italic;
    bool operator==(const cell_config& other) const {
        return row == other.row && col == other.col;
    }
    cell_config(){
        //row=0, col=0;
        font="Segoe UI";
        fcol="#000000";
        color="#ffffff";
        size=9;
        bold=0;
        cursive=0;
        italic=0;
    }
};

class binfile {
    std::string name;
    std::fstream file;
    std::vector<std::string> cols;
    std::vector<std::vector<std::string>> rows;
    std::vector<cell_config> cf;
public:
    binfile(std::string);
    binfile(const binfile& file);
    void new_col(std::string);
    void add_row(std::vector<std::string>);
    void add_row(std::string, int);
    void delete_row(int);
    void delete_col(int);
    void rename_col(std::string, int);
    void edit_row(int, int, std::string);
    void edit_row(int, std::vector<std::string>);
    void rewrite();
    void read();
    void clear();
    void clear_file();
    ~binfile();
    void output();
    void clear_chache();
    binfile& operator--();
    binfile& operator++();
    friend std::ostream& operator<<(std::ostream&, binfile&);
    std::string get_name();
    bool operator==(const binfile& f)const {
        if (this->name == f.name)
            return 1;
        else return 0;
    }
    int get_cols_size();
    int get_rows_size();
    void close();
    std::vector<std::string>& get_cols();
    std::vector<std::vector<std::string>>& get_rows();
    friend std::ostream& operator<<(std::ostream& os, binfile& f) {
        f.clear_file();
        os << f.get_cols_size() << '\n';
        os << f.get_rows_size() << '\n';
        if (f.get_cols_size() == 0) 		os << 'f';
        else {
            os << 'c';
            os<<'\n';
            for (int i = 0; i < f.get_cols_size(); i++)
            {
                os << f.get_cols()[i];
                if (i != f.get_cols_size() - 1) 	os << '\t';
                else os << '\n';
            }
            for (int i = 0; i < f.get_rows_size(); i++)
            {
                for (int j = 0; j < f.get_cols_size(); j++)
                {
                    os << f.get_rows()[i][j];
                    if (j != f.get_cols_size() - 1) 	os << '\t';
                    else os << '\n';
                }
            }
            if(f.cf.size()==0) os<<'p';
            else {os<<'i';
                os<<'\n';
                int n=f.cf.size();
                os<<n;
                os<<'\n';
                for(int i=0; i<n; i++){
                os << f.cf[i].row << '\t' << f.cf[i].col << '\t' << "\"" << f.cf[i].font << "\"" << '\t' << f.cf[i].size << '\t' << f.cf[i].fcol << '\t' << f.cf[i].color<< '\t' << f.cf[i].bold<< '\t' << f.cf[i].italic<< '\t' << f.cf[i].cursive;
                os<<'\n';
                std::cout<<"writ"<<f.cf[i].row<<' '<<f.cf[i].col<<' '<<f.cf[i].font<<' '<<f.cf[i].size<<' '<<f.cf[i].fcol<<' '<<f.cf[i].color<<std::endl;
                }
            }
        }
        return os;
    }

    /*friend std::istream& operator>>(std::istream& is, binfile& f) {
        int colsSize, rowsSize, num;
        is >> colsSize >> rowsSize;

        char marker;
        is >> marker;
        std::vector<std::string> cols;
        std::vector<std::vector<std::string>> rows;
        std::vector<cell_config> cf;
        if (marker != 'f') {

            for (int i = 0; i < colsSize; i++) {
                std::string col;
                is >> col;
                cols.push_back(col);
            }

            for (int i = 0; i < rowsSize; i++) {
                std::vector<std::string> row;
                for (int j = 0; j < colsSize; j++) {
                    std::string cell;
                    is >> cell;
                    row.push_back(cell);
                }
                rows.push_back(row);
            }
            char m;
            is >> m;
            if(m!='p'){
                is >> num;
                for(int i=0; i<num; i++){
                    int row, col, size;
                    std::string font, fcol, color;
                    is>>row>>col>>font>>size>>fcol>>color;

                    cell_config cell;
                    cell.col=col;
                    cell.row=row;

                    // Перевіряємо та заповнюємо параметри за замовчуванням, якщо вони відсутні
                    cell.font = (font.empty() ? "-" : font);
                    cell.size = (size == 0 ? 0 : size);
                    cell.fcol = (fcol.empty() ? "-" : fcol);
                    cell.color = (color.empty() ? "-" : color);

                    cf.push_back(cell);
                }
            }
            f.set_cols(cols);
            f.set_rows(rows);
            f.set_cf(cf);
        }
        else if (marker == 'f') {
            f.clear_chache();
        }
        std::cout<<cf.size();
        return is;
    }*/
    friend std::istream& operator>>(std::istream& is, binfile& f) {
        int colsSize, rowsSize, num;
        is >> colsSize >> rowsSize;

        char marker;
        is >> marker;
        std::vector<std::string> cols;
        std::vector<std::vector<std::string>> rows;
        std::vector<cell_config> cf;
        if (marker != 'f') {
            for (int i = 0; i < colsSize; i++) {
                std::string col;
                is >> col;
                cols.push_back(col);
            }

            for (int i = 0; i < rowsSize; i++) {
                std::vector<std::string> row;
                for (int j = 0; j < colsSize; j++) {
                std::string cell;
                is >> cell;
                row.push_back(cell);
                }
                rows.push_back(row);
            }

            char m;
            is >> m;
            if (m != 'p') {
                /*is >> num;
                is.ignore();
                for(int i = 0; i < num; i++) {
                int row, col, size;
                std::string font, fcol, color;

                std::string configLine="\t";
                std::getline(is, configLine);

                std::istringstream configStream(configLine);
                configStream >> row >> col >> font >> size >> fcol >> color;

                cell_config cell;
                cell.col = col;
                cell.row = row;
                cell.font = font;
                cell.size = size;
                cell.fcol = fcol;
                cell.color = color;
                cf.push_back(cell);
                std::cout<<"read"<<cell.col<<" "<<cell.row<<" "<<cell.font<<" "<<cell.size<<" "<<cell.fcol<<" "<<cell.color<<std::endl;
                }*/
                is >> num;
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                for (int i = 0; i < num; i++) {
                int row, col, size;
                std::string font, fcol, color;
                bool bold, cursive, italic;
                is >> row >> col;

                is >> std::quoted(font);

                is >> size >> fcol >> color>>bold>>italic>>cursive;

                cell_config cell;
                cell.col = col;
                cell.row = row;
                cell.font = font;
                cell.size = size;
                cell.fcol = fcol;
                cell.color = color;
                cell.bold=bold;
                cell.italic=italic;
                cell.cursive=cursive;
                cf.push_back(cell);
                }
            }

            f.set_cols(cols);
            f.set_rows(rows);
            f.set_cf(cf);
        }
        else if (marker == 'f') {
            f.clear_chache();
        }
        //std::cout << cf.size();
        return is;
    }
    void set_name(std::string);
    void set_cols(std::vector<std::string>);
    void set_rows(std::vector<std::vector<std::string>>);
    void set_cf(std::vector<cell_config>);
    void push_conf(cell_config);
    std::vector<cell_config> get_config();
    void push_conf(cell_config c, bool b, bool i, bool u);
    void write_last(std::string);
    std::string out_last();
};
class data {
    std::vector<std::string> dat;
    int number;
public:
    std::vector<std::string> get_data();
    data(int, std::string);
    data();
    void fill(int);
};

}

#endif // CUSTFILE_H
