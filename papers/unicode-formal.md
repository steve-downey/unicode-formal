---
title: Functions and Constants for Unicode Classification and Parsing
document: D0000R0
date: today
audience:
  - None
author:
  - name: Steve Downey
    email: <sdowney@gmail.com>, <sdowney2@bloomberg.net>

toc: false
---

# Abstract
Add functions and contstants useful for parsing and interpreting Unicode data based on their formal properties.

# Comparison table

::: cmptable

### Before
```cpp
 if ((codepoint & 0xfffff800) == 0xd800) {
 // ...
 }
 ```

### After
```cpp
if (std::uc::is_surrogate(codepoint)) {
// ...
}
```

:::





---
---
