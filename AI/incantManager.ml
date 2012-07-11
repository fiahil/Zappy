 (*
  * Busina
  * 10.7.2012
  *)

let id = ref "0"

let init_incant_id () =
  id := (Digest.to_hex (Digest.string (string_of_float (Unix.gettimeofday ()))));
  print_endline(!id)
