fun List<Int>.countEven(): Int {
	var even = 0
	for (item in this)
		if (item % 2 == 0) even++
	return even
}

fun main() {
	println(123411.digitalRoot())
	println(123411.digitalRootIterative())
	println(123411.digitalRootRecursive())

	val data = listOf(1, 2, 3, 4, 5, 6, 7, 8, 9)
	println(data.countEven())
}