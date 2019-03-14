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
  | OnChangeVal(string);

let component = ReasonReact.reducerComponent("Todo_Item");

let make = (~todo, ~onDestroy, ~onUpdate, _children) => {
  ...component,
  initialState: () => {isEdit: false, inputEditValue: todo.title},
  reducer: (action, state) => {
    switch (action) {
    | ToggleEdit => ReasonReact.Update({...state, isEdit: !state.isEdit})
    | OnChangeVal(inputEditValue) =>
      ReasonReact.Update({...state, inputEditValue})
    };
  },
  render: ({state, send}) => {
    <li>
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
             switch (ReactEvent.Keyboard.which(event)) {
             | 13 => onUpdate(state.inputEditValue)
             | _ => Js.log("oh shit")
             }
           }
         /> :
         ReasonReact.null}
      <button onClick=onDestroy> {ReasonReact.string("hapus")} </button>
    </li>;
  },
};