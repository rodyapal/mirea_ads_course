fun String.wordsWith(substring: String, ignoreCase: Boolean = true) : List<String> {
	val result = mutableListOf<String>()
	val words = this.split(',', '.', ' ')
	for (word in words)
		if (word.contains(substring, ignoreCase)) result.add(word)
	return result
}

fun main() {
	println("Hello World. This world is beautiful, Worldwide.".wordsWith("orl"))
}