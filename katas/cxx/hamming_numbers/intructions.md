https://www.codewars.com/kata/526d84b98f428f14a60008da/train/cpp

A Hamming number is a positive integer of the form 2<sup>i</sup>3<sup>j</sup>5<sup>k</sup>, for some non-negative 
integers i, j, and k.

Write a function that computes the nth smallest Hamming number.

Specifically:

- The first smallest Hamming number is 1 = 2<sup>0</sup>3<sup>0</sup>5<sup>0</sup>
- The second smallest Hamming number is 2 = 2<sup>1</sup>3<sup>0</sup>5<sup>0</sup>
- The third smallest Hamming number is 3 = 2<sup>0</sup>3<sup>1</sup>5<sup>0</sup>
- The fourth smallest Hamming number is 4 = 2<sup>2</sup>3<sup>0</sup>5<sup>0</sup>
- The fifth smallest Hamming number is 5 = 2<sup>0</sup>3<sup>0</sup>5<sup>1</sup>
- The 20 smallest Hamming numbers are given in the Example test fixture.

Your code should be able to compute the first `5 000` ( LC: `400`, Clojure: 2 `000`, Haskell: `12 691`, NASM, C, D, C++, 
Go and Rust: `13 282` ) Hamming numbers without timing out.
