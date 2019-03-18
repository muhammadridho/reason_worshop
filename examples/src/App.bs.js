// Generated by BUCKLESCRIPT VERSION 4.0.18, PLEASE EDIT WITH CARE
'use strict';

var Css = require("bs-css/src/Css.js");
var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Pervasives = require("bs-platform/lib/js/pervasives.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Get$ReactTemplate = require("./Get.bs.js");
var Post$ReactTemplate = require("./Post.bs.js");
var Todo_Item$ReactTemplate = require("./Todo_Item.bs.js");
var Todo_Footer$ReactTemplate = require("./Todo_Footer.bs.js");
var Todo_AddInput$ReactTemplate = require("./Todo_AddInput.bs.js");

var container = Css.style(/* :: */[
      Css.display(/* flex */-1010954439),
      /* :: */[
        Css.flexDirection(/* column */-963948842),
        /* :: */[
          Css.alignItems(/* center */98248149),
          /* [] */0
        ]
      ]
    ]);

var todoContainer = Css.style(/* :: */[
      Css.width(/* `percent */[
            -119887163,
            80
          ]),
      /* :: */[
        Css.maxWidth(/* `rem */[
              5691738,
              30
            ]),
        /* :: */[
          Css.display(/* flex */-1010954439),
          /* :: */[
            Css.flexDirection(/* column */-963948842),
            /* [] */0
          ]
        ]
      ]
    ]);

var title = Css.style(/* :: */[
      Css.fontSize(/* `rem */[
            5691738,
            3
          ]),
      /* [] */0
    ]);

var listContainer = Css.style(/* :: */[
      Css.paddingLeft(/* `px */[
            25096,
            0
          ]),
      /* [] */0
    ]);

var Styles = /* module */[
  /* container */container,
  /* todoContainer */todoContainer,
  /* title */title,
  /* listContainer */listContainer
];

var component = ReasonReact.reducerComponent("App_Root");

function make(_children) {
  var handleKeyOnSave = function (state) {
    var value = state[/* newTodoValue */1];
    if (value === "") {
      return undefined;
    } else {
      return /* record */[
              /* id */Pervasives.string_of_float(Date.now()),
              /* title */value,
              /* checked */false
            ];
    }
  };
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (param) {
              var send = param[/* send */3];
              var state = param[/* state */1];
              return React.createElement("div", {
                          className: container
                        }, React.createElement("h1", {
                              className: title
                            }, "Todo Jadi Jadian"), React.createElement("div", {
                              className: todoContainer
                            }, ReasonReact.element(undefined, undefined, Post$ReactTemplate.make((function (status, submit) {
                                        return ReasonReact.element(undefined, undefined, Todo_AddInput$ReactTemplate.make(state[/* newTodoValue */1], (function ($$event) {
                                                          return Curry._1(send, /* OnChangeNewTodoValue */Block.__(2, [$$event.target.value]));
                                                        }), (function ($$event) {
                                                          var match = $$event.which;
                                                          if (match !== 13) {
                                                            return /* () */0;
                                                          } else {
                                                            var match$1 = handleKeyOnSave(state);
                                                            if (match$1 !== undefined) {
                                                              return Curry._2(submit, match$1, (function (responseTodo) {
                                                                            return Curry._1(send, /* AddTodo */Block.__(1, [responseTodo]));
                                                                          }));
                                                            } else {
                                                              return /* () */0;
                                                            }
                                                          }
                                                        }), status ? true : false, /* array */[]));
                                      }))), React.createElement("ul", {
                                  className: listContainer
                                }, ReasonReact.element(undefined, undefined, Get$ReactTemplate.make((function (todos) {
                                            return Curry._1(send, /* SetInitialTodos */Block.__(6, [todos]));
                                          }), (function (todoState) {
                                            if (typeof todoState === "number") {
                                              switch (todoState) {
                                                case 0 : 
                                                    return null;
                                                case 1 : 
                                                    return "loading lho";
                                                case 2 : 
                                                    var todos = state[/* todos */0];
                                                    var send$1 = send;
                                                    var match = List.length(todos) < 1;
                                                    if (match) {
                                                      return null;
                                                    } else {
                                                      var __x = List.filter((function (todo) {
                                                                var match = state[/* selectedFilter */2];
                                                                switch (match) {
                                                                  case 0 : 
                                                                      return true;
                                                                  case 1 : 
                                                                      return !todo[/* checked */2];
                                                                  case 2 : 
                                                                      return todo[/* checked */2];
                                                                  
                                                                }
                                                              }))(state[/* todos */0]);
                                                      return $$Array.of_list(List.map((function (todo) {
                                                                        return ReasonReact.element(todo[/* id */0], undefined, Todo_Item$ReactTemplate.make(todo, (function (_event) {
                                                                                          return Curry._1(send$1, /* DeleteTodo */Block.__(3, [todo[/* id */0]]));
                                                                                        }), (function (value) {
                                                                                          return Curry._1(send$1, /* UpdateTodo */Block.__(0, [
                                                                                                        todo[/* id */0],
                                                                                                        value
                                                                                                      ]));
                                                                                        }), (function (_event) {
                                                                                          return Curry._1(send$1, /* ToggleCheck */Block.__(4, [todo[/* id */0]]));
                                                                                        }), /* array */[]));
                                                                      }), __x));
                                                    }
                                                
                                              }
                                            } else {
                                              return todoState[0];
                                            }
                                          })))), ReasonReact.element(undefined, undefined, Todo_Footer$ReactTemplate.make(List.length(state[/* todos */0]), (function (selectedFilter) {
                                        return Curry._1(send, /* OnFilter */Block.__(5, [selectedFilter]));
                                      }), /* array */[]))));
            }),
          /* initialState */(function (param) {
              return /* record */[
                      /* todos : [] */0,
                      /* newTodoValue */"",
                      /* selectedFilter : All */0
                    ];
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, state) {
              switch (action.tag | 0) {
                case 0 : 
                    var title = action[1];
                    var idTarget = action[0];
                    var newTodoItems = List.map((function (todo) {
                            var match = todo[/* id */0] === idTarget;
                            if (match) {
                              return /* record */[
                                      /* id */todo[/* id */0],
                                      /* title */title,
                                      /* checked */todo[/* checked */2]
                                    ];
                            } else {
                              return todo;
                            }
                          }), state[/* todos */0]);
                    return /* Update */Block.__(0, [/* record */[
                                /* todos */newTodoItems,
                                /* newTodoValue */state[/* newTodoValue */1],
                                /* selectedFilter */state[/* selectedFilter */2]
                              ]]);
                case 1 : 
                    var todo = action[0];
                    console.log(todo);
                    return /* UpdateWithSideEffects */Block.__(2, [
                              /* record */[
                                /* todos : :: */[
                                  todo,
                                  state[/* todos */0]
                                ],
                                /* newTodoValue */state[/* newTodoValue */1],
                                /* selectedFilter */state[/* selectedFilter */2]
                              ],
                              (function (self) {
                                  return Curry._1(self[/* send */3], /* OnChangeNewTodoValue */Block.__(2, [""]));
                                })
                            ]);
                case 2 : 
                    return /* Update */Block.__(0, [/* record */[
                                /* todos */state[/* todos */0],
                                /* newTodoValue */action[0],
                                /* selectedFilter */state[/* selectedFilter */2]
                              ]]);
                case 3 : 
                    var id = action[0];
                    var newTodoItems$1 = List.filter((function (todo) {
                              return todo[/* id */0] !== id;
                            }))(state[/* todos */0]);
                    return /* Update */Block.__(0, [/* record */[
                                /* todos */newTodoItems$1,
                                /* newTodoValue */state[/* newTodoValue */1],
                                /* selectedFilter */state[/* selectedFilter */2]
                              ]]);
                case 4 : 
                    var idTarget$1 = action[0];
                    var newTodoItems$2 = List.map((function (todo) {
                            var match = todo[/* id */0] === idTarget$1;
                            if (match) {
                              return /* record */[
                                      /* id */todo[/* id */0],
                                      /* title */todo[/* title */1],
                                      /* checked */!todo[/* checked */2]
                                    ];
                            } else {
                              return todo;
                            }
                          }), state[/* todos */0]);
                    return /* Update */Block.__(0, [/* record */[
                                /* todos */newTodoItems$2,
                                /* newTodoValue */state[/* newTodoValue */1],
                                /* selectedFilter */state[/* selectedFilter */2]
                              ]]);
                case 5 : 
                    return /* Update */Block.__(0, [/* record */[
                                /* todos */state[/* todos */0],
                                /* newTodoValue */state[/* newTodoValue */1],
                                /* selectedFilter */action[0]
                              ]]);
                case 6 : 
                    return /* Update */Block.__(0, [/* record */[
                                /* todos */action[0],
                                /* newTodoValue */state[/* newTodoValue */1],
                                /* selectedFilter */state[/* selectedFilter */2]
                              ]]);
                
              }
            }),
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.Styles = Styles;
exports.component = component;
exports.make = make;
/* container Not a pure module */
