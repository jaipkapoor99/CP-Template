# CP-Template

A **grandmaster-level C++20 Competitive Programming Template** designed for speed, efficiency, and versatility. This template incorporates modern C++20 features, advanced debugging tools, fast I/O, randomization, modular arithmetic helpers, and much more.

---

## 🚀 Features

- **C++20 Ready:** Uses the latest language features for concise and powerful code.
- **Fast Input/Output:** Macros and settings for lightning-fast I/O.
- **Rich Type Aliases:** Shortcuts for common data structures (vectors, pairs, maps, etc.).
- **Advanced Macros:** For iteration, container manipulation, and readability.
- **Powerful Debugging:** Local-only, source-aware, colorized, and non-intrusive debug macros.
- **Modern STL Utilities:** Ranges, spans, bit-manipulation helpers, and more.
- **Random Number Generator:** Secure and fast for randomized algorithms.
- **Policy-Based Data Structures:** Order-statistics set/map via GNU PBDS.
- **Safe Hashing:** Custom hash for unordered containers to avoid collisions.
- **Modular Arithmetic Helpers:** Fast, reusable modint class for mod calculations.
- **Timer Utility:** For quick performance profiling.
- **Flexible Input/Output:** Variadic read/print, tuple and span support.
- **Ready for Expansion:** Easily add your own snippets and helpers.

---

## 🛠️ How to Use

1. **Copy** `template.cpp` into your contest workspace.
2. **Compile** with C++20 support (e.g. `g++ -std=c++20 -O2 template.cpp -o solution`).
3. **Enable Debugging (Optional):**  
   Locally debug with advanced output by compiling with `-DLOCAL`:
   ```
   g++ -std=c++20 -O2 -DLOCAL template.cpp -o solution
   ```
4. **Start Coding:**  
   Use the built-in aliases, macros, and helpers. See the template’s comments for usage examples.

---

## 📦 Main Components

| Feature            | Macro/Type/Alias          | Description                                    |
|--------------------|--------------------------|------------------------------------------------|
| Fast I/O           | `FASTINOUT`              | Fast cin/cout setup                            |
| Type Aliases       | `ll`, `vll`, `pii`, etc. | Shortforms for common types                    |
| Ranges             | `all(v)`, `rall(v)`      | Easy container manipulation                    |
| Loop Macros        | `f(i,s,e)`, `cf(i,s,e)`  | Fast for-loop patterns                         |
| Debugging          | `DEBUG(...)`             | Advanced, local-only, colorized debug output   |
| Random Generator   | `rand_ll(l, r)`          | Uniform random in [l, r]                       |
| PBDS               | `os<T>`                  | Ordered set with order-statistics              |
| Modular Arithmetic | `Mint<MOD>`              | Handy class for mod calculations               |
| Timer              | `Timer`                  | Profile code segments                          |
| Safe Hashing       | `custom_hash`            | For unordered containers                       |
| Math Utils         | `gcd`, `lcm`, `ceildiv`  | Common math tools                              |

---

## 📝 Example

```cpp
#include "template.cpp"

void solve() {
    int n; read(n);
    vi a(n); read(a);
    DEBUG(n, a);
    UNIQUE(a);
    print("Size after unique:", sz(a));
}

int main() {
    FASTINOUT;
    int t = 1;
    read(t);
    while (t--) solve();
    return 0;
}
```

---

## 🧑‍💻 For Beginners & Grandmasters

- **Beginners:**  
  Simple to use—just focus on writing your algorithm!
- **Grandmasters:**  
  All the power tools are here when you need them (PBDS, bit hacks, modular, advanced debug).

---

## 🏆 Credits

- Inspired by templates from "tourist", "Benq", and many top CPers.
- Maintained by [jaipkapoor99](https://github.com/jaipkapoor99).

---

## 📣 Contributions

Feel free to fork or suggest improvements!

---

## 🔗 License

MIT License

---