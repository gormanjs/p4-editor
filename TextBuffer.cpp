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
        column++;
        return true;
    }
}

bool TextBuffer::backward() {
    if (cursor == data.begin()){
      return false;
    }
    --cursor;

    if (*cursor == '\n'){
      row--;
      column = compute_column();
    }
    else {
      column--;
    }

    return true;
}

//issue here
void TextBuffer::insert(char c){
    data.insert(cursor, c);

    if (c == '\n'){
      //move to next row
      row++;
      column = 0;
    }
    if (cursor == data.end()) {
        // Insert the character at the end of the buffer
        data.push_back(c);
        cursor = data.end();
    }
    else {
      column++;
    }

    //update position
    index++;
}

bool TextBuffer::remove(){
    if (cursor == data.end()){
      return false;
    }

    cursor = data.erase(cursor);

    // if the end of buffer or end of line
    if (cursor != data.end() && *cursor == '\n'){
      row--;
      column = compute_column();
    }
    else {
      column--;
    }
    index--;
    return true;
  }

void TextBuffer::move_to_row_start(){
    column = 0;
}

void TextBuffer::move_to_row_end() {
    if (cursor == data.end()){
      return;
    }

    while (*cursor != '\n' && cursor != data.end()){
      index++;
      row++;
      column++;
    }

  }

void TextBuffer::move_to_column(int new_column){
    assert(new_column >= 0);

    if (column < new_column){
      move_to_row_end();
    }

    else {
      int amount = column - new_column;
      for (int i = 0; i < amount; i++){
        backward();
      }
    }
}

bool TextBuffer::up(){
    if (row == 1){
      return false;
    }

    //***This may cause issue
    //compute previous row size
    move_to_row_start();
    backward();
    int prevRowLength = compute_column();

    //compare
    if (prevRowLength < column){
      row--;
      move_to_row_end();
    }
    else {
      row--;
      move_to_column(column);
    }
    return true;
  }

bool TextBuffer::down(){
    if (is_at_end()){
      return false;
    }
    //i see what ur trying to do. yea just need to find a diff way
   while (*cursor != '\n') {
        forward();
    }
    forward();

    row++;

    int nextRowLength = compute_column();

    if (nextRowLength < column) {
        // If next line is shorter, move to its end
        move_to_row_end();
    } else {
        // Otherwise, move to the same column
        move_to_column(column);
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


int TextBuffer::compute_column() const {
    Iterator it = cursor;
    int tempColumn = 0;
    while (it != data.begin() && *(--it) != '\n'){
      tempColumn++;
    }
    return tempColumn;
}
