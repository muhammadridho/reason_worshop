let component = ReasonReact.statelessComponent("Todo_AddInput");

let make = (~value, ~onChange, ~onKeyDown, _children) => {
  ...component,
  render: _self => {
    <input type_="text" onChange value onKeyDown />;
  },
};