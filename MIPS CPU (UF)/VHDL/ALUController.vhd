library ieee;
use ieee.std_logic_1164.all;

entity ALU_ctrl is
		port(
		IR_5_0 : in std_logic_vector(5 downto 0);
		IR_20_16 : in std_logic_vector(4 downto 0);
		ALUOp : in std_logic_vector(5 downto 0);
		HI_en : out std_logic;
		LO_en : out std_logic;
		ALU_LO_HI : out std_logic_vector(1 downto 0);
		OpSel : out std_logic_vector(5 downto 0));
end ALU_ctrl;
		
architecture BHV of ALU_ctrl is

	--CONTROLLER
	constant ST_BE : std_logic_vector(5 downto 0) := "000100";
	constant ST_BNE : std_logic_vector(5 downto 0) := "000101";
	constant ST_BLEZ : std_logic_vector(5 downto 0) := "000110";
	constant ST_BGTZ : std_logic_vector(5 downto 0) := "000111";
	constant ST_SP_BR : std_logic_vector(5 downto 0) := "000001";
	constant ST_J : std_logic_vector(5 downto 0) := "000010";
	constant ST_JAL : std_logic_vector(5 downto 0) := "000011";
	constant ST_PCADD : std_logic_vector(5 downto 0) := "111111";
	constant ST_ADDI : std_logic_vector(5 downto 0) := "001001";
	constant ST_SUBI : std_logic_vector(5 downto 0) := "010000";
	constant ST_ANDI : std_logic_vector(5 downto 0) := "001100";
	constant ST_ORI : std_logic_vector(5 downto 0) := "001101";
	constant ST_XORI : std_logic_vector(5 downto 0) := "001110";
	constant DOSLTI	: std_logic_vector(5 downto 0) := "001010";
	constant ST_SLTIU : std_logic_vector(5 downto 0) := "001011";
	constant ST_LW : std_logic_vector(5 downto 0) := "100011";
	constant ST_SW : std_logic_vector(5 downto 0) := "101011";
	
	--ALU
	constant LW : std_logic_vector(5 downto 0) := "001111";
	constant SW : std_logic_vector(5 downto 0) := "010001";
	constant BE : std_logic_vector(5 downto 0) := "010011";
	constant BNE : std_logic_vector(5 downto 0) := "010100";
	constant BLEZ : std_logic_vector(5 downto 0) := "010110";
	constant BGTZ : std_logic_vector(5 downto 0) := "010111";
	constant BLTZ : std_logic_vector(5 downto 0) := "010101";
	constant BGEZ : std_logic_vector(5 downto 0) := "011110";
	constant J : std_logic_vector(5 downto 0) := "111110";
	constant JAL : std_logic_vector(5 downto 0) := "111111";
	constant RTYPE : std_logic_vector(5 downto 0) := "000000";
	constant ADDI : std_logic_vector(5 downto 0) := "111101";
	constant SUBI : std_logic_vector(5 downto 0) := "000101";
	constant ANDI : std_logic_vector(5 downto 0) := "000111";
	constant ORI : std_logic_vector(5 downto 0) := "001001";
	constant XORI : std_logic_vector(5 downto 0) := "001011";
	constant MULT : std_logic_vector(5 downto 0) := "011000";
	constant MULTU : std_logic_vector(5 downto 0) := "011001";
	constant MVHI : std_logic_vector(5 downto 0) := "010000";
	constant MVLO : std_logic_vector(5 downto 0) := "010010";
	constant SLTIU : std_logic_vector(5 downto 0) := "001101";
	constant SLTI : std_logic_vector(5 downto 0) := "001110";
	constant PCADD : std_logic_vector(5 downto 0) := "111100";
	constant FAKE : std_logic_vector(5 downto 0) := "111011";
	
begin
		
	process(IR_5_0, IR_20_16, ALUOp)
	begin
		HI_en <= '0';
		LO_en <= '0';
		ALU_LO_HI <= "00";
		OPSel <= FAKE;
		
		case ALUop is
		
			when RTYPE =>
				OpSel <= IR_5_0;
				
				case IR_5_0 is
					
					when MULT =>
						HI_en <= '1';
						LO_en <= '1';
					
					when MULTU =>
						HI_en <= '1';
						LO_en <= '1';
					
					when MVLO =>
						ALU_LO_HI <= "01";
					
					when MVHI =>
						ALU_LO_HI <= "10";
					
					when others => null;

				end case;
			
			when ST_ADDI =>
				OPSel <= ADDI;
			
			when ST_SUBI =>
				OPSel <= SUBI;
			
			when ST_ANDI =>
				OPSel <= ANDI;
			
			when ST_ORI =>
				OPSel <= ORI;
			
			when ST_XORI =>
				OPSel <= XORI;
			
			when ST_SLTIU =>
				OPSel <= SLTIU;
			
			when DOSLTI =>
				OPSel <= SLTI;
			
			when ST_LW =>
				OPSel <= lW;
			
			when ST_SW =>
				OPSel <= SW;
			
			when ST_BE =>
				OPSel <= BE;
			
			when ST_BNE =>
				OPSel <= BNE;
			
			when ST_BLEZ =>
				OPSel <= BLEZ;
			
			when ST_BGTZ =>
				OPSel <= BGTZ;
			
			when ST_J =>
				OPSel <= J;
			
			when ST_JAL =>
				OpSel <= JAL;
			
			when ST_SP_BR =>
				if (IR_20_16 = "00000") then
					OPSel <= BLTZ;
				elsif (IR_20_16 = "00001") then
					OPSel <= BGEZ;
				end if;
			
			when ST_PCADD =>
				OpSel <= PCADD;
			
			when others =>
				OPSel <= FAKE;
		end case;
	end process;
end BHV;