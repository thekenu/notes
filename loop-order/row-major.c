int main() {
  static int big_2d_array[10000][10000];
  for (int i = 0; i < 10000; i++) {
    for (int j = 0; j < 10000; j++) {
      big_2d_array[i][j] = 0; 
    }
  }
}
