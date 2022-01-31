library ieee;

use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity controller is
	port(
		clk	: in std_logic;
		rst	: in std_logic;
		IR_31_26 : in std_logic_vector(5 downto 0); 
		IR_20_16 : in std_logic_vector(4 downto 0); 
		PCWriteCond : out std_logic;
		PCWrite : out std_logic;
		IorD : out std_logic;
		MemWrite : out std_logic;
		MemToReg : out std_logic;
		IRWrite : out std_logic;
		JumpAndLink : out std_logic;
		IsSigned : out std_logic;
		PCSource : out std_logic_vector(1 downto 0);
		ALUOp : out std_logic_vector(5 downto 0);
		ALUSrcB	: out std_logic_vector(1 downto 0);
		ALUSrcA : out std_logic;
		RegWrite : out std_logic;
		RegDst : out std_logic);
end controller;		

architecture BHV of controller is
	type state_type is (Instr_Fetch_Start,Instr_Fetch,Instr_Decode,Instr_Execute,Instr_Complete,LW_Wait,LorS_Wait, FAKE);
	signal state, next_state : state_type;

	constant ST_ADDI : std_logic_vector(5 downto 0) := "001001";
	constant ST_SUBI : std_logic_vector(5 downto 0) := "010000";
	constant ST_ANDI : std_logic_vector(5 downto 0) := "001100";
	constant ST_ORI : std_logic_vector(5 downto 0) := "001101";
	constant ST_XORI : std_logic_vector(5 downto 0) := "001110";
	constant ST_SLTI : std_logic_vector(5 downto 0) := "001010";
	constant ST_SLTIU : std_logic_vector(5 downto 0) := "001011";
	constant ST_LW : std_logic_vector(5 downto 0) := "100011";
	constant ST_SW : std_logic_vector(5 downto 0) := "101011";
	constant ST_BE : std_logic_vector(5 downto 0) := "000100";
	constant ST_BNE : std_logic_vector(5 downto 0) := "000101";
	constant ST_BLEZ : std_logic_vector(5 downto 0) := "000110";
	constant ST_BGTZ : std_logic_vector(5 downto 0) := "000111";
	constant ST_SP_BR : std_logic_vector(5 downto 0) := "000001";
	constant ST_J : std_logic_vector(5 downto 0) := "000010";
	constant ST_JAL : std_logic_vector(5 downto 0) := "000011";
	constant ST_PCADD : std_logic_vector(5 downto 0) := "111111";
	constant ST_R_TYPE : std_logic_vector(5 downto 0) := "000000";
	constant ST_JR : std_logic_vector(5 downto 0) := "000011";
	
begin
	process(clk, rst)
	begin
			if(rst = '1') then
				state <= Instr_Fetch_Start;
			elsif(rising_edge(clk)) then
				state <= next_state;
			end if;
	end process;
	
	process(state, IR_31_26, IR_20_16)
	begin
		IRWrite <= '0';
		JumpAndLink <= '0';
		IsSigned <= '0';
		PCSource <= "00";
		ALUOp <= ST_R_TYPE;
		ALUSrcB <= "00";
		ALUSrcA <= '1';
		RegWrite <= '0';
		RegDst <= '0';
		PCWriteCond <= '0';
		PCWrite <= '0';
		IorD <= '0';
		MemWrite <= '0';
		MemToReg	<= '0';
		next_state <= FAKE;

		case state is
			when Instr_Fetch_Start =>
				IorD <= '0';
				next_state <= Instr_Fetch;
			
			when Instr_Fetch =>
				ALUOP <= ST_PCADD; 
				PCSource <= "00";
				PCWrite <= '1';
				next_state <= Instr_Decode;	
				IRWrite <= '1';
				ALUSrcA <= '0';
				ALUSrcB <= "01";

			when Instr_Decode =>
				ALUOp <= IR_31_26; 
				next_state <= Instr_Execute;
				ALUSrcA <= '0'; 
				ALUSrcB <= "11"; 
				
				case IR_31_26 is
				
					when ST_J =>
						PCSource <= "10";
						PCWrite <= '1';
						next_state <= Instr_Fetch_Start;
					
					when ST_JAL => 
						MemToReg <= '0';
						RegWrite <= '1';
						JumpAndLink <= '1';
						PCSource <= "10";
						PCWrite <= '1';
						next_state <= Instr_Fetch_Start;
				
					when ST_BE =>
						ALUSrcA <= '0';  
						ALUSrcB <= "11";
						ALUOp <= ST_ADDI;
						IsSigned <= '1'; 
					
					when ST_BNE =>
						ALUSrcA <= '0';
						ALUSrcB <= "11";
						ALUOp <= ST_ADDI;
						IsSigned <= '1';
					
					when ST_BLEZ =>
						ALUOp <= ST_ADDI;
						ALUSrcA <= '0';
						ALUSrcB <= "11";
						IsSigned <= '1';
					
					when ST_BGTZ =>
						ALUSrcA <= '0';
						ALUSrcB <= "11";
						ALUOp <= ST_ADDI;
						IsSigned <= '1';
					
					when ST_SP_BR =>
						ALUSrcA <= '0';
						ALUSrcB <= "11";
						ALUOp <= ST_ADDI;
						IsSigned <= '1';
					
					when others =>
						null;
				end case;
				
			when Instr_Execute =>
				ALUOp <= IR_31_26; 				
				next_state <= Instr_Complete;
				
				case IR_31_26 is
					when ST_R_TYPE =>
						ALUSrcA <= '1';
						ALUSrcB <= "00";
						PCSource <= "00";
						PCWriteCond <= '1'; 
						
					when ST_ADDI => 
						ALUSrcA <= '1';
						IsSigned <= '1';
						ALUSrcB <= "10";
					
					when ST_SUBI =>
						ALUSrcA <= '1';
						IsSigned <= '1';
						ALUSrcB <= "10";
					
					when ST_ANDI =>
						ALUSrcA <= '1';
						IsSigned <= '0';
						ALUSrcB <= "10";						
					
					when ST_ORI =>
						ALUSrcA <= '1';
						IsSigned <= '0';
						ALUSrcB <= "10";
					
					when ST_XORI =>
						ALUSrcA <= '1';
						IsSigned <= '0';
						ALUSrcB <= "10";
					
					when ST_SLTIU =>
						ALUSrcA <= '1';
						IsSigned <= '0';
						ALUSrcB <= "10";
					
					when ST_SLTI =>
						ALUSrcA <= '1';
						IsSigned <= '1';
						ALUSrcB <= "10";
					
					when ST_LW =>
						ALUSrcA <= '1';
						ALUSrcB <= "10";
					
					when ST_SW =>
						ALUSrcA <= '1';
						ALUSrcB <= "10";
					
					when ST_BE =>
						PCWriteCond <= '1';
						PCSource <= "01";
						ALUSrcA <= '1';
						ALUSrcB <= "00";
						ALUOp <= ST_BE;
						next_state <= Instr_Fetch_Start;
					
					when ST_BNE =>
						PCWriteCond <= '1';
						PCSource <= "01";
						ALUSrcA <= '1';
						ALUSrcB <= "00";
						ALUOp <= ST_BNE;
						next_state <= Instr_Fetch_Start;
					
					when ST_BLEZ =>
						PCWriteCond <= '1';
						PCSource <= "01";
						ALUSrcA <= '1';
						ALUSrcB <= "00";
						ALUOp <= ST_BLEZ;
						next_state <= Instr_Fetch_Start;
					
					when ST_BGTZ =>
						PCWriteCond <= '1';
						PCSource <= "01";
						ALUSrcA <= '1';
						ALUSrcB <= "00";
						ALUOp <= ST_BGTZ;
						next_state <= Instr_Fetch_Start;				
					
					when ST_J =>

					
					when ST_JAL =>

					
					when ST_SP_BR =>
						PCWriteCond <= '1';
						PCSource <= "01";
						ALUSrcA <= '1';
						ALUSrcB <= "00";
						ALUOp <= ST_SP_BR; 
						next_state <= Instr_Fetch_Start;
					
					when others =>
						next_state <= FAKE; 
				end case;
			
			when Instr_Complete =>
				ALUOp <= IR_31_26;
				ALUSrcA <= '1';
				next_state <= Instr_Fetch_Start; 
				
				case IR_31_26 is
					
					when ST_R_TYPE =>
						RegWrite <= '1';
						MemtoReg <= '0';
						RegDst <= '1';
						ALUSrcB <= "00";
					
					when ST_ADDI =>
						RegWrite <= '1';
						MemtoReg <= '0';
						RegDst <= '0';
						ALUSrcB <= "00";
					
					when ST_SUBI =>
						RegWrite <= '1';
						MemtoReg <= '0';
						RegDst <= '0';
						ALUSrcB <= "00";
					
					when ST_ANDI =>
						RegWrite <= '1';
						MemtoReg <= '0';
						RegDst <= '0';
						ALUSrcB <= "00";				
					
					when ST_ORI =>
						RegWrite <= '1';
						MemtoReg <= '0';
						RegDst <= '0';
						ALUSrcB <= "00";
					
					when ST_XORI =>
						RegWrite <= '1';
						MemtoReg <= '0';
						RegDst <= '0';
						ALUSrcB <= "00";
					
					when ST_SLTIU =>
						RegWrite <= '1';
						MemtoReg <= '0';
						RegDst <= '0';
						ALUSrcB <= "00";
					
					when ST_SLTI =>
						RegWrite <= '1';
						MemtoReg <= '0';
						RegDst <= '0';
						ALUSrcB <= "00";
					
					when ST_LW => 
						MemtoReg <= '0';
						IorD <= '1';
						ALUSrcA <= '1';
						ALUSrcB <= "10";			
						next_state <= LW_Wait;
					
					when ST_SW =>
						ALUSrcA <= '1';
						ALUSrcB <= "10";
						IorD <= '1';
						MemWrite <= '1';
						next_state <= LorS_Wait;
					
					when others =>
						next_state <= FAKE; 
				end case;
			
			when LW_Wait =>
				IorD <= '1';
				next_state <= LorS_Wait;
			
			when LorS_Wait => 
				case IR_31_26 is
					when ST_LW =>
					MemtoReg <= '1';
					RegDst <= '0';
					RegWrite <= '1';
					next_state <= Instr_Fetch_Start; 
					
					when ST_SW => 
						IorD <= '1';
						MemWrite <= '0';
						next_state <= Instr_Fetch_Start;
					
					when others =>
						next_state <= FAKE; 
				end case;
			when others =>
				null;
		end case;
	end process;
end BHV;
