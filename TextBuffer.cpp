#include "TextBuffer.hpp"

TextBuffer::TextBuffer() : data(), cursor(data.begin()), row(1), column(0), index(0) {}

bool TextBuffer::forward() {
    if (is_at_end()) {
        return false;
    } else if (*cursor == '\n') {
        cursor++;
        column = 0;
        index++;
        row++;
        return true;
    } else {
        cursor++;
        column++;
        index++;
        return true;
    }
}

bool TextBuffer::backward() {
    if (row == 1 && column == 0){
      return false;
    }
    if (column == 0)
    { 
      cursor--;
      row--;
      index--;
      column = compute_column();
      
    }
    else {
      cursor--;
      column--;
      index--;
    }

    return true;
}

void TextBuffer::insert(char c){
    cursor = data.insert(cursor, c);
    forward();
}

bool TextBuffer::remove(){
    if (cursor == data.end()) {
        return false;
    }

    cursor = data.erase(cursor);

    //if curser is a newline
    if (cursor != data.end() && *cursor == '\n') {
        row--;
        column = compute_column();
    } else {
        if (*cursor != '\n') {
            --index;
        }
    }
    return true;
  }

void TextBuffer::move_to_row_start(){
    while(column != 0) {
        backward();
    }
}

void TextBuffer::move_to_row_end() {
    while (!is_at_end() && *cursor != '\n') {
        forward();
    }
}

void TextBuffer::move_to_column(int new_column){
    move_to_row_start();

    // Move the cursor to the specified column
    while(!is_at_end() && column < new_column && *cursor != '\n') {
        forward();
    }
}

bool TextBuffer::up(){
    if (row == 1) {
        return false;
    }

    int currentColumn = column;
    move_to_row_start();

    backward();

    if (column < currentColumn) {
        return true;
    } else {
        move_to_column(currentColumn);
    }
    return true;
  }

bool TextBuffer::down(){
    //store orig column
    int myrow = row;
    int currentColumn = column;
    move_to_row_end();
    forward();

    move_to_column(currentColumn);
    return row != myrow;
}

bool TextBuffer::is_at_end() const {
    return cursor == data.end();
  }

char TextBuffer::data_at_cursor() const{
    return *cursor;
}

int TextBuffer::get_row() const {
    return row;
  }
  
int TextBuffer::get_column() const {
    return column;
  }
  
int TextBuffer::get_index() const{
    return index;
  }  

int TextBuffer::size() const{
    return data.size();
  }

std::string TextBuffer::stringify() const{
    return std::string(data.begin(), data.end());
}


int TextBuffer::compute_column() const {
    Iterator it = cursor;
    int tempColumn = 0;
    if(it != data.begin()) {
    while (it != data.begin() && *--it != '\n') {
        ++tempColumn;
    }
    }

    return tempColumn;
}