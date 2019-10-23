int pairs(int k, vector<int> arr) {

    int counter = 0;

    if (arr.size() <= 1)
        return counter;

    sort(arr.begin(), arr.end());

    for(int i = arr.size() - 1;i > 0;i--){
        auto &a = arr[i];

        for(int j = i - 1; j >=0; j--){
            auto &b = arr[j];

            if (a - b == k) {
                counter++;
            }
            else if (a - b > k)
                break;
        }
    }

    return counter;
}