library ieee;

use ieee.std_logic_1164.all;

entity mux_2x1 is
  generic (
    width  :     positive);
  port (
    input1    : in  std_logic_vector(width-1 downto 0);
    input2    : in  std_logic_vector(width-1 downto 0);
    sel    : in  std_logic;
    output : out std_logic_vector(width-1 downto 0));
end mux_2x1;

architecture BHV of mux_2x1 is
begin
	with sel select
		output <= input2 when '1',input1 when others;
end BHV;
