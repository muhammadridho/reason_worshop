let component = ReasonReact.statelessComponent("Todo_Footer");

type filter =
  | All
  | Active
  | Completed;

let make = (~todoLength, ~onFilter, _children) => {
  ...component,
  render: _self => {
    <div>
      <p> {ReasonReact.string(string_of_int(todoLength))} </p>
      <button onClick={_event => onFilter(All)}>
        {ReasonReact.string("All")}
      </button>
      <button onClick={_event => onFilter(Active)}>
        {ReasonReact.string("Active")}
      </button>
      <button onClick={_event => onFilter(Completed)}>
        {ReasonReact.string("Completed")}
      </button>
    </div>;
  },
};