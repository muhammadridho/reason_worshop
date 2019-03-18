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
  | AddTodo(Model.t)
  | OnChangeNewTodoValue(string)
  | DeleteTodo(string)
  | ToggleCheck(string)
  | OnFilter(Todo_Footer.filter)
  | SetInitialTodos(list(Model.t))
let component = ReasonReact.reducerComponent("App_Root");

let make = _children => {
  let handleKeyOnSave = state => {
    switch (state.newTodoValue) {
    | "" => None
    | value =>
      let todo: Model.t = {
        id: string_of_float(Js.Date.now()),
        title: value,
        checked: false,
      };

      Some(todo)
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
      | AddTodo(todo) =>
      Js.log(todo) 
              ReasonReact.UpdateWithSideEffects(
        {...state, todos: [todo, ...state.todos]},
        self => self.send(""->OnChangeNewTodoValue),
      )

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
      | SetInitialTodos(todos) =>
        ReasonReact.Update({...state, todos})
      
      
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
        <Post>
          ...{(status, submit) =>
           <Todo_AddInput
            value={state.newTodoValue}
            disabled={
              switch status {
              | Idle => false
              | Sending => true
              };
            }
            onChange={event =>
              send(
                ReactEvent.Form.target(event)##value->OnChangeNewTodoValue,
              )
            }
            onKeyDown={event =>
              switch (ReactEvent.Keyboard.which(event)) {
                | 13 => 
                  switch(handleKeyOnSave(state)){
                    | None => ()
                    | Some(todo) => submit(~bodyData=todo,~onCompleted={responseTodo => send(AddTodo(responseTodo))} )
                  }
                | _ => ()
                }
            }
          />
          }
        </Post>
          <ul className=Styles.listContainer>

              <Get
              onCompleted={todos => send(SetInitialTodos(todos))}>
                ...{todoState =>
                  switch (todoState) {
                  | Loading => ReasonReact.string("loading lho")
                  | Error(message) => ReasonReact.string(message)
                  | Idle => ReasonReact.null
                  | Loaded => renderTodoItems(state.todos, send)
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