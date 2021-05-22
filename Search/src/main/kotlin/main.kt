private val data100 = randomTable(100)
private val data1000 = randomTable(1000)
private val data10000 = randomTable(10000)

fun <Key, Value> assertAndLog(logPrefix: String, key: Key, item: Value, searchedItem: Value) : Boolean {
	val working = item == searchedItem
	colored {
		println("$logPrefix] ${if (working) "working".green else "failed".red}")
	}
	if (!working) {
		colored {
			println("$logPrefix] key = ${key.blue} | item = ${item.yellow} | searched item = ${searchedItem.yellow}\n\t $item != $searchedItem".red)
		}
	}
	return working
}

fun testLinearSearch() {
	val logPrefix = "[Linear search:"
	val key = data100.randomKey()
	val item = data100[key]; val searchedItem = data100.linearSearch(key)
	val working = assertAndLog(logPrefix, key, item, searchedItem)
	if (!working) return

	measureTest(ITERATIONS = 1, TEST_COUNT =  3, WARM_COUNT = 0, LOG_PREFIX = "$logPrefix 100 items]") {
		data100.linearSearch(data100.randomKey())
	}
	measureTest(ITERATIONS = 1, TEST_COUNT =  3, WARM_COUNT = 0, LOG_PREFIX = "$logPrefix 1'000 items]") {
		data1000.linearSearch(data1000.randomKey())
	}
	measureTest(ITERATIONS = 1, TEST_COUNT =  3, WARM_COUNT = 0, LOG_PREFIX = "$logPrefix 10'000 items]") {
		data10000.linearSearch(data10000.randomKey())
	}
}

fun testSentinelSearch() {
	val logPrefix = "[Sentinel search:"
	val key = data100.randomKey()
	val item = data100[key]; val searchedItem = data100.linearSearchSentinel(key)
	val working = assertAndLog(logPrefix, key, item, searchedItem)
	if (!working) return

	measureTest(ITERATIONS = 1, TEST_COUNT =  3, WARM_COUNT = 0, LOG_PREFIX = "$logPrefix 100 items]") {
		data100.linearSearchSentinel(data100.randomKey())
	}
	measureTest(ITERATIONS = 1, TEST_COUNT =  3, WARM_COUNT = 0, LOG_PREFIX = "$logPrefix 1'000 items]") {
		data1000.linearSearchSentinel(data1000.randomKey())
	}
	measureTest(ITERATIONS = 1, TEST_COUNT =  3, WARM_COUNT = 0, LOG_PREFIX = "$logPrefix 10'000 items]") {
		data10000.linearSearchSentinel(data10000.randomKey())
	}
}

fun testInterpolationSearch() {
	val logPrefix = "[Interpolation search:"
	val key = data100.randomKey()
	val item = data100[key]; val searchedItem = data100.toSortedMap().interpolationSearch(key)
	val working = assertAndLog(logPrefix, key, item, searchedItem)
	if (!working) return

	measureTest(ITERATIONS = 1, TEST_COUNT =  3, WARM_COUNT = 0, LOG_PREFIX = "$logPrefix 100 items]") {
		data100.toSortedMap().interpolationSearch(data100.randomKey())
	}
	measureTest(ITERATIONS = 1, TEST_COUNT =  3, WARM_COUNT = 0, LOG_PREFIX = "$logPrefix 1'000 items]") {
		data1000.toSortedMap().interpolationSearch(data1000.randomKey())
	}
	measureTest(ITERATIONS = 1, TEST_COUNT =  3, WARM_COUNT = 0, LOG_PREFIX = "$logPrefix 10'000 items]") {
		data10000.toSortedMap().interpolationSearch(data10000.randomKey())
	}
}

fun main() {
	testLinearSearch()
	testSentinelSearch()
	testInterpolationSearch()
}