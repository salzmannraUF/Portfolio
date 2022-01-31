library ieee;

use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity registers is
    port(
        clk : in std_logic;
        rst : in std_logic;
		JumpAndLink	: in std_logic;
        rd_addr0 : in std_logic_vector(4 downto 0);
        rd_addr1 : in std_logic_vector(4 downto 0);
        wr_addr : in std_logic_vector(4 downto 0);
        wr_en : in std_logic;
        wr_data : in std_logic_vector(31 downto 0);
        rd_data0 : out std_logic_vector(31 downto 0);
        rd_data1 : out std_logic_vector(31 downto 0));
end registers;

architecture BHV of registers is
    type reg_array is array(0 to 31) of std_logic_vector(31 downto 0); -- 32 regs with 32 bits
    signal regs : reg_array;
    signal rd_addr0_temp : std_logic_vector(4 downto 0);
    signal rd_addr1_temp : std_logic_vector(4 downto 0);
	constant C0 : std_logic_vector(4 downto 0) := (others => '0');
	constant JAL_ADDR : std_logic_vector(4 downto 0) := std_logic_vector(to_unsigned(31,5));
    
begin
    process (clk, rst) is
    begin
        if (rst = '1') then
            for i in regs'range loop
                regs(i) <= (others => '0');
            end loop;
				
        elsif (rising_edge(clk)) then
            if (wr_en = '1') then
				
					if (JumpAndLink = '1') then
						regs(to_integer(unsigned(JAL_ADDR))) <= wr_data;
						
					elsif (wr_addr /= C0) then 
						regs(to_integer(unsigned(wr_addr))) <= wr_data;
					
					end if;
            end if;
				
            rd_addr0_temp <= rd_addr0;
            rd_addr1_temp <= rd_addr1;
				
        end if;
    end process;

    rd_data0 <= regs(to_integer(unsigned(rd_addr0_temp)));
    rd_data1 <= regs(to_integer(unsigned(rd_addr1_temp)));
    
end BHV;