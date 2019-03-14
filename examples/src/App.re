module Styles = {
  open Css;
  let container =
    style([display(`flex), flexDirection(`column), alignItems(`center)]);
};

type state = {
  todos: list(Todo_Item.t),
  newTodoValue: string,
};

type action =
  | UpdateTodo(string, string)
  | OnChangeNewTodoValue(string)
  | HandleEnterKeyDown(int)
  | DeleteTodo(string);

let component = ReasonReact.reducerComponent("App_Root");

let make = _children => {
  ...component,
  initialState: () => {
    todos: [{id: "sss", title: "ahay", checked: true}],
    newTodoValue: "",
  },
  reducer: (action, state) =>
    switch (action) {
    | UpdateTodo(idTarget, title) =>
      let newTodoItems =
        List.map(
          todo => todo.Todo_Item.id == idTarget ? {...todo, title} : todo,
          state.todos,
        );
      ReasonReact.Update({...state, todos: newTodoItems});
    | OnChangeNewTodoValue(newTodoValue) =>
      ReasonReact.Update({...state, newTodoValue})
    | HandleEnterKeyDown(13) =>
      switch (state.newTodoValue) {
      | "" => ReasonReact.NoUpdate
      | value =>
        let todo: Todo_Item.t = {
          id: string_of_float(Js.Date.now()),
          title: value,
          checked: false,
        };
        ReasonReact.UpdateWithSideEffects(
          {...state, todos: [todo, ...state.todos]},
          self => self.send(""->OnChangeNewTodoValue),
        );
      }
    | DeleteTodo(id) =>
      let todos = List.filter(todo => todo.Todo_Item.id !== id, state.todos);
      ReasonReact.Update({...state, todos});
    // 🔥 when we type another key
    | HandleEnterKeyDown(_) => ReasonReact.NoUpdate
    },
  render: ({state, send}) => {
    let renderTodoItems = (todos, send) =>
      List.length(todos) < 1 ?
        ReasonReact.null :
        List.map(
          todo =>
            <Todo_Item
              key={todo.Todo_Item.id}
              onDestroy={_event => send(DeleteTodo(todo.Todo_Item.id))}
              onUpdate={value => send(UpdateTodo(todo.Todo_Item.id, value))}
              todo
            />,
          todos,
        )
        ->Array.of_list
        ->ReasonReact.array;

    <div className=Styles.container>
      <input
        type_="text"
        onChange={event =>
          send(ReactEvent.Form.target(event)##value->OnChangeNewTodoValue)
        }
        value={state.newTodoValue}
        onKeyDown={event =>
          send(HandleEnterKeyDown(ReactEvent.Keyboard.which(event)))
        }
      />
      {renderTodoItems(state.todos, send)}
    </div>;
  },
};