fun String?.isOperator() =
	this == "+" || this == "-" || this == "*" || this == "/"

fun Char?.isOperator() =
	this == '+' || this == '-' || this == '*' || this == '/'

fun String.performAction(lhs: String, rhs: String): String = when (this) {
	"+" -> (lhs.toInt() + rhs.toInt()).toString()
	"-" -> (lhs.toInt() - rhs.toInt()).toString()
	"*" -> (lhs.toInt() * rhs.toInt()).toString()
	else -> (lhs.toInt() / rhs.toInt()).toString()
}

fun String.toQueue(): Queue<String> {
	val queue = Queue<String>()
	var index = 0
	while (index < this.length) {
		if(this[index].isDigit()) {
			val digitEndIndex = (this.substring(index).find { (it == ' ' || it.isOperator())}?.let { this.indexOf(it, index) } ?: this.length) - 1
			queue.push(this.substring(index..digitEndIndex))
			index = digitEndIndex + 1
		} else {
			if (this[index] != ' ') queue.push(this[index].toString())
			index++;
		}
	}
	return queue
}

fun String.isInt(): Boolean =
	this.all { it in '0'..'9' }

fun String.eval(): Int {
	val queue = this.toQueue()
	while (queue.size != 1) {
		val item = queue.pop()!!
		if (queue.top().isOperator()) {
			queue.push(item)
			continue
		}
		val lhs = queue.pop()!!; val rhs = queue.pop()!!
		if (!rhs.isInt()) with(queue) {
			push(item)
			push(lhs)
			push(rhs)
		}
		else queue.push(item.performAction(lhs, rhs))
	}
	return queue.top()!!.toInt()
}

fun String.getParenthesesIndexes(byOpen: Boolean = true): List<Pair<Int, Int>> {
	val result = mutableListOf<Pair<Int, Int>>()
	var start = indexOf('('); var end = 0
	while (start != -1) {
		substring(start + 1).let {
			var open = 0; var close = 0;
			for ((index, symbol) in it.withIndex()) {
				if (symbol == '(') open++
				else if (symbol == ')') close++

				if (open + close > 0 && close > open) {
					end = index + start + 1
					break
				}
			}
		}
		result.add(
			Pair(start + 1, end + 1)
		)
		start = indexOf('(', start + 1)
	}
	result.sortWith(compareBy { if (byOpen) it.first else it.second})
	return result
}

fun Char?.priority() : Int = when {
	this == '+' || this == '-' -> 1
	this == '*' || this == '/' -> 2
	else -> 0
}

fun String.toPrefix(): String {
	val reverseExpression = reversed()
	var prefixExpression = ""
	val stack = ArrayDeque<Char>()
	for (symbol in reverseExpression) when {
		symbol.isLetterOrDigit() -> prefixExpression += symbol
		symbol == '(' -> stack.addFirst(symbol)
		symbol == ')' -> while (stack.isNotEmpty() && stack.first() != '(') prefixExpression += stack.removeFirst()
		else -> {
			if (symbol.priority() < stack.firstOrNull().priority())
				while (stack.isNotEmpty() && symbol.priority() < stack.first().priority())
					prefixExpression += stack.removeFirst()

			stack.addFirst(symbol)
		}
	}
	while (stack.isNotEmpty()) prefixExpression += stack.removeFirst()
	return prefixExpression.reversed()
}