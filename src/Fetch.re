type response;
[@bs.val] external fetch: string => Js.Promise.t(response) = "";

module Response = {
  type t = response;
  [@bs.send.pipe: response] external json: Js.Promise.t(Js.Json.t) = ""
};