library ieee;

use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity top_level is
    port (
        switch : in  std_logic_vector(9 downto 0);
        button : in  std_logic_vector(1 downto 0);
		clk : in  std_logic;
        led0 : out std_logic_vector(6 downto 0);
        led0_dp : out std_logic;
        led1 : out std_logic_vector(6 downto 0);
        led1_dp : out std_logic;
        led2 : out std_logic_vector(6 downto 0);
        led2_dp : out std_logic;
        led3 : out std_logic_vector(6 downto 0);
        led3_dp : out std_logic;
        led4 : out std_logic_vector(6 downto 0);
        led4_dp : out std_logic;
        led5 : out std_logic_vector(6 downto 0);
        led5_dp : out std_logic);
end top_level;


architecture STR of top_level is

    component decoder7seg
        port (
            input  : in  std_logic_vector(3 downto 0);
            output : out std_logic_vector(6 downto 0));
    end component;
	
	signal rst : std_logic;
	signal IR_31_26 : std_logic_vector(5 downto 0);
	signal IR_20_16	: std_logic_vector(4 downto 0);
	signal IP0 : std_logic_vector(31 downto 0);
	signal IP1 : std_logic_vector(31 downto 0);
	signal IP0_en : std_logic;
	signal IP1_en : std_logic;
	signal OP : std_logic_vector(31 downto 0);
	signal PCWriteCond : std_logic;
	signal PCWrite : std_logic;
	signal IorD : std_logic;
	signal MemWrite : std_logic;
	signal MemToReg : std_logic;
	signal IRWrite : std_logic;
	signal JumpAndLink : std_logic;
	signal IsSigned : std_logic;
	signal PCSource : std_logic_vector(1 downto 0);
	signal ALUOp : std_logic_vector(5 downto 0);
	signal ALUSrcB : std_logic_vector(1 downto 0);
	signal ALUSrcA : std_logic;
	signal RegWrite : std_logic;
	signal RegDst : std_logic;

begin

    IP1 <= std_logic_vector(to_unsigned(0,23)) & switch(8 downto 0);
    IP0 <= std_logic_vector(to_unsigned(0,23)) & switch(8 downto 0);
	IP1_en <= switch(9) and not button(1);
	IP0_en <= not switch(9) and not button(1);
	rst <= not button(0);
	 
	U_DATAPATH : entity work.datapath
		port map(
		clk  => clk,
		rst => rst,
		PCWriteCond => PCWriteCond,
		PCWrite => PCWrite,
		IorD => IorD,
		MemWrite => MemWrite,
		MemToReg => MemToReg,
		IRWrite => IRWrite,
		JumpAndLink => JumpAndLink,
		IsSigned => IsSigned,
		PCSource => PCSource,
		ALUOp => ALUOp,
		ALUSrcB => ALUSrcB,
		ALUSrcA => ALUSrcA,
		RegWrite => RegWrite,
		RegDst => RegDst,
		inport0 => IP0,
		inport1 => IP1,
		IP0_en => IP0_en,
		IP1_en => IP1_en,
		outport => OP,
		IR_31_26 => IR_31_26,
		IR_20_16 => IR_20_16);
				
	U_CTRL	: entity work.controller
		port map(
		clk => clk,
		rst => rst,
		IR_31_26 => IR_31_26,
		IR_20_16 => IR_20_16,
		PCWriteCond => PCWriteCond,
		PCWrite => PCWrite,
		IorD => IorD,
		MemWrite => MemWrite,
		MemToReg => MemToReg,
		IRWrite => IRWrite,
		JumpAndLink => JumpAndLink,
		IsSigned => IsSigned,
		PCSource => PCSource,
		ALUOp => ALUOp,
		ALUSrcB => ALUSrcB,
		ALUSrcA => ALUSrcA,
		RegWrite => RegWrite,
		RegDst => RegDst);

    U_LED5 : decoder7seg port map (
        input  => OP(23 downto 20),
        output => led5);

    U_LED4 : decoder7seg port map (
        input  => OP(19 downto 16),
        output => led4);

    U_LED3 : decoder7seg port map (
        input  => OP(15 downto 12),
        output => led3);

    U_LED2 : decoder7seg port map (
        input  => OP(11 downto 8),
        output => led2);
    
    U_LED1 : decoder7seg port map (
        input  => OP(7 downto 4),
        output => led1);

    U_LED0 : decoder7seg port map (
        input  => OP(3 downto 0),
        output => led0);

	led5_dp <= '1';
	led4_dp <= '1';
	led3_dp <= '1';
	led2_dp <= '1';
	led1_dp <= '1';
	led0_dp <= '1';

end STR;