library ieee;

use ieee.std_logic_1164.all;

entity mux_4x1 is
  generic (
    width  :     positive);
  port (
    input1    : in  std_logic_vector(width-1 downto 0);
    input2    : in  std_logic_vector(width-1 downto 0);
	 input3    : in  std_logic_vector(width-1 downto 0);
    input4    : in  std_logic_vector(width-1 downto 0);
    sel    : in  std_logic_vector(1 downto 0);
    output : out std_logic_vector(width-1 downto 0));
end mux_4x1;

architecture BHV of mux_4x1 is
begin
	with sel select
		output <= input2 when "01", input3 when "10", input4 when "11", input1 when others;
end BHV;