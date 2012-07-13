(*
 * Fiahil
 * 12.07.2012
 *)

(* Move *)
let move_to = function
  | 0           -> true
  | 1           ->
      begin
        Bridge.push (Bridge.Avance);
        false
      end
  | 2           ->
      begin
        Bridge.push (Bridge.Avance);
        Bridge.push (Bridge.Gauche);
        Bridge.push (Bridge.Avance);
        false
      end
  | 3           ->
      begin
        Bridge.push (Bridge.Gauche);
        Bridge.push (Bridge.Avance);
        false
      end
  | 4           ->
      begin
        Bridge.push (Bridge.Gauche);
        Bridge.push (Bridge.Avance);
        Bridge.push (Bridge.Gauche);
        Bridge.push (Bridge.Avance);
        false
      end
  | 5           ->
      begin
        Bridge.push (Bridge.Gauche);
        Bridge.push (Bridge.Gauche);
        Bridge.push (Bridge.Avance);
        false
      end
  | 6           ->
      begin
        Bridge.push (Bridge.Droite);
        Bridge.push (Bridge.Avance);
        Bridge.push (Bridge.Droite);
        Bridge.push (Bridge.Avance);
        false
      end
  | 7           ->
      begin
        Bridge.push (Bridge.Droite);
        Bridge.push (Bridge.Avance);
        false
      end
  | 8           ->
      begin
        Bridge.push (Bridge.Avance);
        Bridge.push (Bridge.Droite);
        Bridge.push (Bridge.Avance);
        false
      end
  | _           -> false

