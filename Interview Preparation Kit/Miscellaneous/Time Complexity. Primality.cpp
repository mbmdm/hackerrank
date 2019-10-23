string primality(int n) {

    if (n == 1)
        return "Not prime";

    static vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 
                                29, 31, 37, 41, 43, 47, 53, 59, 
                                61, 67, 71, 73, 79, 83, 89, 97, 101};
    
    bool flag = std::binary_search(primes.begin(), primes.end(), n);
    
    if (flag)
        return "Prime";

    for (int i = 2; i <= sqrt(n); i++) {   
        if (n % i == 0)
            return "Not prime";
    }

    return "Prime";
}