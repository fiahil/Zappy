 (*
  * Busina
  * 07.07.2012
  *)

let size = ref (0, 0)

let storage () =
  let aux = function
    | (Bridge.R_map_size (Bridge.RP_map_size ret)) -> ret
    | _                                            -> (0, 0)
  in
  size := (aux (Bridge.pull (Bridge.Team "")))
