fun String.wordsWith(substring: String, ignoreCase: Boolean = true) : List<String> {
	val result = mutableListOf<String>()
	val words = this.split(',', '.', ' ')
	for (word in words)
		if (word.contains(substring, ignoreCase)) result.add(word)
	return result
}

private fun String.isPalindrome() : Boolean {
	for (index in 0 until length)
		if (this[index] != this[length - 1 - index]) return false;
	return true
}

fun String.maxPalindrome() : String? {
	for (substringSize in length downTo 1) {
		for (startIndex in 0..(length - substringSize))
			substring(startIndex, startIndex + substringSize).let {
				if (it.isPalindrome()) return it
			}
	}
	return null
}

fun randomString(size: Int) : String =
	List(size) {
		(('A'..'Z') + ('a'..'z') + ('0'..'9') + ' ' + ',' + '.').random()
	}.joinToString("")

fun String.randomSubstring() : String = (0..length).random().let { start ->
	substring(start, (start..length).random())
}

private val data100 = randomString(100)
private val sub100 = data100.randomSubstring()
private val data1000 = randomString(1000)
private val sub1000 = data1000.randomSubstring()
private val data10000 = randomString(10000)
private val sub10000 = data10000.randomSubstring()

fun testFirst() {
	val prefix = "[String.wordsWith "
	measureTest(ITERATIONS =  1, WARM_COUNT = 0, LOG_PREFIX = "$prefix 100]") {
		data100.wordsWith(sub100)
	}
	measureTest(ITERATIONS =  1, WARM_COUNT = 0, LOG_PREFIX = "$prefix 1'000]") {
		data1000.wordsWith(sub1000)
	}
	measureTest(ITERATIONS =  1, WARM_COUNT = 0, LOG_PREFIX = "$prefix 10'000]") {
		data10000.wordsWith(sub10000)
	}
}

fun testSecond() {
	val prefix = "[String.maxPalindrome "
	measureTest(ITERATIONS =  1, WARM_COUNT = 0, LOG_PREFIX = "$prefix 100]") {
		data100.maxPalindrome()
	}
	measureTest(ITERATIONS =  1, WARM_COUNT = 0, LOG_PREFIX = "$prefix 1'000]") {
		data1000.maxPalindrome()
	}
	measureTest(ITERATIONS =  1, WARM_COUNT = 0, LOG_PREFIX = "$prefix 10'000]") {
		data10000.maxPalindrome()
	}
}

fun main() {
	println("Word. World. Worldwide, dog, apple".wordsWith("or"))

	"abanbabclkserhghlghjklkjhgvdbgbb .aw4ty48mya8wm rp984yp984a".maxPalindrome()?.let {
		println(
			"max palindrome = $it | length = ${it.length}"
		)
	}
	testFirst()
	testSecond()
}