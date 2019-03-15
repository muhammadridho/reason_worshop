type t = {
  id: string,
  title: string,
  checked: bool,
};

type state = {
  isEdit: bool,
  inputEditValue: string,
};

type action =
  | ToggleEdit
  | OnChangeVal(string)
  | OnSaveVal
  | OnKeyDown(int);

let component = ReasonReact.reducerComponent("Todo_Item");

let make = (~todo, ~onDestroy, ~onUpdate, ~onToggle, _children) => {
  ...component,
  initialState: () => {isEdit: false, inputEditValue: todo.title},
  reducer: (action, state) => {
    switch (action) {
    | ToggleEdit => ReasonReact.Update({...state, isEdit: !state.isEdit})
    | OnChangeVal(inputEditValue) =>
      ReasonReact.Update({...state, inputEditValue})
    | OnSaveVal =>
      ReasonReact.SideEffects(
        self => {
          self.send(ToggleEdit);
          onUpdate(state.inputEditValue);
        },
      )
    | OnKeyDown(num) =>
      switch (num) {
      | 27 =>
        ReasonReact.Update({
          ...state,
          inputEditValue: state.inputEditValue,
          isEdit: false,
        })
      | 13 => ReasonReact.SideEffects(({send}) => send(OnSaveVal))
      | _ => ReasonReact.NoUpdate
      }
    };
  },
  render: ({state, send}) => {
    <li>
      <input type_="checkbox" checked={todo.checked} onChange=onToggle />
      <p onDoubleClick={_event => send(ToggleEdit)}>
        {ReasonReact.string(todo.title)}
      </p>
      {state.isEdit ?
         <input
           type_="text"
           value={state.inputEditValue}
           onChange={event =>
             send(OnChangeVal(ReactEvent.Form.target(event)##value))
           }
           onKeyDown={event =>
             send(ReactEvent.Keyboard.which(event)->OnKeyDown)
           }
           onBlur={_event => send(OnSaveVal)}
         /> :
         ReasonReact.null}
      <button onClick=onDestroy> {ReasonReact.string("hapus")} </button>
    </li>;
  },
};