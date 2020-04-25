vector <int> get_zarray(string &text) {
    int len = text.size();
    vector <int> z(len);
    z[0] = 0;
    int lt = 0;
    int rt = 0;
    for (int k = 1; k < len; k++) {
        if (k > rt) {
            int i = 0;
            while (i + k < len && text[i + k] == text[i]) {
                  i++;
            }
            z[k] = i;
            lt = k;
            rt = k + z[k] - 1;
        }
        else {
            int p = k - lt;
            int right_part_len = rt - k + 1;
            if (z[p] < right_part_len) {
                z[k] = z[p];
            }
            else {
                int i = rt + 1;
                while (i < len && text[i] == text[i - k]) {
                        i++;
                }
                z[k] = i - k;
                lt = k;
                rt = k + z[k] - 1;
            }
        }
    }
    return z;
}
