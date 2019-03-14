// let a = "string";
// let integer = 1_000_000;
// let floating = 1.0;
// let bool = true;
// let list = [];
// let array = [||];
// type tuple = (string, string, int);

// let add = (a, b) => a +. b;

// let (<$>) = (maybe, fn) => {
//   switch (maybe) {
//   | Some(value) => fn(value)
//   | None => None
//   };
// };

// l

// let a = Some(1) <$> (whatever => Some(whatever + 1));

// // let (+) = (a, b) => add(a, b);

// let concat = (a, b) => a ++ b;

// let (or) = (maybe, defaultValue) => {
//   switch (maybe) {
//   | Some(value) => value
//   | None => defaultValue
//   };
// };

// let maybeNumber = None;

// let n = maybeNumber or 0;

// let object_ = {"hello": "world"};

// type record = {
//   hello: string,
//   world: string,
// };

// let record = {hello: "world", world: "hello"};

let append = (maybeValue, xs) => {
  switch (maybeValue) {
  | Some(value) => Array.append([|value|], xs)
  | None => xs
  };
};

let rec sum = xs => {
  switch (xs) {
  | [] => 0
  | [hd, ...tl] => hd + sum(tl)
  };
};

let sum = xs => {
  let length = List.length(xs);
  let result = ref(0);
  for (x in 0 to length) {
    result := result^ + x;
  };
  result^;
};

let sum = xs => List.fold_left((acc, number) => acc + number, 0, xs);

let rec fib = x =>
  if (x == 0) {
    1;
  } else {
    x - 1 + fib(x - 1);
  };
// let somethong = xs => [...xs, 1////];

// let value = None;

append(None, [||]);