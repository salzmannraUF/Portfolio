library ieee;

use ieee.std_logic_1164.all;

entity memory is
	port(
	clk : in std_logic;
	MemWrite : in std_logic;
	address	: in std_logic_vector(31 downto 0);
	inport0 : in std_logic_vector(31 downto 0);
	inport1 : in std_logic_vector(31 downto 0);
	IP0_en : in std_logic;
	IP1_en : in std_logic;
	wrdata : in std_logic_vector(31 downto 0); -- RegB
	outport : out std_logic_vector(31 downto 0);
	data_out : out std_logic_vector(31 downto 0));
end memory;

architecture BHV of memory is
	signal IP0_out, IP1_out : std_logic_vector(31 downto 0);
	signal RAM_out : std_logic_vector(31 downto 0);
	signal wren : std_logic;
begin

U_RAM		: entity work.TestCase1
				port map(
					address => address(9 downto 2),
					clock => clk,
					data => wrdata,
					wren => wren,
					q	 => RAM_out);

--U_RAM		: entity work.TestCase2
--				port map(
--					address	 => address(9 downto 2),
--					clock => clk,
--					data => wrdata,
--					wren => wren,
--					q => RAM_out);

--U_RAM		: entity work.TestCase4
--				port map(
--					address	 => address(9 downto 2),
--					clock => clk,
--					data => wrdata, 
--					wren => wren,
--					q => RAM_out);

--U_RAM		: entity work.TestCase7
--				port map(
--					address	 => address(9 downto 2),
--					clock => clk,
--					data => wrdata,
--					wren => wren,
--					q => RAM_out);

--U_RAM		: entity work.bubble_sort
--				port map(
--					address	 => address(9 downto 2),
--					clock => clk,
--					data => wrdata,
--					wren => wren,
--					q => RAM_out);

--U_RAM		: entity work.GCD_assembly
--				port map(
--					address	 => address(9 downto 2),
--					clock => clk,
--					data => wrdata,
--					wren => wren,
--					q => RAM_out);

	process(clk)
	begin
		if(rising_edge(clk))then
			if (IP0_en = '1') then
				IP0_out <= inport0;
			end if;
			
			if (IP1_en = '1') then
				IP1_out <= inport1;
			end if;

			wren <= '0';
			if (memWrite = '1') then
			
				if (address = x"0000FFFC") then

					outPort <= wrdata; 
				else
					wren <= '1';
				end if;
			end if;
		end if;
	end process;
	
	process(address,IP0_out,IP1_out,RAM_out)
	begin
		if (address = x"0000FFF8") then
			data_out <= IP0_out;
		elsif (address = x"0000FFFC") then
			data_out <= IP1_out;					
		else
			data_out <= RAM_out;
		end if;
	end process;
end BHV;