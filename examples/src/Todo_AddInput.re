let component = ReasonReact.statelessComponent("Todo_AddInput");

module Styles = {
  open Css;
  let input =
    style([
      borderColor(`hex("#DCDEDD")),
      padding(`rem(0.4)),
      focus([outlineWidth(`zero), borderColor(`hex("000000"))]),
    ]);
};
let make = (~value, ~onChange, ~onKeyDown ,~disabled=?, _children) => {
  ...component,
  render: _self => {
    <input className=Styles.input type_="text" onChange value onKeyDown ?disabled />;
  },
};