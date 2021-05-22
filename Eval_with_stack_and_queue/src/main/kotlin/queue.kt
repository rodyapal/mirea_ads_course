class Queue<Type> {
	private val data = mutableListOf<Type>()

	val size get() = data.size

	fun clear() = data.clear()
	fun isEmpty() = data.isEmpty()
	fun isNotEmpty() = data.isNotEmpty()
	override fun toString() = data.toString()

	fun top() : Type? =
		if (isNotEmpty()) data[0] else null

	fun push(value: Type) = data.add(value)
	fun push(vararg elements: Type) {
		for (item in elements) {
			data.add(item)
		}
	}

	fun pop() : Type? {
		if(isEmpty()) return null
		val value = data[0]
		data.removeAt(0)
		return value
	}
}

fun <Type> queueOf(vararg elements: Type) : Queue<Type> {
	val queue = Queue<Type>()
	for (item in elements) {
		queue.push(item)
	}
	return queue
}