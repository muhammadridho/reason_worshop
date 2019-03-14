type t = {
  id: string,
  title: string,
  checked: bool,
};

type state = {
  isEdit: bool,
  inputEditValue: string,
};

let component = ReasonReact.statelessComponent("Todo_Item");

let make = (~todo, ~onDestroy, _children) => {
  ...component,
  render: _self => {
    <li>
      <p> {ReasonReact.string(todo.title)} </p>
      <input type_="text" value="" />
      <button onClick=onDestroy> {ReasonReact.string("hapus")} </button>
    </li>;
  },
};