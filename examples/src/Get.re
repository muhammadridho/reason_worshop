type state =
  | Idle
  | Error(string)
  | Loading
  | Loaded

type action =
  | FetchRequested
  | FetchSucceed
  | FetchFailed(string);

let component = ReasonReact.reducerComponent("Get");

let make = (~onCompleted, children) => {
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
                 onCompleted(todos)
                 self.send(FetchSucceed) |> resolve;
               })
            |> catch(_error =>
                 self.send(FetchFailed("Fetch todos failed")) |> resolve
               )
            |> ignore
          ),
      )
    | FetchSucceed => ReasonReact.Update(Loaded)
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