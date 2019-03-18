type state = 
    | Idle
    | Sending

type action = 
  | SendRequested(Model.t, Model.t => unit)
  | SendSucceed(Model.t, Model.t => unit)
  | SendFailed
  

let component = ReasonReact.reducerComponent("Post")

let make = (children) => {
  ...component,
  initialState: () => Idle,
  reducer: (action, _state) => {
    switch (action) {
    | SendRequested(bodyData, fn) =>
      ReasonReact.UpdateWithSideEffects(
        Sending,
        self =>

  Js.Promise.(
    Fetch.fetchWithInit(
      "http://localhost:3000/todos",
      Fetch.RequestInit.make(
        ~credentials=Include,
      ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
        ~body=Fetch.BodyInit.make(Json.stringify(Model.write_t(bodyData))),
        ~method_=Post,
        ()
      )
    )
    |> then_(Bs_fetch.Response.json)
    |> then_(response => {
      let todo = Model.read_todo_t(response)
                 self.send(SendSucceed(todo, fn)) |> resolve;
               })
            |> catch(_error =>
                 self.send(SendFailed) |> resolve
               )
            |> ignore
      ))
    | SendSucceed(todo, fn) => ReasonReact.UpdateWithSideEffects(Idle, (_self) => fn(todo))
    | SendFailed => ReasonReact.Update(Idle)
    };
  },
  render: self => {
    children(self.state, (~bodyData, ~onCompleted) => self.send(SendRequested(bodyData, onCompleted)));
  },
};