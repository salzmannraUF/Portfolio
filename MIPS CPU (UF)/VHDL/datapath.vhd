library ieee;

use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity datapath is
	port(
		clk	: in std_logic;
		rst : in std_logic;
		PCWriteCond : in std_logic;
		PCWrite : in std_logic;
		IorD : in std_logic;
		MemWrite : in std_logic;
		MemToReg : in std_logic;
		IRWrite : in std_logic;
		JumpAndLink : in std_logic;
		IsSigned : in std_logic;
		PCSource : in std_logic_vector(1 downto 0);
		ALUOp : in std_logic_vector(5 downto 0);
		ALUSrcB	: in std_logic_vector(1 downto 0);
		ALUSrcA : in std_logic;
		RegWrite : in std_logic;
		RegDst : in std_logic;
		inport0 : in std_logic_vector(31 downto 0);
		inport1 : in std_logic_vector(31 downto 0);
		IP0_en : in std_logic;
		IP1_en : in std_logic;
		outport : out std_logic_vector(31 downto 0);
		IR_31_26 : out std_logic_vector(5 downto 0);
		IR_20_16 : out std_logic_vector(4 downto 0));
		
end datapath;

architecture STR of datapath is

	constant width : positive := 32;
	
	signal MEM_D_REG_OUT : std_logic_vector(31 downto 0);	
	signal REGA_OUT,REGB_OUT : std_logic_vector(31 downto 0);
	signal REG_ALU_OUT : std_logic_vector(31 downto 0);
	signal WR_ADDR_TEMP	: std_logic_vector(4 downto 0);
	signal WR_DATA_TEMP : std_logic_vector(31 downto 0);
	signal WR_DATA_MUX_IP1 : std_logic_vector(31 downto 0);
	signal IR_out : std_logic_vector(31 downto 0);
	signal INSTR_OUT, INSTR_NEXT : std_logic_vector(31 downto 0);
	signal MEM_ADDR : std_logic_vector(31 downto 0);
	signal OP : std_logic_vector(5 downto 0);
	signal HI_OUT, LO_OUT : std_logic_vector(31 downto 0);
	signal REG_HI_OUT, REG_LO_OUT : std_logic_vector(31 downto 0);
	signal HI_en,LO_en : std_logic;
	signal branch : std_logic;
	signal PC_en : std_logic;
	signal MEM_DATA_OUT : std_logic_vector(31 downto 0);
	signal ALU_LO_HI_sel : std_logic_vector(1 downto 0);
	signal ALU_OUT : std_logic_vector(31 downto 0);
	signal concat_out : std_logic_vector(31 downto 0);
	signal MUX_REGA_OUT, regB_mux : std_logic_vector(31 downto 0);
	signal sign_ext_OP,sign_ext_OP_shifted	: std_logic_vector(31 downto 0);


begin
	U_ALU : entity work.ALU
		generic map(WIDTH => WIDTH)
		port map(
			shift => IR_OUT(10 downto 6),
			input1 => MUX_REGA_OUT,
			input2 => regB_mux,
			OP => OP,
			result => ALU_out,
			result_HI => HI_OUT,
			result_LO => LO_OUT,
			branch => branch);

	U_ALU_CTRL	: entity work.ALU_ctrl
		port map(
			IR_5_0 => IR_OUT(5 downto 0),
			IR_20_16 => IR_OUT(20 downto 16),
			ALUOp => ALUOp,
			HI_en => HI_en,
			LO_en => Lo_en,
			ALU_LO_HI => ALU_LO_HI_sel,
			OpSel => OP);
		

	U_MEM_BLK : entity work.memory
		port map(
			clk => clk,
			memWrite => memWrite,
			address => MEM_ADDR,
			inport0 => inport0,
			inport1 => inport1,
			IP0_en => IP0_en,
			IP1_en => IP1_en,
			wrdata	=> REGB_OUT,
			outport => OutPort,
			data_out => MEM_DATA_OUT);
			
	U_REGS_FILE	: entity work.registers
		port map(
		  clk => clk,
		  rst => rst,
		  rd_addr0 => IR_OUT(25 downto 21),
		  rd_addr1 => IR_OUT(20 downto 16),
		  wr_addr => WR_ADDR_TEMP,
		  wr_en => RegWrite,
		  JumpAndLink => JumpAndLink,
		  wr_data => WR_DATA_TEMP,
		  rd_data0 => REGA_OUT, 
		  rd_data1 => REGB_OUT); 
								
	--REGISTERS
	U_PC_REG : entity work.reg
		generic map(WIDTH => WIDTH)
		port map(
			clk => clk,
			rst => rst,
			en => PC_en,
			input => INSTR_NEXT,
			output => INSTR_OUT);
			
	U_MEMD_REG : entity work.reg				
		generic map(WIDTH => WIDTH)
		port map(
			clk => clk,
			rst => rst,
			en => '1',
			input => MEM_DATA_OUT,
			output => MEM_D_REG_OUT);
			
	U_INSTR_REG	: entity work.reg
		generic map(WIDTH => WIDTH)
		port map(
			clk => clk,
			rst => rst,
			en => IRWrite,
			input => MEM_DATA_OUT,
			output => IR_out);
			
	U_ALU_OUT : entity work.reg
		generic map(WIDTH => WIDTH)
		port map(
		clk => clk,
		rst => rst,
		en => '1',
		input => ALU_out,
		output => REG_ALU_OUT);
	
	U_HI_REG : entity work.reg
		generic map(WIDTH => WIDTH)
		port map(
			clk => clk,
			rst => rst,
			en => HI_en,
			input => HI_OUT,
			output => REG_HI_OUT);
			
	U_LO_REG : entity work.reg
		generic map(WIDTH => WIDTH)
		port map(
			clk => clk,
			rst => rst,
			en => LO_en,
			input => LO_OUT,
			output => REG_LO_OUT);
			
	-- MUXES		
	U_PC_MUX : entity work.mux_2x1
		generic map(WIDTH => WIDTH)
		port map(
			input1 => INSTR_OUT,
			input2 => REG_ALU_OUT,
			output => MEM_ADDR,
			sel => IorD);
				
	U_WREG_MUX : entity work.mux_2x1
		generic map(WIDTH => 5)
		port map(
			input1 => IR_OUT(20 downto 16),
			input2 => IR_OUT(15 downto 11),
			output =>  WR_ADDR_TEMP,
			sel => RegDst);
			
	U_WR_DATA_MUX : entity work.mux_2x1
		generic map(WIDTH => WIDTH)
		port map(
			input1 => WR_DATA_MUX_IP1,
			input2 => MEM_D_REG_OUT,
			output => WR_DATA_TEMP,
			sel => MemToReg);
	
	U_REGB_MUX : entity work.mux_4x1
		generic map(WIDTH => WIDTH)
		port map(
			input1 => REGB_OUT,
			input2 => x"00000004",
			input3 => sign_ext_OP,
			input4 => sign_ext_OP_shifted,
			output => regB_mux,
			sel => ALUSrcB);
						
	U_REGA_MUX : entity work.mux_2x1	
		generic map(WIDTH => WIDTH)
		port map(
			input1 => INSTR_OUT,
			input2 => REGA_OUT,
			output => MUX_REGA_OUT,
			sel => ALUSrcA);		  
					
	U_ALU_MUX : entity work.mux_4x1				
		generic map(WIDTH => WIDTH)
		port map(
			input1 => REG_ALU_OUT,
			input2 => REG_LO_OUT,
			input3 => REG_HI_OUT,
			input4 => x"00000000",
			output => WR_DATA_MUX_IP1,
			sel => ALU_LO_HI_sel);

	U_PC_SEL_MUX : entity work.mux_4x1
		generic map(WIDTH => WIDTH)
		port map(
			input1 => ALU_out,
			input2 => REG_ALU_OUT,
			input3 => concat_out,
			input4 => x"00000000",
			output => INSTR_NEXT,
			sel => PCsource);
	
	U_SIGN_EXT : entity work.sign_extend
		port map(
			input		=> IR_OUT(15 downto 0),
			IsSigned => IsSigned,
			output   => sign_ext_OP,
			output_shifted => sign_ext_OP_shifted);
				
	U_CONCAT : entity work.concat
		port map(
			IR => IR_OUT(25 downto 0),
			PC => INSTR_OUT(31 downto 28),
			concat => concat_out);
	
	PC_en <= PCWrite or (PCWriteCond and branch);	
	IR_31_26 <= IR_OUT(31 downto 26);
	IR_20_16 <= IR_OUT(20 downto 16);

end STR;