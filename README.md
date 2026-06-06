**24-Round DES — Data Encryption Standard**

A modified implementation of the Data Encryption Standard (DES) algorithm
extended from the original 16 rounds to 24 rounds, with a comparative analysis
of time complexity, space complexity, and security implications.

> C++ implementation — includes both encryption and decryption.

---

**Project Overview**

| | |
|---|---|
| **Project Title** | 16-Round vs 24-Round DES Comparative Analysis |
| **Language** | C++ |
| **Course** | Cryptography |

**Key Findings**

| | |
|---|---|
| **Time Complexity** | O(1) per block for both versions |
| **Speed Difference** | 24-round is ~2.4x slower per block |
| **Memory — 16 Rounds** | ~6.4 KB |
| **Memory — 24 Rounds** | ~17 KB |
| **Key Size** | 56 bits (unchanged in both versions) |
| **Block Size** | 64 bits (unchanged in both versions) |

---

**Algorithm Overview**

| **Operation** | **Purpose** | **Bit Size** |
|---|---|---|
| Initial Permutation (IP) | Reorders input bits | 64 bits |
| Key Expansion (PC1/PC2) | Generates subkeys per round | 56 → 48 bits |
| E-Expansion | Expands R half for XOR | 32 → 48 bits |
| S-Box Substitution | Non-linear transformation (8 boxes) | 48 → 32 bits |
| P-Permutation | Diffusion after S-boxes | 32 bits |
| Final Permutation (FP) | Inverse of IP | 64 bits |

---

**Time Complexity Comparison**

| **Phase** | **16 Rounds** | **24 Rounds** |
|---|---|---|
| Key Generation | 1,720 operations | 5,144 operations |
| Round Function f(R,K) | ~3,456 operations | ~6,336 operations |
| IP + FP + Split/Combine | ~640 operations | ~640 operations |
| **Total per block** | **~5,816 operations** | **~14,040 operations** |
| **Big-O Complexity** | **O(1)** | **O(1)** |

---

**Space Complexity Comparison**

| **Memory Type** | **16 Rounds** | **24 Rounds** |
|---|---|---|
| Global Tables | ~4,128 B | ~4,544 B |
| Stack Memory | ~863 B | ~7,384 B |
| **Total** | **~6.4 KB** | **~17 KB** |
| **Complexity** | **O(1)** | **O(1)** |

---

**Security Analysis**

| **Attack Type** | **16 Rounds** | **24 Rounds** | **Result** |
|---|---|---|---|
| Brute Force | 2^56 key tries | 2^56 key tries | No change |
| Differential Cryptanalysis | Needs ~2^47 pairs | Needs more pairs | Improved |
| Linear Cryptanalysis | Needs ~2^43 msgs | Needs more msgs | Improved |
| Avalanche Effect | Achieved by round 6 | Achieved by round 6 | Same |

---

**Overall Comparison**

| **Aspect** | **16 Rounds (Original)** | **24 Rounds (Modified)** |
|---|---|---|
| Time per block | ~5,800 operations | ~14,000 operations |
| Execution speed | Baseline | ~2.4x slower |
| Memory usage | ~6.4 KB | ~17 KB |
| Time complexity | O(1) per block | O(1) per block |
| Space complexity | O(1) | O(1) |
| Key size | 56 bits | 56 bits |
| Block size | 64 bits | 64 bits |
| Differential cryptanalysis | Moderate | Better |
| Linear cryptanalysis | Moderate | Better |
| Overall security | Weak (deprecated) | Slightly better, still weak |

---

**How to Compile & Run**

```cpp
// Compile
g++ 24Round-DES.cpp -o des

// Run
./des
```

**Input Format**

| | |
|---|---|
| **Plaintext** | 8 characters (64 bits) |
| **Key** | 8 characters (64 bits) |
| **Output** | Ciphertext + Decrypted text |

---

**Note**

| | |
|---|---|
| **DES Status** | Deprecated in 2001 |
| **Replacement** | AES-128/256 recommended for production use |
| **Purpose** | Academic study of Feistel cipher round extension |

---

**License**

Academic project — all documentation is original work produced by the team.
