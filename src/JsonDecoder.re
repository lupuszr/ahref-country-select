module type Parsing = {
  type t;
  /* let transformer: Js.Json.t => t  */
}

[@bs.new]
external _unsafeCreateUninitializedArray: int => array('a) = "Array";
exception DecodeError(string);

module MakeJsonDecoder = (M: Parsing) => {
  let parseArray = json => {
    if (Js.Array.isArray(json)) {
      let source: array(M.t) = Obj.magic(json: Js.Json.t);
      let length = Js.Array.length(source);
      let target = _unsafeCreateUninitializedArray(length);
      
      for (i in 0 to length - 1) {
        let value =
          try (Array.unsafe_get(source, i)) {
          | DecodeError(msg) =>
            raise @@
            DecodeError(msg ++ "\n\tin array at index " ++ string_of_int(i))
          };

        Array.unsafe_set(target, i, value);
      };
      Belt.Result.Ok(target);
    } else {
      Belt.Result.Error("Expected array, got " ++ Js.Json.stringify(json));
    };
  }
  
}
/* let array decode json = 
  if Js.Array.isArray json then begin
    let source = (Obj.magic (json : Js.Json.t) : Js.Json.t array) in
    let length = Js.Array.length source in
    let target = _unsafeCreateUninitializedArray length in
    for i = 0 to length - 1 do
      let value = 
        try
          decode (Array.unsafe_get source i)
        with
          DecodeError msg -> raise @@ DecodeError (msg ^ "\n\tin array at index " ^ string_of_int i)
        in
      Array.unsafe_set target i value;
    done;
    target
  end
  else
    raise @@ DecodeError ("Expected array, got " ^ _stringify json) */