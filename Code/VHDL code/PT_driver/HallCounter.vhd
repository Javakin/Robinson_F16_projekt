--------------------------------------------------------------------------------
--
-- MODULENAME	: Hallcounter.vhd
-- PROJECT		: P&T system
-- DESCRIPTION	: See documentation
--
-- CHANGE LOG:
--------------------------------------------------------------------------------
-- DATE		ID		CHANGE
-- DDMMYY
------------------------
-- 130516	MG		Module created.
-- 140516	MG		Added: circular counting
--
--------------------------------------------------------------------------------

--Library declarations
--------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


--Entity declaration
--------------------------------------------------------------------------------
entity Hall_Counter is
	generic( max_val: integer := 1080;
				start_val: integer := 540);
   port( HALL1: in std_logic;
         HALL2: in std_logic;
         POSITION: out std_logic_vector(10 downto 0);
			CLK: in std_logic);
end Hall_Counter;


--Architecture of entity
--------------------------------------------------------------------------------
architecture Behavioral of Hall_Counter is
	signal debounce_hall1: std_logic_vector(1 downto 0) := "00";
	signal debounce_hall2: std_logic_vector(1 downto 0) := "00";

begin

-- Sensor sampling --
sampling_pro:
	process(CLK)
	begin
		if rising_edge(CLK) then -- Sample and shift
			debounce_hall1 <= debounce_hall1(0) & HALL1;
			debounce_hall2 <= debounce_hall2(0) & HALL2;
		end if;
	end process;


-- Calculating process --
calculation_pro:
	process(CLK)
		variable pos: integer range -1 to max_val := start_val;
	begin
		if falling_edge(CLK) then -- Calculate pos
			if debounce_hall1 = "01" then
				if HALL2 = '1' then
						pos := pos + 1;
				else
						pos := pos - 1;
				end if;
				
			elsif debounce_hall1 = "10" then
				if HALL2 = '1' then
					pos := pos - 1;
				else
					pos := pos + 1;
				end if;
				
			elsif debounce_hall2 = "01" then
				if HALL1 = '1' then
					pos := pos - 1;
				else
					pos := pos + 1;
				end if;
				
			elsif debounce_hall2 = "10" then
				if HALL1 = '1' then
					pos := pos + 1;
				else
					pos := pos - 1;
				end if;
			end if;
		
			if pos = max_val then -- Create circle
				pos := 0;
			elsif pos = -1 then
				pos := max_val - 1;
			end if;
		
			POSITION <=  conv_std_logic_vector(pos,11);
		
		end if;
	end process;
	
end Behavioral;