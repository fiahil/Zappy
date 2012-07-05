(*
 * Fiahil
 * 27.06.2012
 *)

let timeout t =
  ignore (Unix.select [] [] [] t)

let launch () =
  let rec aux = function
    | Bridge.Prend p   ->
        begin
          Bridge.push (Bridge.Prend p);
          timeout 0.1;
          aux (Bridge.Avance)
        end
    | Bridge.Avance    ->
        begin
          Bridge.push Bridge.Avance;
          timeout 0.1;
          aux (Bridge.Prend Bridge.Nourriture)
        end
  in
    aux (Bridge.Avance)
