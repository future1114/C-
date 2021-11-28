#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// 定义结构体,保存一次会议的相关信息
typedef struct Meeting {
    int id;   // 编号
    int start;   // 开始时间
    int end;   // 结束时间
};

// 定义排序规则
bool cmp(Meeting a, Meeting b) {
    if (a.end < b.end)
        return true;
    else if (a.end > b.end)
        return false;
    // 如果结束时间相等，就选开始时间最晚的
    else
        return a.start > b.start;
}

// 初始化，将所有会议信息保存到数组中并返回
vector<Meeting> InitMeetings() {
    int n, start, end;
    cout << "请输入会议总数：" << endl;
    cin >> n;
    cout << "请输入" << n << "个会议的开始时间和结束时间(以空格分开)：" << endl;
    vector<Meeting> meets(n);
    for (int i = 0; i < n; i++) {
        cin >> start >> end;
        // 将第i次会议的相关信息存入结构体
        meets[i].id = i + 1;
        meets[i].start = start;
        meets[i].end = end;
    }
    return meets;
}

// 按贪心算法安排会议行程，返回安排好的会议的编号
vector<int> ArrangeMeetings(vector<Meeting>& meets) {
    // 对会议按结束时间进行从小到大排序
    std::sort(meets.begin(), meets.end(), cmp);
    // 记录当前被选中会议的结束时间
    int last = 0;
    // 用来保存已经选中会议的编号
    vector<int> res;

    for (int i = 0; i < meets.size(); i++) {
        if (meets[i].start >= last) {
            // 满足要求，可以选中
            res.push_back(meets[i].id);
            // 更新last
            last = meets[i].end;
        }
    }
    return res;
}

int main() {
    // 测试
    vector<Meeting> meets = InitMeetings();
    vector<int> res = ArrangeMeetings(meets);
    cout << "\n会议行程安排如下：" << endl;
    for (auto id : res) {
        cout << id << " ";
    }
}
