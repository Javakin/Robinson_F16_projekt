--------------------------------------------------------------------------------
--
-- MODULENAME	: Simple_comparator.vhd
-- PROJECT		: P&T system
-- DESCRIPTION	: See documentation
--
-- CHANGE LOG:
--------------------------------------------------------------------------------
-- DATE		ID		CHANGE
-- DDMMYY
------------------------
-- 120516	MG		Module created.
-- 140516	MG		Added: constrains, shortest path and circular counting
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
entity Simple_comparator is
	generic( max_val: integer := 1080;
				constrain_min: integer := 361;
				constrain_max: integer := 710);
				
	port( INPUT: in std_logic_vector(10 downto 0);
			FEEDBACK: in std_logic_vector(10 downto 0);
			OUTPUT: out std_logic_vector(10 downto 0);
			DIR: out std_logic;
			CONSTRAINER: in std_logic);
end Simple_comparator;


--Architecture of entity
--------------------------------------------------------------------------------
architecture Behavioral of Simple_comparator is
	signal compare_val: std_logic_vector(10 downto 0);
	signal complement_val: std_logic_vector(10 downto 0);
	signal direction: std_logic;
begin
	
	compare_val <= INPUT - FEEDBACK when INPUT > FEEDBACK else FEEDBACK - INPUT;
	complement_val <= conv_std_logic_vector(max_val, 11) - compare_val;
	direction <= '1' when (INPUT > FEEDBACK) else '0';

	process(compare_val, complement_val, direction, CONSTRAINER)
	begin
		if CONSTRAINER = '0' then
			if compare_val < complement_val then
				OUTPUT <= compare_val;
				DIR <= direction;
			else
				OUTPUT <= complement_val;
				DIR <= not(direction);
			end if;
		else
			if INPUT < conv_std_logic_vector(constrain_min, 11) then
				if conv_std_logic_vector(constrain_min, 11) > FEEDBACK then
					OUTPUT <= conv_std_logic_vector(constrain_min, 11) - FEEDBACK;
					DIR <= '1';
					else
					OUTPUT <= FEEDBACK - conv_std_logic_vector(constrain_min, 11);
					DIR <= '0';
				end if;
			elsif INPUT > conv_std_logic_vector(constrain_max, 11) then
				if conv_std_logic_vector(constrain_max, 11) > FEEDBACK then
					OUTPUT <= conv_std_logic_vector(constrain_max, 11) - FEEDBACK;
					DIR <= '1';
				else
					OUTPUT <= FEEDBACK - conv_std_logic_vector(constrain_max, 11);
					DIR <= '0';
				end if;
			else
				OUTPUT <= compare_val;
				DIR <= direction;
			end if;
		end if;
	end process;

end Behavioral;

