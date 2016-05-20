-- Made by Mathias Gregersen 14/03 2016

--Library declarations--
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
--End of Library declarations--


--Entity declaration--
entity Mux_Display is
	port( clk_50MHz: 	in		std_logic;
			bcd:			in		std_logic_vector(15 downto 0);
			segm:			out	std_logic_vector(1 to 8);
			an:			out 	std_logic_vector(3 downto 0);
			clk_1kHz:	out	std_logic);
end Mux_Display;
--End of Entity declaration--


--Architecture of entity--
architecture Behavioral of Mux_Display is
	signal clk_1kHz_holder:	std_logic;
	signal current_bcd:		std_logic_vector(3 downto 0);
	signal decimal_point:	std_logic;
	signal segments:			std_logic_vector(1 to 8);

--Function for conversion--
	function conv_boolean(b:boolean) return std_logic is
		variable result: std_logic := '0';
	begin
		if b then result := '1'; end if;
		return result;
	end conv_boolean;

begin
	
	clk_1kHz <= clk_1kHz_holder;
	segm <= segments;

--Process that scales the clock--
clock_scale:
	process(clk_50MHz)
		variable i: integer range 0 to 50000;
	begin
		if rising_edge(clk_50MHz) then
			if i < 50000 then
				i := i + 1;
				clk_1kHz_holder <= '0';
			else
				i := 1;
				clk_1kHz_holder <= '1';
			end if;
		end if;
	end process;

--Process that multiplex--
multiplexer:
	process(clk_1kHz_holder)
		variable k: std_logic_vector(1 downto 0);
	begin
		if rising_edge(clk_1kHz_holder) then
			k := k+1;
			case k is
				when "00" =>
					current_bcd 	<= bcd(3 downto 0);
					an					<= "1110";
				when "01" =>
					current_bcd 	<= bcd(7 downto 4);
					an					<= "1101";
				when "10" =>
					current_bcd 	<= bcd(11 downto 8);
					an					<= "1011";
				when "11" =>
					current_bcd 	<= bcd(15 downto 12);
					an					<= "0111";
				when others =>
					null;
			end case;
		end if;
	end process;

--Process that translates bcd to segments--
bcd_to_segment:
	process(current_bcd)
		type j_bool_array is array(15 downto 0) of boolean;
		variable j: j_bool_array;
		variable seg_a, seg_b, seg_c, seg_d, seg_e, seg_f, seg_g: std_logic;
	begin
		j := (others => false);								--Reset array
		j(conv_integer(current_bcd)) := true;			--Set j(bcd) = true
		seg_a := conv_boolean(j( 1) or j( 4) or j(11) or j(13));
		seg_b := conv_boolean(j( 5) or j( 6) or j(11) or j(12) or j(14) or j(15));
		seg_c := conv_boolean(j( 2) or j(12) or j(14) or j(15));
		seg_d := conv_boolean(j( 1) or j( 4) or j( 7) or j(10) or j(15));
		seg_e := conv_boolean(j( 1) or j( 3) or j( 4) or j( 5) or j( 7) or j( 9));
		seg_f := conv_boolean(j( 1) or j( 2) or j( 3) or j( 7) or j(13));
		seg_g := conv_boolean(j( 0) or j( 1) or j( 7) or j(12));
		
		segments <= seg_a & seg_b & seg_c & seg_d & seg_e & seg_f & seg_g & '1';
	end process;


end Behavioral;
--End of Architecture of entity--
