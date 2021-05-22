fun<T : Comparable<T>> Array<T>.bubbleSort(): Array<T> {
	val array = clone()
	var exchanged: Boolean
	do {
		exchanged = false
		for (i in 1 until array.size) {
			if (array[i] < array[i - 1]) {
				array.swap(i, i - 1)
				exchanged = true
			}
		}
	} while (exchanged)
	return array
}

fun<T : Comparable<T>> Array<T>.shakerSort(): Array<T> {
	val array = clone()
	var exchanged: Boolean
	do {
		exchanged = false
		for (i in 1 until array.size) {
			if (array[i] < array[i - 1]) {
				array.swap(i, i - 1)
				exchanged = true
			}
		}
		for (i in array.size - 2 downTo 1) {
			if (array[i] < array[i - 1]) {
				array.swap(i, i - 1)
				exchanged = true
			}
		}
	} while (exchanged)
	return array
}

fun <T : Comparable<T>> Array<T>.mergeSort(): Array<T> {
	val array = clone(); val buffer = clone()
	_mergeSort(array, buffer, 0, array.size - 1)
	return array
}

private fun <T : Comparable<T>> _mergeSort(
	array: Array<T>,
	buffer: Array<T>,
	lo: Int,
	hi: Int
) {
	if (hi <= lo) return
	val mid = (lo + hi) / 2
	_mergeSort(array, buffer, lo, mid)
	_mergeSort(array, buffer, mid + 1, hi)
	_merge(array, buffer, lo, mid, hi)
}

private fun <T : Comparable<T>> _merge(
	array: Array<T>,
	buffer: Array<T>,
	lo: Int,
	mid: Int,
	hi: Int
) {
	System.arraycopy(array, lo, buffer, lo, hi - lo + 1)

	var i = lo
	var j = mid + 1
	for (k in lo..hi) {
		when {
			i > mid -> array[k] = buffer[j++]
			j > hi -> array[k] = buffer[i++]
			buffer[j] < buffer[i] -> array[k] = buffer[j++]
			else -> array[k] = buffer[i++]
		}
	}
}