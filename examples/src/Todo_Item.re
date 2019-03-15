type t = {
  id: string,
  title: string,
  checked: bool,
};

type state = {
  isEdit: bool,
  inputEditValue: string,
  inputRef: ref(option(ReasonReact.reactRef)),
};

type action =
  | ToggleEdit
  | OnChangeVal(string)
  | OnSaveVal
  | OnKeyDown(int);

module Styles = {
  open Css;

  let container =
    style([
      display(`flex),
      alignItems(`center),
      position(`relative),
      paddingTop(`px(16)),
      paddingBottom(`px(16)),
    ]);

  let createCheckboxStyle = checked => {
    let base =
      style([
        position(`relative),
        cursor(`pointer),
        width(`px(16)),
        height(`px(16)),
        border(`px(2), `solid, `hex("585757")),
        borderRadius(`px(2)),
        marginRight(`px(12)),
      ]);

    let styleBaseOnChecked =
      if (checked) {
        style([backgroundColor(`hex("585757"))]);
      } else {
        style([]);
      };
    merge([base, styleBaseOnChecked]);
  };

  let checkmarkIcon =
    style([
      position(`absolute),
      top(`px(2)),
      left(`px(5)),
      border(`px(2), `solid, `hex("fff")),
      borderTopWidth(`px(0)),
      borderRightWidth(`px(2)),
      borderBottomWidth(`px(2)),
      borderLeftWidth(`px(0)),
      width(`px(3)),
      height(`px(8)),
      transform(`rotate(`deg(45))),
    ]);

  let text =
    style([margin(`zero), fontSize(`px(24)), color(`hex("040402"))]);
  let deleteButton =
    style([
      position(`absolute),
      top(`percent(50.)),
      right(`px(10)),
      transform(translate(`px(2), `percent(-50.))),
    ]);

  let inputText =
    style([
      fontSize(`px(24)),
      borderColor(`hex("#DCDEDD")),
      padding(`rem(0.4)),
      borderColor(`hex("fff")),
      borderStyle(`solid),
      focus([outlineWidth(`zero), borderColor(`hex("fff"))]),
    ]);
};

let component = ReasonReact.reducerComponent("Todo_Item");

let make = (~todo, ~onDestroy, ~onUpdate, ~onToggle, _children) => {
  ...component,
  initialState: () => {
    isEdit: false,
    inputEditValue: todo.title,
    inputRef: ref(None),
  },
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
  render: self => {
    <li className=Styles.container>
      <div
        className={Styles.createCheckboxStyle(todo.checked)} onClick=onToggle>
        <div className=Styles.checkmarkIcon />
      </div>
      {self.state.isEdit ?
         <input
           type_="text"
           className=Styles.inputText
           value={self.state.inputEditValue}
           onChange={event =>
             self.send(OnChangeVal(ReactEvent.Form.target(event)##value))
           }
           onKeyDown={event =>
             self.send(ReactEvent.Keyboard.which(event)->OnKeyDown)
           }
           onBlur={_event => self.send(OnSaveVal)}
         /> :
         <p
           className=Styles.text
           onDoubleClick={_event => self.send(ToggleEdit)}>
           {ReasonReact.string(todo.title)}
         </p>}
      <button className=Styles.deleteButton onClick=onDestroy>
        {ReasonReact.string("hapus")}
      </button>
    </li>;
  },
};