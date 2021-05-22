import kotlin.random.Random

fun listOfRandomInts(size: Int): List<Int> {
	val random = Random(System.currentTimeMillis())
	return (0..size).map { random.nextInt() }
}

fun <T> Array<T>.swap(firstIndex: Int, secondIndex: Int) {
	val temp = this[firstIndex]
	this[firstIndex] = this[secondIndex]
	this[secondIndex] = temp
}

fun <T> Array<T>.asString() {
	var result = "["
	forEach {
		result += "${it}${if (it != last()) ", " else ""}"
	}
	result += "]"
}

/**
 * Iterates provided by [callback] code [ITERATIONS]x[TEST_COUNT] times.
 * Performs warming by iterating [ITERATIONS]x[WARM_COUNT] times.
 */
fun measureTest(
	ITERATIONS: Int = 1000,
	TEST_COUNT: Int = 10,
	WARM_COUNT: Int = 2,
	LOG_PREFIX: String = "[TimeTest]",
	callback: ()->Unit
) {
	val results = ArrayList<Long>()
	var totalTime = 0L
	var t = 0

	println("$LOG_PREFIX -> go")

	while (++t <= TEST_COUNT + WARM_COUNT) {
		val startTime = System.currentTimeMillis()

		var i = 0
		while (i++ < ITERATIONS)
			callback()

		if (t <= WARM_COUNT) {
			println("$LOG_PREFIX Warming $t of $WARM_COUNT")
			continue
		}

		val time = System.currentTimeMillis() - startTime
		println(LOG_PREFIX+" "+time.toString()+"ms")

		results.add(time)
		totalTime += time
	}

	results.sort()

	val average = totalTime / TEST_COUNT
	val median = results[results.size / 2]

	println("$LOG_PREFIX -> average=${average}ms / median=${median}ms")
}