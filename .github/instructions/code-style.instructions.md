---
applyTo: '*.cpp,*.h, *.hpp
---
If asked to generate file content, always add a comment at the top of the file indicating that it was generated by Copilot. For example:
- for C++ files (*.cpp, *.h, *,hpp)
// Generated by copilot on behalf of Andrii

When generating code for method always add a description of what method takes as arguments and what it returns. For example:
```cpp
// Adds two integers and returns the result
// @param a First integer to add
// @param b Second integer to add
// @return The sum of a and b
int Add(int a, int b) {
    return a + b;
}
```