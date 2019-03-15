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

let write_t = t =>
  Json.Encode.object_([
    ("id", Json.Encode.string(t.id)),
    ("item", Json.Encode.string(t.title)),
    ("checked", Json.Encode.bool(t.checked)),
  ]);