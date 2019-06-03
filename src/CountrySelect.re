/* [%%raw "require('flag-icon-css/flags/1x1/')"]; */
let url = "https://gist.githubusercontent.com/rusty-key/659db3f4566df459bd59c8a53dc9f71f/raw/4127f9550ef063121c564025f6d27dceeb279623/counties.json"

type country = {
  label: string,
  value: string
};

let decodeCountries = (xs: Js.Json.t) => {
  module JsonToCountry = JsonDecoder.MakeJsonDecoder({
    type t = country
  });
  JsonToCountry.parseArray(xs);
};

let findInCountries = (xs: array(country), value: string) => {
  Belt.Array.getBy(xs, c => c.value == value)
};

[@react.component]
let make = (~onChange, ~value) => {
  let (error, setError) = React.useState(() => "");
  let (countries, setCountries) = React.useState(() => [||]);

  React.useEffect1(() => {
    open Fetch;
    
    let _ = fetch(url) 
    |> Js.Promise.then_(Response.json)
    |> Js.Promise.then_(a => {
      switch (decodeCountries(a)) {
      | Ok(xs) => setCountries(_ => xs)
      | Error(e) => setError(_ => e)
      };
      Js.Promise.resolve(a)
    });
    Some(() => ())
  }, [||]);
  
  <div>
    {ReasonReact.string(error)}
    {switch (value) {
    | Some(country_code) =>
      <IReactSelect
        value=findInCountries(countries, country_code)
        options=countries
        onChange=onChange
      />;
    | None => ReasonReact.null
    };}
  </div>;
};
