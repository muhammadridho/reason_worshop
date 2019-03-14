module Styles = {
  open Css;
  let container = style([display(`flex)]);
};

type state = {
  todos: list(Todo_Item.t),
  newTodoValue: string,
};

type action =
  | SaveTodo(Todo_Item.t, string)
  | OnChangeTodoValue(string)
  | HandleEnterKeyDown;

let component = ReasonReact.reducerComponent("App_Root");

let make = _children => {
  ...component,
  initialState: () => {todos: [], newTodoValue: ""},
  reducer: (action, state) =>
    switch (action) {
    | SaveTodo(todoItem, title) =>
      ReasonReact.Update({...state, todos: state.todos})
    | OnChangeTodoValue(newTodoValue) =>
      ReasonReact.Update({...state, newTodoValue})
    | HandleEnterKeyDown => ReasonReact.NoUpdate
    },
  render: self => {
    <div> <input type_="text" /> </div>;
  },
};