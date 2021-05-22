fun main() {
	println("+7/-9 3*2 5 = ${"+7/-9 3*2 5".eval()}")
	println("a+b/c+d+e-f/m*k in prefix notation: ${"a+b/c+d+e-f/m*k".toPrefix()}")
	println("a+(45-a(x)*(b-c)) by close parentheses: ${"a+(45-a(x)*(b-c))".getParenthesesIndexes(byOpen = false)}")
	println("a+(45-a(x)*(b-c)) by open parentheses: ${"a+(45-a(x)*(b-c))".getParenthesesIndexes()}")
}