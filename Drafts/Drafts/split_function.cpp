#include <vector>
#include <functional>
#include <algorithm>

using int_vector = std::vector<int>;
using index_pair = std::pair<unsigned, unsigned>;

index_pair split(int_vector& a, int p)
{
  int_vector before_p;
  int_vector after_p;
  unsigned count_p = 0;

  for (int i : a)
  {
    if (i < p)
    {
      before_p.push_back(i);
    }
    else if (i > p)
    {
      after_p.push_back(i);
    }
    else ++count_p;
  }

  int_vector res(before_p);
  res.insert(res.end(), count_p, p);

  res.insert(
    res.end(),
    std::make_move_iterator(after_p.begin()),
    std::make_move_iterator(after_p.end())
  );

  //return std::make_pair(before_p.size(), before_p.size()+count_p-1);
  auto iters = std::equal_range(res.begin(), res.end(), p);

  return std::make_pair(
    std::distance(res.begin(), iters.first),
    std::distance(res.begin(), iters.second)-1);
}
