// Solutions 1

let rec createFibonacciLists = (num, array) => {
  switch (num) {
  | 0 => [|0|]
  | 1 => [|0, 1|]
  | _ =>
    if (Array.length(array) - 1 == num) {
      array;
    } else {
      let l1 = array[Array.length(array) - 1];
      let l2 = array[Array.length(array) - 2];
      createFibonacciLists(num, Array.append(array, [|l1 + l2|]));
    }
  };
};

let sumEvenNumbers = array =>
  Array.fold_left(
    (allVal, curr) => curr mod 2 == 0 ? allVal + curr : allVal,
    0,
    array,
  );

let sumEvenFibonacciNumbers = num => {
  let defaultFibonacci = [|0, 1|];
  createFibonacciLists(num, defaultFibonacci) |> sumEvenNumbers;
};

// Solutions 2
let rec getFibonacciNum = num => {
  switch (num) {
  | 0 => 0
  | 1 => 1
  | num => getFibonacciNum(num - 1) + getFibonacciNum(num - 2)
  };
};

let sumEvenNumber = (x, y) => x mod 2 == 0 ? x + y : x;

let sumEvenFibonacciNumbersTwo = num => {
  let result = ref(0);
  for (i in 1 to num) {
    let fibonacciNumber = getFibonacciNum(i);
    result := sumEvenNumber(result^, fibonacciNumber);
  };
  result^;
};

Js.log(sumEvenFibonacciNumbers(8));
Js.log(sumEvenFibonacciNumbers(8));