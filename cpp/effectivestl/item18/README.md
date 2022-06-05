# Item 18: Avoid using vector<bool>

vector<bool> is not a container because it doesn't meet some container requirement.

Alternatives for vector<bool> is bitset and deque<bool>.
