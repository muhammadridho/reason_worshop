type t = {
  id: string,
  title: string,
  checked: bool,
};

let read_t = json => {
  id: json |> Json.Decode.field("id", Json.Decode.string),
  title: json |> Json.Decode.field("item", Json.Decode.string),
  checked: json |> Json.Decode.field("checked", Json.Decode.bool),
};

let read_response = Json.Decode.list(read_t);