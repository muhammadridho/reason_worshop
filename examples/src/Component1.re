module ButtonRG = {
  let component = ReasonReact.statelessComponent("ButtonRGKewl");

  let make = (~onClick=?, ~title, _children) => {
    ...component,
    render: _self => {
      <button ?onClick> {ReasonReact.string(title)} </button>;
    },
  };
};
let renderRgButton = (~title, ~onClick) => {
  <button onClick> {ReasonReact.string(title)} </button>;
};

type state = int;

type action =
  | Increment
  | Decrement
  | Reset;

let component = ReasonReact.reducerComponent("Counter");

let make = _children => {
  ...component,
  initialState: () => 0,
  reducer: (action, state) => {
    switch (action) {
    | Increment => ReasonReact.Update(state + 1)
    | Decrement => ReasonReact.Update(state - 1)
    | Reset => ReasonReact.Update(0)
    };
  },
  render: ({state, send}) => {
    <div>
      <p> {ReasonReact.string(string_of_int(state))} </p>
      <ButtonRG title="Increment" onClick={_ => send(Increment)} />
      {renderRgButton(~title="Decrement", ~onClick=_ => send(Decrement))}
      <button onClick={_ => send(Reset)}>
        {ReasonReact.string("Reset")}
      </button>
    </div>;
  },
};