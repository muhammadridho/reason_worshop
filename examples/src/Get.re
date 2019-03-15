type state =
  | Idle
  | Error(string)
  | Loading
  | Loaded(list(Model.t));

type action =
  | FetchRequested
  | FetchSucceed(list(Model.t))
  | FetchFailed(string);

let component = ReasonReact.reducerComponent("Get");

let make = children => {
  ...component,
  initialState: () => Idle,
  reducer: (action, _state) => {
    switch (action) {
    | FetchRequested =>
      ReasonReact.UpdateWithSideEffects(
        Loading,
        self =>
          Js.Promise.(
            Bs_fetch.fetch("http://localhost:3000/todos")
            |> then_(Bs_fetch.Response.json)
            |> then_(response => {
                 let todos = Model.read_response(response);
                 self.send(FetchSucceed(todos)) |> resolve;
               })
            |> catch(_error =>
                 self.send(FetchFailed("Fetch todos failed")) |> resolve
               )
            |> ignore
          ),
      )
    | FetchSucceed(todos) => ReasonReact.Update(Loaded(todos))
    | FetchFailed(message) => ReasonReact.Update(Error(message))
    };
  },
  didMount: self => {
    self.send(FetchRequested);
  },
  render: self => {
    children(self.state);
  },
};