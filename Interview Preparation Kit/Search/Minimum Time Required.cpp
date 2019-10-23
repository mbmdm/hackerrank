long mlower_bound(std::vector<long>& m, long goal, long l, long r)
{
    if (l > r) return l;

    long mid = (l + r) / 2; 
    
    unsigned long sum = 0;

    for(size_t i = 0; i < m.size(); i++)
        sum += mid/m[i];

    if (sum >= goal)
        return mlower_bound(m, goal, l, mid-1);
    else 
        return mlower_bound(m, goal, mid+1, r);
}

long minTime(vector<long> machines, long goal) {
    
    long end = std::numeric_limits<long>::max();
    return mlower_bound(machines, goal, 0, end);

}