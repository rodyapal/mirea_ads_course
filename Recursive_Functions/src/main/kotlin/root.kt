fun Int.digitalRootIterative(): Int {
	var number = this;
	while (number > 9) {
		var sum = 0
		while (number > 0) {
			sum += number % 10
			number /= 10
		}
		number = sum
	}
	return number
}

fun Int.digitalRootRecursive(): Int {
	var number = this; var sum = 0
	while (number > 0) {
		sum += number % 10
		number /= 10
	}
	return if (sum > 9) sum.digitalRootRecursive() else sum
}

fun Int.digitalRoot(): Int = if (this % 9 == 0) 9 else this % 9