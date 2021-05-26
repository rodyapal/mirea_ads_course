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
		colored {
			println("$LOG_PREFIX ${time.yellow} ms")
		}

		results.add(time)
		totalTime += time
	}

	results.sort()

	val average = totalTime / TEST_COUNT
	val median = results[results.size / 2]

	colored {
		println("$LOG_PREFIX -> average = ${average.blue} ms | median = ${median.cyan} ms")
	}
}