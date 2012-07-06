(*
 * Fiahil
 * 25.06.2012
 *)

let sock = Unix.socket Unix.PF_INET Unix.SOCK_STREAM 0
let buffer = ref (String.create 4096)

let connect addr port =
  let recv_buf = String.create 4096
  in
    begin
      Unix.connect sock (Unix.ADDR_INET ((Unix.inet_addr_of_string addr), port));
      ignore (Unix.recv sock recv_buf 0 (String.length recv_buf) []);
      Unix.setsockopt_float sock Unix.SO_RCVTIMEO 0.0001
    end

let send data =
  ignore (Unix.send sock data 0 (String.length data) [])

let recv () =
  let rec split str =
    let re = Str.regexp "^\\(.*\\)\n"
    in
      if Str.string_match re str 0 then
        begin
          buffer := Str.string_after str (Str.match_end ());
          Str.matched_string str
        end
      else
        begin
          buffer := str;
          ""
        end
  and
          aux ret buf =
    try
      if Unix.recv sock buf 0 (String.length buf) [] = (String.length buf) then
        aux (ret ^ buf) (String.create 4096)
      else if !buffer.[0] != Char.chr(0) then
        split (!buffer ^ ret ^ buf)
      else
        split (ret ^ buf)
    with
      | Unix.Unix_error (t, w, r)       -> ""
  in
    if not (String.contains !buffer '\n') then
      aux "" (String.create 4096)
    else
      split !buffer

(*
 * Unitest
 *)
let unitest () =
  let _ = connect "127.0.0.1" 4242
  in
  let _ = print_endline ((recv ()) ^ " == END")
  and
            _ = print_endline ((recv ()) ^ " == END")
  and
                  _ = print_endline ((recv ()) ^ " == END")
  in
    send "Je vais au royaume du poney fringuant!"

