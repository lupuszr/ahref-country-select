
type components = {
  option: ReasonReact.reactClass
};

[@react.component] [@bs.module "react-select"]
external make: (
  ~value: option('a)=?,
  ~onChange: Js.nullable('a) => unit=?,
  ~options: array('a),
  ~className: string=?,
  ~components: components=?,
) => React.element = "default";
