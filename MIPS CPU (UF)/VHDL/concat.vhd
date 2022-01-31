library ieee;

use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity concat is
	port (
		IR : in std_logic_vector(25 downto 0);
		PC : in std_logic_vector(3 downto 0);
		concat: out std_logic_vector(31 downto 0));
end concat;

architecture BHV of concat is
begin
	concat <= PC & std_logic_vector(SHIFT_LEFT(resize(unsigned(IR),28),2));
end BHV;