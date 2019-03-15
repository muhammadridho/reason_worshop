module Styles = {
  /*
        - Promise - Js.Promise | Lwt Async
        - Fetch - @glenssl/bs-fetch |


        - Normalization - @lennsl/bs-json | yojson
        - Validation

   fetch(string, {
     headers: {
       method: Post
     }
   })
      */
  open Css;

  let container =
    style([display(`flex), flexDirection(`column), alignItems(`center)]);

  let todoContainer =
    style([
      width(`percent(80.)),
      maxWidth(`rem(30.)),
      display(`flex),
      flexDirection(`column),
    ]);
  let title = style([fontSize(`rem(3.))]);

  let listContainer = style([paddingLeft(`px(0))]);
};

type state = {
  todos: list(Model.t),
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
      let todo: Model.t = {
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
    initialState: () => {todos: [], newTodoValue: "", selectedFilter: All},
    reducer: (action, state) =>
      switch (action) {
      | UpdateTodo(idTarget, title) =>
        let newTodoItems =
          List.map(
            (todo: Model.t) => todo.id == idTarget ? {...todo, title} : todo,
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
          List.filter((todo: Model.t) => todo.id !== id, state.todos);
        ReasonReact.Update({...state, todos: newTodoItems});
      | ToggleCheck(idTarget) =>
        let newTodoItems =
          List.map(
            (todo: Model.t) =>
              todo.id == idTarget ? {...todo, checked: !todo.checked} : todo,
            state.todos,
          );

        ReasonReact.Update({...state, todos: newTodoItems});
      | OnFilter(filterType) =>
        ReasonReact.Update({...state, selectedFilter: filterType})
      },
    render: ({state, send}) => {
      open Model;
      let renderTodoItems = (todos, send) =>
        List.length(todos) < 1 ?
          ReasonReact.null :
          List.filter(
            todo =>
              switch (state.selectedFilter) {
              | Active => !todo.checked
              | Completed => todo.checked
              | All => true
              },
            state.todos,
          )
          |> List.map(
               todo =>
                 <Todo_Item
                   key={todo.id}
                   onDestroy={_event => send(DeleteTodo(todo.id))}
                   onUpdate={value => send(UpdateTodo(todo.id, value))}
                   onToggle={_event => send(ToggleCheck(todo.id))}
                   todo
                 />,
               _,
             )
          |> Array.of_list
          |> ReasonReact.array;

      <div className=Styles.container>
        <h1 className=Styles.title>
          {ReasonReact.string("Todo Jadi Jadian")}
        </h1>
        <div className=Styles.todoContainer>
          <Todo_AddInput
            value={state.newTodoValue}
            onChange={event =>
              send(
                ReactEvent.Form.target(event)##value->OnChangeNewTodoValue,
              )
            }
            onKeyDown={event =>
              send(HandleEnterKeyDown(ReactEvent.Keyboard.which(event)))
            }
          />
          <ul className=Styles.listContainer>

              <Get>
                ...{todoState =>
                  switch (todoState) {
                  | Loading => ReasonReact.string("loading lho")
                  | Error(message) => ReasonReact.string(message)
                  | Idle => ReasonReact.null
                  | Loaded(todos) =>
                    todos
                    |> List.map(todo =>
                         <Todo_Item
                           key={todo.id}
                           onDestroy={_event => send(DeleteTodo(todo.id))}
                           onUpdate={value =>
                             send(UpdateTodo(todo.id, value))
                           }
                           onToggle={_event => send(ToggleCheck(todo.id))}
                           todo
                         />
                       )
                    |> Array.of_list
                    |> ReasonReact.array
                  }
                }
              </Get>
            </ul>
            // {renderTodoItems(state.todos, send)}
          <Todo_Footer
            todoLength={List.length(state.todos)}
            onFilter={selectedFilter => send(OnFilter(selectedFilter))}
          />
        </div>
      </div>;
    },
  };
};