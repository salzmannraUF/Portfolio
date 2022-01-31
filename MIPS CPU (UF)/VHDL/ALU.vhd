library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity alu is
	generic(
		WIDTH : integer := 16);
	port(
		shift : in std_logic_vector(4 downto 0);
		input1 : in std_logic_vector(WIDTH-1 downto 0);
		input2 : in std_logic_vector(WIDTH-1 downto 0);
		OP : in std_logic_vector(5 downto 0);
		result : out std_logic_vector(WIDTH-1 downto 0);
		result_HI : out std_logic_vector(WIDTH-1 downto 0);
		result_LO : out std_logic_vector(WIDTH-1 downto 0);
		branch : out std_logic);
		
end alu;

architecture BHV of alu is
	
	constant ADD_UN	: std_logic_vector(5 downto 0) := "100001";
	constant ADD_IMM : std_logic_vector(5 downto 0) := "111101";
	constant SUB_UN : std_logic_vector(5 downto 0) := "100011";
	constant SUB_IMM : std_logic_vector(5 downto 0) := "000101";
	constant MULT : std_logic_vector(5 downto 0) := "011000";
	constant MULT_UN : std_logic_vector(5 downto 0) := "011001";
	constant AND_C : std_logic_vector(5 downto 0) := "100100";
	constant AND_IMM : std_logic_vector(5 downto 0) := "000111";
	constant OR_C : std_logic_vector(5 downto 0) := "100101";
	constant OR_IMM : std_logic_vector(5 downto 0) := "001001";
	constant XOR_C : std_logic_vector(5 downto 0) := "100110";
	constant XOR_IMM : std_logic_vector(5 downto 0) := "001011";
	constant SHRL : std_logic_vector(5 downto 0) := "000010";
	constant SHLL : std_logic_vector(5 downto 0) := "000000";
	constant SHRA : std_logic_vector(5 downto 0) := "000011";
	constant SLT : std_logic_vector(5 downto 0) := "101010";
	constant SLTI : std_logic_vector(5 downto 0) := "001110";
	constant SLTIU : std_logic_vector(5 downto 0) := "001101";
	constant SLTU : std_logic_vector(5 downto 0) := "101011";
	constant MVHI : std_logic_vector(5 downto 0) := "010000";
	constant MVLO : std_logic_vector(5 downto 0) := "010010";
	constant LW	: std_logic_vector(5 downto 0) := "001111";
	constant SW : std_logic_vector(5 downto 0) := "010001";
	constant BE : std_logic_vector(5 downto 0) := "010011";
	constant BNE : std_logic_vector(5 downto 0) := "010100";
	constant BLEZ : std_logic_vector(5 downto 0) := "010110";
	constant BGTZ : std_logic_vector(5 downto 0) := "010111";
	constant BLTZ : std_logic_vector(5 downto 0) := "010101";
	constant BGEZ : std_logic_vector(5 downto 0) := "011110";
	constant J : std_logic_vector(5 downto 0) := "111110";
	constant JAL : std_logic_vector(5 downto 0) := "111111";
	constant JR : std_logic_vector(5 downto 0) := "001000";
	constant PCADD : std_logic_vector(5 downto 0) := "111100";
	signal IR : std_logic_vector(WIDTH-1 downto 0);
	
	constant C0 : std_logic_vector(WIDTH-1 downto 0) := (others => '0');
	constant C1 : std_logic_vector(WIDTH-1 downto 0) := std_logic_vector(to_unsigned(1,WIDTH));
begin
	IR <= std_logic_vector(to_unsigned(0,WIDTH-5)) & shift;
	
	process(IR, input1,input2, OP)
		variable temp 			: std_logic_Vector(WIDTH-1 downto 0);
		variable temp_mult	: std_logic_vector(2*WIDTH-1 downto 0);
	begin
	temp_mult := (others => '0');
	temp := (others => '0');
	branch <= '0'; 
	
		case OP is
			
			when ADD_UN => 
				temp := std_logic_vector(signed(input1) + signed(input2));
			
			when ADD_IMM =>
				temp := std_logic_vector(signed(input1) + signed(input2));
			
			when SUB_IMM => 
				temp := std_logic_vector(signed(input1) - signed(input2));
			
			when SUB_UN => 
				temp := std_logic_vector(signed(input1) - signed(input2));
			
			when MULT_UN => 
				temp_mult := std_logic_vector(unsigned(input1) * unsigned(input2));
				temp := temp_mult(WIDTH-1 downto 0);
			
			when MULT => 
				temp_mult := std_logic_vector(signed(input1) * signed(input2));
				temp := temp_mult(WIDTH-1 downto 0);
			
			when AND_C => 
			temp := std_logic_vector(unsigned(input1) and unsigned(input2));
			
			when AND_IMM => 
			temp := std_logic_vector(unsigned(input1) and unsigned(input2));
			
			when OR_C =>
			temp := std_logic_vector(unsigned(input1) or unsigned(input2));

			when OR_IMM =>
			temp := std_logic_vector(unsigned(input1) or unsigned(input2));
			
			when XOR_C => 
			temp := std_logic_vector(unsigned(input1) xor unsigned(input2));

			when XOR_IMM => 
			temp := std_logic_vector(unsigned(input1) xor unsigned(input2));
			
			when SHRL => 
			temp := std_logic_vector(SHIFT_RIGHT(unsigned(input2),to_integer(unsigned(IR))));
			
			when SHLL => 
			temp := std_logic_vector(SHIFT_LEFT(unsigned(input2),to_integer(unsigned(IR))));
			
			when SHRA => 
			temp := std_logic_vector(SHIFT_RIGHT(signed(input2),to_integer(unsigned(IR))));
			
			when SLT => 
			if (signed(input1) < signed(input2)) then
				temp := C1;			
			else
				temp := C0;			
			end if;
			
			when SLTI => 
			if (signed(input1) < signed(input2)) then
				temp := C1;			
			else
				temp := C0;			
			end if;
			
			when SLTIU => 
			if (unsigned(input1) < unsigned(input2)) then
				temp := C1;
			else
				temp := C0;
			end if;	

			when SLTU => 
			if (unsigned(input1) < unsigned(input2)) then
				temp := C1;
			else
				temp := C0;
			end if;	
			
			when MVHI =>

			when MVLO =>

			when LW => 
				temp := std_logic_vector(unsigned(input1) + unsigned(input2));
			
			when SW =>
				temp := std_logic_vector(unsigned(input1) + unsigned(input2));
			
			when BE => 
				if (unsigned(input1) = unsigned(input2)) then
					branch <= '1';
				end if;
				
			when BNE =>
				if (unsigned(input1) /= unsigned(input2)) then
					branch <= '1';
				end if;
				
			when BLTZ => 
				if (input1(WIDTH-1) = '1') then
					branch <= '1';
				end if;
				
			when BLEZ => 
				if (unsigned(input1) = 0 or input1(WIDTH-1) = '1') then
					branch <= '1';
				end if;
				
			when BGTZ =>
				if (signed(input1) > 0) then
					branch <= '1';
				end if;
				
			when BGEZ =>
				if (input1(WIDTH-1) = '0') then
					branch <= '1';
				end if;
				
			when J =>

			when JAL =>
			 
			when JR =>
				temp := input1; 
				branch <= '1'; 
			
			when PCADD => 
				temp := std_logic_vector(unsigned(input1) + unsigned(input2));
			
			when others => null;
					
		end case;
			result 		<= temp(WIDTH-1 downto 0);
			result_HI	<= temp_mult(2*WIDTH-1 downto WIDTH);
			result_LO	<= temp_mult(WIDTH-1 downto 0);
	end process;
end BHV;
		