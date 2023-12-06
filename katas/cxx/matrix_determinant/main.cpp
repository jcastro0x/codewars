#include <gtest/gtest.h>

#include <vector>
#include <cstdint>

typedef std::vector<std::vector<int64_t>> matrix_t;

int64_t determinant(const matrix_t& m)
{
    const size_t n = m.size();

    int64_t det = 0;

    // Base case of a 1x1 matrix
    if (n == 1) return m[0][0];

    // Base case of a 2x2 matrix
    if (n == 2) return m[0][0] * m[1][1] - m[0][1] * m[1][0];

    // When n > 2, recursively calculate determinant
    int sign = 1;
    for (int i = 0; i < n; i++)
    {
        // Get matrix of minors
        matrix_t sub_m(n - 1, std::vector<int64_t>(n - 1));
        for (int j = 1; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (k < i) sub_m[j-1][k] = m[j][k];
                else if (k > i) sub_m[j-1][k-1] = m[j][k];
            }
        }

        // Calculate determinant
        det += sign * m[0][i] * determinant(sub_m);
        sign = -sign;
    }
    return det;
}

TEST(Codewars, matrix_determinant)
{
    EXPECT_EQ(determinant(matrix_t{
        {1}
    }), 1);

    EXPECT_EQ(determinant(matrix_t{
        {1, 3},
        {2, 5}
    }), -1);

    EXPECT_EQ(determinant(matrix_t{
        {2, 5, 3},
        {1, -2, -1},
        {1, 3, 4}
    }), -20);
}
