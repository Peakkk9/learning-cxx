#include "../exercise.h"
#include <algorithm>
#include <string>
#include <vector>

// READ: `std::transform` <https://zh.cppreference.com/w/cpp/algorithm/transform>
/**
 * 【std::transform 加工厂】
 * 1. 作用：Map 操作，将 Input 经过 Func 处理后存入 Output。
 * 2. 关键参数：
 * - InputRange: 输入的头尾迭代器。
 * - OutputIter: 写入的起始位置。
 * - UnaryOp: 接收 1 个参数，返回加工后的值。
 * 3. 常见用法：
 * - 原地修改：OutputIter 传入 Input.begin()。
 * - 存入新容器：配合 std::back_inserter(vec)。
 * 4. 注意：如果不使用 back_inserter，目标容器必须有足够的 size。
 */
// READ: `std::vector::begin` <https://zh.cppreference.com/w/cpp/container/vector/begin>

int main(int argc, char **argv) {
    std::vector<int> val{8, 13, 21, 34, 55};
    // TODO: 调用 `std::transform`，将 `v` 中的每个元素乘以 2，并转换为字符串，存入 `ans`
    std::vector<std::string> ans(val.size());
    std::transform(val.begin(),val.end(),ans.begin(),
                    [](int x){ return std::to_string(x*2); });
    ASSERT(ans.size() == val.size(), "ans size should be equal to val size");
    ASSERT(ans[0] == "16", "ans[0] should be 16");
    ASSERT(ans[1] == "26", "ans[1] should be 26");
    ASSERT(ans[2] == "42", "ans[2] should be 42");
    ASSERT(ans[3] == "68", "ans[3] should be 68");
    ASSERT(ans[4] == "110", "ans[4] should be 110");
    return 0;
}
