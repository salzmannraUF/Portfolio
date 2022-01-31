library ieee;

use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity sign_extend is
	port(
	input : in std_logic_vector(15 downto 0);
	IsSigned : in std_logic;
	output : out std_logic_vector(31 downto 0);
	output_shifted : out std_logic_vector(31 downto 0));
end sign_extend;

architecture BHV of sign_extend is
begin
	process(input,IsSigned)
	begin
		if (IsSigned = '1') then
			output <= std_logic_vector(resize(signed(input),32));
			output_shifted <= std_logic_vector(SHIFT_LEFT(resize(signed(input),32),2));
		
		else
			output <= std_logic_vector(resize(unsigned(input),32));
			output_shifted <= std_logic_vector(SHIFT_LEFT(resize(unsigned(input),32),2));
		
		end if;
	end process;
end BHV;