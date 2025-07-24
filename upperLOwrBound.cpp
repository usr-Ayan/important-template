✅ Correct meanings (from C++ STL):
🔹 std::lower_bound(begin, end, x)
Finds the first element ≥ x

That means it gives the smallest index where value is not less than x

🔹 std::upper_bound(begin, end, x)
Finds the first element > x

That means it gives the smallest index where value is strictly greater than x

💡 So in simple terms:

Function	What it returns
lower_bound(x)	First element that is ≥ x
upper_bound(x)	First element that is > x
