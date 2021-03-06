(*
 * Fiahil
 * 25.06.2012
 *)

let sock = Unix.socket Unix.PF_INET Unix.SOCK_STREAM 0
let buffer = ref ""

let connect addr port =
  let recv_buf = String.create 4096
  in
    begin
      Unix.connect sock (Unix.ADDR_INET ((Unix.inet_addr_of_string addr), port));
      ignore (Unix.recv sock recv_buf 0 (String.length recv_buf) [])
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
    let rec auxx buf r =
      match Unix.select [sock] [] [] 0.01 with
        | (sock::[], _, _)    -> r := Unix.recv sock buf 0 (String.length buf) []
        | (_, _, _)           -> ()
    and
        r = ref (-1)
    in
      begin
        auxx buf r;
        (if !r > 0 then
          buffer := !buffer ^ (String.sub buf 0 !r)
        else if !r = 0 then
          raise Exit);
        split !buffer
      end
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
  let rec aux () =
    begin
      Printf.printf "== end :%s\n" (recv ());
      flush stdout;
      aux ()
    end
  in
    aux ()
