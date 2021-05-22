import kotlin.math.abs

fun <Key, Value> Map<Key, Value>.linearSearch(searchKey: Key) : Value? {
	for ((key, value) in this)
		if (key == searchKey) return value
	return null //Not found
}

fun <Key, Value> Map<Key, Value>.linearSearchSentinel(searchKey: Key) : Value? {
	var index = 0
	with(this.keys.toList()) {
		try {
			while (this[index] != searchKey) index++
		} catch (e: Exception) {
			return null //No element was found
		}
		return this@linearSearchSentinel[this[index]]
	}
}

fun <Value> Map<Int, Value>.interpolationSearch(searchKey: Int) : Value? = with(this.keys.toList()) {
	var lowerBound = 0
	var upperBound = size - 1
	var middle: Int
	while (lowerBound != upperBound && this[lowerBound] <= searchKey && searchKey <= this[upperBound]) {
		middle = lowerBound + abs(
			((searchKey - this[lowerBound]) * (upperBound - lowerBound)) / (this[upperBound] - this[lowerBound])
		)
		when {
			this[middle] < searchKey -> lowerBound = middle + 1
			this[middle] > searchKey -> upperBound = middle - 1
			else -> return this@interpolationSearch[this[middle]]
		}
	}
	return null //Not found
}