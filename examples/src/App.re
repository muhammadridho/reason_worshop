module Styles = {
  open Css;
  let container =
    style([display(`flex), flexDirection(`column), alignItems(`center)]);
};

type state = {
  todos: list(Todo_Item.t),
  newTodoValue: string,
  selectedFilter: Todo_Footer.filter,
};

type action =
  | UpdateTodo(string, string)
  | OnChangeNewTodoValue(string)
  | HandleEnterKeyDown(int)
  | DeleteTodo(string)
  | ToggleCheck(string)
  | OnFilter(Todo_Footer.filter);

let component = ReasonReact.reducerComponent("App_Root");

let make = _children => {
  let handleKeyOnSave = state => {
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
    };
  };
  {
    ...component,
    initialState: () => {
      todos: [{id: "sss", title: "ahay", checked: true}],
      newTodoValue: "",
      selectedFilter: All,
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
      | HandleEnterKeyDown(num) =>
        switch (num) {
        | 13 => handleKeyOnSave(state)
        | _ => ReasonReact.NoUpdate
        }

      | DeleteTodo(id) =>
        let newTodoItems =
          List.filter(todo => todo.Todo_Item.id !== id, state.todos);
        ReasonReact.Update({...state, todos: newTodoItems});
      | ToggleCheck(idTarget) =>
        let newTodoItems =
          List.map(
            todo =>
              todo.Todo_Item.id == idTarget ?
                {...todo, checked: !todo.checked} : todo,
            state.todos,
          );

        ReasonReact.Update({...state, todos: newTodoItems});
      | OnFilter(filterType) =>
        ReasonReact.Update({...state, selectedFilter: filterType})
      },
    render: ({state, send}) => {
      let renderTodoItems = (todos, send) =>
        List.length(todos) < 1 ?
          ReasonReact.null :
          List.filter(
            todo =>
              switch (state.selectedFilter) {
              | Active => !todo.Todo_Item.checked
              | Completed => todo.Todo_Item.checked
              | All => true
              },
            state.todos,
          )
          |> List.map(
               todo =>
                 <Todo_Item
                   key={todo.Todo_Item.id}
                   onDestroy={_event => send(DeleteTodo(todo.Todo_Item.id))}
                   onUpdate={value =>
                     send(UpdateTodo(todo.Todo_Item.id, value))
                   }
                   onToggle={_event => send(ToggleCheck(todo.Todo_Item.id))}
                   todo
                 />,
               _,
             )
          |> Array.of_list
          |> ReasonReact.array;

      <div className=Styles.container>
        <Todo_AddInput
          value={state.newTodoValue}
          onChange={event =>
            send(ReactEvent.Form.target(event)##value->OnChangeNewTodoValue)
          }
          onKeyDown={event =>
            send(HandleEnterKeyDown(ReactEvent.Keyboard.which(event)))
          }
        />
        <ul> {renderTodoItems(state.todos, send)} </ul>
        <Todo_Footer
          todoLength={List.length(state.todos)}
          onFilter={selectedFilter => send(OnFilter(selectedFilter))}
        />
      </div>;
    },
  };
};