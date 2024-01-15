fun <T : Comparable<T>> Array<T>.countInversions(): Pair<Int, Array<T>> {
	val array = clone(); val buffer = clone()
	val inversions = _mergeSort(array, buffer, 0, array.size - 1)
	return inversions to array
}

private fun <T : Comparable<T>> _mergeSort(
	array: Array<T>,
	buffer: Array<T>,
	left: Int,
	right: Int
): Int {
	if (right <= left) return 0
	val mid = (left + right) / 2
	var inversions = 0
	inversions += _mergeSort(array, buffer, left, mid)
	inversions += _mergeSort(array, buffer, mid + 1, right)
	inversions += _merge(array, buffer, left, mid + 1, right)
	return inversions
}

private fun <T : Comparable<T>> _merge(
	array: Array<T>,
	buffer: Array<T>,
	left: Int,
	mid: Int,
	right: Int
): Int {
	System.arraycopy(array, left, buffer, left, right - left + 1)

	var inversions = 0
	var i = left
	var j = mid
	var k = left
	while (i <= mid - 1 && j <= right) {
		if (array[i] <= array[j]) {
			buffer[k++] = array[i++]
		} else {
			buffer[k++] = array[j++]
			inversions += mid - i
		}
	}
	while (i <= mid - 1) buffer[k++] = array[i++]
	while (j <= right) buffer[k++] = array[j++]
	for (x in left..right) array[x] = buffer[x]
	return inversions
}

fun main() {
	val p = intArrayOf(8, 4, 2, 1).toTypedArray()
	p.countInversions().second.forEach { println(it) }
}