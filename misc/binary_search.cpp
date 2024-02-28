int bs1(auto check, int l, int r) {
    while (l < r) {
        int mid = (l + r)/2;
        if (check(mid)) r = mid;
        else l = mid+1;
    }
    return l;
}

int bs2(auto check, int l, int r) {
    while (l < r) {
        int mid = (l + r + 1)/2;
        if (check(mid)) l = mid;
        else r = mid-1;
    }
    return l;
}