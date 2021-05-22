private val data0 = listOfRandomInts(100).toTypedArray()
private val data1 = listOfRandomInts(1000).toTypedArray()
private val data2 = listOfRandomInts(10000).toTypedArray()
private val data3 = listOfRandomInts(100000).toTypedArray()
private val data4 = listOfRandomInts(1000000).toTypedArray()
private val dataBest0 = data0.sortedArray()
private val dataBest1 = data1.sortedArray()
private val dataBest2 = data2.sortedArray()
private val dataBest3 = data3.sortedArray()
private val dataBest4 = data4.sortedArray()
private val dataWorst0 = data0.sortedArray().apply { reverse() }
private val dataWorst1 = data1.sortedArray().apply { reverse() }
private val dataWorst2 = data2.sortedArray().apply { reverse() }
private val dataWorst3 = data3.sortedArray().apply { reverse() }
private val dataWorst4 = data4.sortedArray().apply { reverse() }

fun testBubble() {
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[BubbleSort: 100]") {
		data0.bubbleSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[BubbleSort: 1'000]") {
		data1.bubbleSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[BubbleSort: 10'000]") {
		data2.bubbleSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[BubbleSort: 100'000]") {
		data3.bubbleSort()
	}
}

fun testShaker() {
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[ShakerSort: 100]") {
		data0.shakerSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[ShakerSort: 1'000]") {
		data1.shakerSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[ShakerSort: 10'000]") {
		data2.shakerSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[ShakerSort: 100'000]") {
		data3.shakerSort()
	}
}

fun testMerge() {
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[MergeSort: 100]") {
		data0.mergeSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[MergeSort: 1'000]") {
		data1.mergeSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[MergeSort: 10'000]") {
		data2.mergeSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[MergeSort: 100'000]") {
		data3.mergeSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[MergeSort: 1'000'000]") {
		data4.mergeSort()
	}
}

fun testBubbleEdges() {
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[BubbleSort Best case: 100]") {
		dataBest0.bubbleSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[BubbleSort Best case: 1'000]") {
		dataBest1.bubbleSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[BubbleSort Best case: 10'000]") {
		dataBest2.bubbleSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[BubbleSort Best case: 100'000]") {
		dataBest3.bubbleSort()
	}

	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[BubbleSort Worst case: 100]") {
		dataWorst0.bubbleSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[BubbleSort Worst case: 1'000]") {
		dataWorst1.bubbleSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[BubbleSort Worst case: 10'000]") {
		dataWorst2.bubbleSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[BubbleSort Worst case: 100'000]") {
		dataWorst3.bubbleSort()
	}
}

fun testShakerEdges() {
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[shakerSort Best case: 100]") {
		dataBest0.shakerSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[shakerSort Best case: 1'000]") {
		dataBest1.shakerSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[shakerSort Best case: 10'000]") {
		dataBest2.shakerSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[shakerSort Best case: 100'000]") {
		dataBest3.shakerSort()
	}

	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[shakerSort Worst case: 100]") {
		dataWorst0.shakerSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[shakerSort Worst case: 1'000]") {
		dataWorst1.shakerSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[shakerSort Worst case: 10'000]") {
		dataWorst2.shakerSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[shakerSort Worst case: 100'000]") {
		dataWorst3.shakerSort()
	}
}

fun testMergeEdges() {

	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[mergeSort Best case: 100]") {
		dataBest0.mergeSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[mergeSort Best case: 1'000]") {
		dataBest1.mergeSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[mergeSort Best case: 10'000]") {
		dataBest2.mergeSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[mergeSort Best case: 100'000]") {
		dataBest3.mergeSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[mergeSort Best case: 1'000'000]") {
		dataBest4.mergeSort()
	}

	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[mergeSort Worst case: 100]") {
		dataWorst0.mergeSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[mergeSort Worst case: 1'000]") {
		dataWorst1.mergeSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[mergeSort Worst case: 10'000]") {
		dataWorst2.mergeSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[mergeSort Worst case: 100'000]") {
		dataWorst3.mergeSort()
	}
	measureTest(TEST_COUNT = 3, ITERATIONS = 1, WARM_COUNT = 0,  LOG_PREFIX = "[mergeSort Worst case: 1'000'000]") {
		dataWorst4.mergeSort()
	}
}

fun main() {
	testBubbleEdges()
	testShakerEdges()
	testMergeEdges()
	testBubble()
	testShaker()
	testMerge()
}