#include "TextBuffer.hpp"

TextBuffer::TextBuffer() : data(), cursor(data.begin()), row(1), column(0), index(0) {}

bool TextBuffer::forward() {
    if (cursor == data.end()) {
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
    if (cursor == data.begin()){
      return false;
    }
    if (column == 0){
      --cursor;
      row--;
      index--;
      column = compute_column();
    }
    else {
      --cursor;
      column--;
      index--;
    }

    return true;
}


void TextBuffer::insert(char c){
    if (c == '\n'){
        data.insert(cursor, c);
        //cursor = data.insert(cursor, c);
        row++;
        column = 0;
        ++cursor;
    }
    else if (cursor == data.end()) {
        data.push_back(c);
        cursor = data.end();
        column++;
    }
    else {
        cursor = data.insert(cursor, c); 
        column++; 
        ++cursor;
    }

    index++;
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

void TextBuffer::move_to_row_start() {
    
    while (cursor != data.begin() && *(--cursor) != '\n') {
        --index;
    }

    
    if (cursor != data.begin()) {
        ++cursor;
        ++index; 
    }

    column = 0;
}


void TextBuffer::move_to_row_end() {
    if (cursor == data.end()) {
        return; 
    }

    while (cursor != data.end() && *cursor != '\n') {
        cursor++;
        column++;
        
    }
}

void TextBuffer::move_to_column(int new_column){
    move_to_row_start();

    // Move the cursor to the specified column
    for (int i = 0; i < new_column; ++i) {
        forward();
    }
}

//compute column conflict of interest in up and backwards
bool TextBuffer::up(){
    if (row == 1) {
        return false;
    }

    int currentColumn = column;
    move_to_row_start();

    backward();

    if (column < currentColumn) {
        move_to_row_end();

    } else {
        move_to_column(currentColumn);
    }
    return true;
  }

bool TextBuffer::down(){
    if (cursor == data.end()) {
        return false; 
    }

    //store orig column
    int currentColumn = column;
    move_to_row_end();

    if (cursor != data.end()) {
        ++cursor;
        ++row;
    }

    move_to_row_end();

    if (compute_column() < currentColumn) {
        column = compute_column();
    } else {
        move_to_column(currentColumn);
    }

    return true;
}

bool TextBuffer::is_at_end() const {
    return index == this->size();
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
    if (cursor == data.end()){
      return size();
    } 
    else {
      return index;
    }
  }  

int TextBuffer::size() const{
    return data.size();
  }

std::string TextBuffer::stringify() const{
    return std::string(data.begin(), data.end());
}


// int TextBuffer::compute_column() const {
//     Iterator it = cursor;
//     int tempColumn = 0; 
//     while (it != data.begin() && *(--it) != '\n') {
//         ++tempColumn;
//     }
//     if (*it != '\n') {
//         ++tempColumn;
//     }
//     return tempColumn;
// }

int TextBuffer::compute_column() const {
    Iterator it = cursor;
    int tempColumn = 0;

    while (it != data.begin() && *(--it) != '\n') {
        ++tempColumn;
    }

    if (it == data.begin()) {
        return tempColumn;
    }
    if (*it != '\n') {
        ++tempColumn;
    }

    return tempColumn;
}
